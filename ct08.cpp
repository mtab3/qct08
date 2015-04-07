#include <strings.h>
#include "ct08.h"

CT08::CT08( void )
{
  CTIP = "192.168.51.204";
  CTPORT = "7777";
  ss = NULL;

  busy = false;
  blocking = false;
  emit changedIsBusy( busy );

  cmdq.clear();
  RBuf[0] = '\0';

  Connected = false;
  t = new QTimer;
  t->setInterval( 50 );
  connect( t, SIGNAL( timeout() ), this, SLOT( watch() ), Qt::UniqueConnection );
  //  t->start();
}

CT08::~CT08( void )
{
  if ( ss != NULL )
    ss->close();
}

void CT08::Connect( QString ip, QString port )
{
  CTIP = ip;
  CTPORT = port;
  if ( ss == NULL ) {
    ss = new QTcpSocket;
    connect( ss, SIGNAL( readyRead() ), this, SLOT( RcvMessage() ), Qt::UniqueConnection );
    ss->connectToHost( CTIP, CTPORT.toInt() );
    Connected = true;
    //    t->start();
  }
}

void CT08::RcvMessage( void )
{
  while( ! ss->atEnd() ) {
    ss->readLine( rBuf, BUFSIZE );
    strcat( RBuf, rBuf );
    char *p = strchr( RBuf, '\x0d' );
    //    qDebug() << "read size " << strlen( RBuf );
    
    // \r\n を見て、一区切りの通信メッセージであると判断
    if ( ( p != NULL ) && ( *(p+1) == '\x0a' ) ) {
      // 制御文字等を消す簡単な整形
      *p = '\0';
      p = RBuf;
      while( *p != '\0' ) {
	if ( *p < ' ' )
	  *p = ' ';
	p++;
      }
      
      if ( strncmp( RBuf, "flag2 = ", 8 ) == 0 ) {
	qDebug() << "RBuf" << RBuf << busy;
	if ( QString( RBuf ).mid( 8, 2 ).toInt( 0, 16 ) & 0x20 ) {
	  if ( ! busy ) {
	    busy = true;
	    emit changedIsBusy( busy );
	  }
	} else {
	  if ( busy ) {
	    busy = false;
	    emit changedIsBusy( busy );
	    t->stop();
	  }
	}
      } else {
	CTMsg ctmsg;
	ctmsg.ParseMsg( QString( RBuf ) );
	//	qDebug() << "Before Emitt!! Receive" << RBuf;
	RBuf[0] = '\0';
	emit received( ctmsg, sMsg );
      }
    }
  }
}

void CT08::QueCmd( QString cmd, int size, SMsg msg,
		   QObject *from, const char *signal,
		   QObject *to,   const char *slot )
{
  aQue *que = new aQue;
  que->cmd = cmd;
  que->size = size;
  que->msg = msg;
  que->from = from;
  if ( signal != NULL )
    que->signal = strdup( signal );
  else
    que->signal = NULL;
  que->to = to;
  if ( slot != NULL )
    que->slot = strdup( slot );
  else
    que->slot = NULL;

  cmdq << que;
  qDebug() << "qued " << cmdq.count();
}

void CT08::SendCmd( void )
{
  qDebug() << "in SendCmd";
  if ( blocking ) {
    qDebug() << "Blocked";
    return;
  }
  qDebug() << "rest of que " << cmdq.count();
  if ( cmdq.count() > 0 ) {
    qDebug() << "Send" << cmdq[0]->cmd;
    if ( cmdq[0]->from != NULL ) {
      connect( cmdq[0]->from, cmdq[0]->signal, cmdq[0]->to, cmdq[0]->slot );
    }
    if ( cmdq[0]->signal != NULL ) free( cmdq[0]->signal );
    if ( cmdq[0]->slot != NULL ) free( cmdq[0]->slot );

    if ( cmdq[0]->cmd == "STRT" ) {
      busy = true;
      emit changedIsBusy( busy );
      t->start();
    }
    blocking = true;
    sMsg = cmdq[0]->msg;
    QByteArray Cmd = cmdq[0]->cmd.toLatin1() + "\x0d\x0a\0";
    ss->write( Cmd.data() );
    RBuf[0] = '\0';
    cmdq.remove( 0 );
  }
}

void CT08::SendACmd( QString cmd )
{
  qDebug() << "Send Single" << cmd;
  QByteArray Cmd = cmd.toLatin1() + "\x0d\x0a\0";
  ss->write( Cmd.data() );

  if ( cmd == "STRT" ) {
    busy = true;
    emit changedIsBusy( busy );
    t->start();
  }
}

QString CT08::SendAndRead( QString cmd, int size )
{
  qDebug() << "disConnect";
  disconnect( ss, SIGNAL( readyRead() ),
	      this, SLOT( RcvMessage() ) );

  qDebug() << "Send and Read" << cmd;
  QByteArray Cmd = cmd.toLatin1() + "\x0d\x0a\0";
  ss->write( Cmd.data() );
  ss->waitForReadyRead();
  while( ss->bytesAvailable() < size ) { ss->waitForReadyRead(); };
  QByteArray rbuf;
  rbuf.resize( ss->bytesAvailable() );
  ss->read( rbuf.data(), ss->bytesAvailable() );

  connect( ss, SIGNAL( readyRead() ),
	   this, SLOT( RcvMessage() ), Qt::UniqueConnection );

  return QString( rbuf.data() );
}

void CT08::watch( void )
{
  QByteArray Cmd = QString( "FLG?2" ).toLatin1() + "\x0d\x0a\0";
  ss->write( Cmd.data() );
  RBuf[0] = '\0';
  qDebug() << "Send Watch cmd";
}



