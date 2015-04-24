#include <strings.h>
#include "ct08.h"

CT08::CT08( void )
{
  CTIP = "192.168.51.204";
  CTPORT = "7777";
  ss = NULL;

  busy = false;
  emit changedIsBusy( busy );

  RBuf[0] = '\0';

  Connected = false;
  t = new QTimer;
  t->setInterval( 50 );
  connect( t, SIGNAL( timeout() ), this, SLOT( watch() ), Qt::UniqueConnection );
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
    ss->connectToHost( CTIP, CTPORT.toInt() );
    Connected = true;

    SendACmd( "STOP" );
    SendACmd( "CLAL" );
    SendACmd( "CLGSDN" );     // データ記録番地 0 にセット
    SendACmd( "GATEIN_DS" );
  }
}

void CT08::SendACmd( QString cmd )
{
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
  SendACmd( cmd );
  ss->waitForReadyRead();
  while( ss->bytesAvailable() < size ) { ss->waitForReadyRead(); };
  QByteArray rbuf;
  rbuf.resize( ss->bytesAvailable() );
  ss->read( rbuf.data(), ss->bytesAvailable() );

  return QString( rbuf.data() );
}

void CT08::QGetData( int ch, int num, QStringList &data )
{
  data.clear();
  bool Reading = true;
  QString cmd = QString( "GSCRDX?%1%2%3%4%5" )
    .arg( ch,     2, 10, QChar( '0' ) )
    .arg( ch,     2, 10, QChar( '0' ) )
    .arg( (int)0, 2, 10, QChar( '0' ) )
    .arg( (int)0, 4, 10, QChar( '0' ) )
    .arg( num,    4, 10, QChar( '0' ) );
  SendACmd( cmd );
  ss->waitForReadyRead();
  while ( Reading ) {
    while ( ! ss->atEnd() ) {
      QString rbuf = ss->readLine();
      if ( rbuf.mid( 0, 3 ) == "EOF" ) {
	Reading = false;
	break;
      }
      data << QString( rbuf );
    }
    if ( Reading ) {
      ss->waitForReadyRead();
    }
  }
}

void CT08::watch( void )
{
  QString RBuf = SendAndRead( "FLG?2", 2 );
  if ( RBuf.mid( 8, 2 ).toInt( 0, 16 ) & 0x20 ) {
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
}



