
#include <QTextStream>
#include <QFile>
#include <QFileInfo>

#include "Stars.h"

/********************/
/** サーバとの接続 **/

Stars::Stars( void ) : QObject()
{
  ss = NULL;
  StarsServer = STARSSERVER;
  StarsSPort  = STARSPORT;
  newSetting = true;
}

void Stars::SetNewSVAddress( const QString &item )
{
  StarsServer = item;
  
  qDebug() << "Stars Server " << StarsServer;
  if ( ss != NULL ) {
    ss->disconnectFromHost();
    delete ss;
    ss = NULL;
    newSetting = true;
    MakeConnection();
  }
}

void Stars::SetNewSVPort( const QString &item )
{
  StarsSPort = item.toInt();

  qDebug() << "Stars Port " << StarsSPort;
  if ( ss != NULL ) {
    ss->disconnectFromHost();
    delete ss;
    ss = NULL;
    newSetting = true;
    MakeConnection();
  }
}

void Stars::ReadStarsKeys( QString SelectedName, QString DefaultName )
{
  bool FileOK = false;

  qDebug() << "key file names " << SelectedName << DefaultName;

  MyNameOnStars = DefaultName;

  QFile file;
  if ( SelectedName != "" ) {
    file.setFileName( SelectedName + ".key" );
    if ( file.open( QIODevice::ReadOnly ) ) {
      FileOK = true;
    } else {
      qDebug() << tr( "Cannot open [%1.key]" ).arg( SelectedName );
    }
  }

  if ( ! FileOK ) {
    file.setFileName( ":" + DefaultName + ".key" );
    if ( !file.open( QIODevice::ReadOnly ) ) {
      qDebug() << tr( "Cannot open both [%1.key] and [:%2.key]" )
                  .arg( SelectedName ).arg( DefaultName );
      exit(1);
    }
  }

  QString item;
  QTextStream in( &file );

  while( !in.atEnd() ) {
    in >> item;
    if ( !item.isEmpty() ) {
      keys << item;
    }
  }

  MaxKeys = 0;
  foreach( QString i, keys ) {
    MaxKeys++;
  }

  file.close();
}

QString Stars::GetKey( int nkey )
{
  int key = ( nkey - ((int)( nkey / MaxKeys )) * MaxKeys );
  return keys[ key ];
}

void Stars::ReConnect( void )
{
  if ( ss != NULL ) {
    ss->disconnectFromHost();
    delete ss;
    ss = NULL;
    newSetting = true;
    MakeConnection();
  }

  emit ReConnected();
}

/** サーバとの接続 **/
/********************/

/************************/
/** 低レベルの通信関数 **/

void Stars::MakeConnection( void )
{
  if ( ( ss == NULL ) || ( ss->state() != QAbstractSocket::ConnectedState ) ){
    if ( newSetting == true ) {  // 同じアドレス設定での接続試行は一回だけ
      newSetting = false;
      if ( ss == NULL )
        ss = new QTcpSocket;

      emit AskRecord( tr( "Connecting Stars Server [%1] [%2] as [%3]" )
                      .arg( StarsServer ).arg( StarsSPort ).arg( MyNameOnStars ) );
      ConnectionStage = 0;
      connect( ss, SIGNAL( readyRead( void ) ), this, SLOT( ReceiveMessageFromStars( void ) ), Qt::UniqueConnection );
      ss->connectToHost( StarsServer, StarsSPort );
    }
  }
}

