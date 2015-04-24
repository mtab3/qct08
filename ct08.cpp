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
  qDebug() << "in Send a cmd " << cmd;
  QByteArray Cmd = cmd.toLatin1() + "\x0d\x0a\0";
  ss->write( Cmd.data() );

  if ( cmd == "STRT" ) {
    busy = true;
    emit changedIsBusy( busy );
    t->start();
  }
  qDebug() << "out Send a cmd ";
}

QString CT08::SendAndRead( QString cmd, int size )
{
  qDebug() << "in Send and read" << cmd;
  SendACmd( cmd );
  ss->waitForReadyRead();
  while( ss->bytesAvailable() < size ) { ss->waitForReadyRead(); };
  QByteArray rbuf;
  rbuf.resize( ss->bytesAvailable() );
  ss->read( rbuf.data(), ss->bytesAvailable() );

  qDebug() << "out Send and read";
  return QString( rbuf.data() );
}

void CT08::QGetData( QStringList &data )
{
  qDebug() << "in qGetData";
  data.clear();
  bool Reading = true;
   SendACmd( "GSDAL?" );
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
  qDebug() << "out qGetData";
}

void CT08::watch( void )
{
  qDebug() << "in watch";
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
  qDebug() << "out watch";
}