void Stars::ReceiveMessageFromStars( void )
{
  SMsg smsg;
  QByteArray RBuf;
  QString WBuf;

  switch( ConnectionStage ) {
  case 0:
    RBuf = ss->readLine( 4000 );
    RBuf = RBuf.simplified();
    WBuf = tr( "%1 %2\n" ).arg( MyNameOnStars ).arg( GetKey( RBuf.toInt() ) );
    ConnectionStage = 1;
    ss->write( WBuf.toLatin1() );
    break;
  case 1:
    while( ss->canReadLine() )
      RBuf = ss->readLine( 4000 );
    ConnectionStage = 2;
    emit AskRecord( tr( "Success to connect." ) );
    emit ConnectionIsReady( this );
    break;
  case 2:
    while( ss->canReadLine() ) {
      RBuf = ss->readLine( 4000 );
      RBuf = RBuf.simplified();
      switch( smsg.ParseMsg( RBuf ) ) {
      case RES_MSG:
        switch( smsg.Msgt() ) {
        case ISBUSY:
          emit AskIsBusy( smsg ); break;
        case GETVALUE:
          emit AskGetValue( smsg ); break;
        case SETVALUE:
          emit AskSetValue( smsg ); break;
        case SETVALUEREL:
          emit AskSetValueREL( smsg ); break;
        case GETSPEEDSELECTED:
          emit AskGetSpeedSelected( smsg ); break;
        case SPEEDHIGH:
          emit AskSpeedHigh( smsg ); break;
        case SPEEDMIDDLE:
          emit AskSpeedMiddle( smsg ); break;
        case SPEEDLOW:
          emit AskSpeedLow( smsg ); break;
	case STOP:
	  emit AskStop( smsg ); break;
	case REMOTE:
	  emit AskRemote( smsg ); break;
	case STOPEMERGENCY:
	  emit AskStopEmergency( smsg ); break;
	case STANDBY:
	  emit AskStandby( smsg ); break;
	case SYNCRUN:
	  emit AskSyncRun( smsg ); break;
	case SETHIGHSPEED:
	case SETMIDDLESPEED:
	case SETLOWSPEED:
	  emit AskSetSpeed( smsg ); break;

        default:
          SendAns( MyNameOnStars, smsg.From(), "Er: Undefined Command" );
          break;
        }
        break;
      case RES_EVENT:
        emit AskRecord( tr( "Receive an event from Stars [%1]" ).arg( RBuf.data() ) );
        switch( smsg.Msgt() ) {
#if 0
        case EvCHANGEDVALUE:
          emit EvChangedValue( smsg ); break;
        case EvISBUSY:
          emit EvIsBusy( smsg ); break;
#endif
        default:
          SendAns( MyNameOnStars, smsg.From(), "Er: Undefined Command" );
          break;
        }
        break;
      default:
        SendAns( MyNameOnStars, smsg.From(), "Er: Undefined Command" );
        emit AskRecord( tr( "Receive an unrecognized message from Stars [%1]" )
                        .arg( RBuf.data() ) );
      }
    }
  }
}

void Stars::SendAns( QString from, QString to, QString msg )
{
  QString aLine = from + ">" + to + " " + msg + "\n";
  emit AskRecord( tr( "Sending an answer [%1] to Stars" ).arg( aLine ) );
  ss->write( aLine.toLatin1() );
}

void Stars::SendEvent( QString from, QString msg )
{
  QString aLine = from + ">System " + msg +"\n";
  emit AskRecord( tr( "Sending an Event [%1] to Stars" ).arg( aLine ) );
  ss->write( aLine.toLatin1() );
}

bool Stars::SendCMD( QString dev, QString cmd1, QString cmd2 )
{
  QString Cmd = dev + " " + cmd1;
  if ( !cmd2.isEmpty() )
    Cmd += " " + cmd2;
  Cmd += "\n";

  emit AskRecord( tr( "Sending a message [%1] to Stars" ).arg( Cmd ) );
  ss->write( Cmd.toLatin1() );

  return true;
}

bool Stars::SendCMD2( QString fromCh, QString dev, QString cmd1, QString cmd2 )
{
  QString Cmd = MyNameOnStars + "." + fromCh + ">" + dev + " " + cmd1;
  if ( !cmd2.isEmpty() )
    Cmd += " " + cmd2;
  Cmd += "\n";

  emit AskRecord( tr( "Sending a message [%1] to Stars" ).arg( Cmd ) );
  ss->write( Cmd.toLatin1() );

  return true;
}

