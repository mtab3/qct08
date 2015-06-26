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
    SendACmd( "ENTS" );
    SendACmd( "CLGSDN" );     // データ記録番地 0 にセット
    SendACmd( "GATEIN_DS" );
    busy = false;
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

  qDebug() << "S&R" << cmd << rbuf;
  return QString( rbuf.data() );
}

// counter -- 8byte + ' ,' + timer -- 8byte + CRLF
#define DATALEN    ( 8 + 2 + 8 + 2 )

#include <stdio.h>

void CT08::clearBuffer( void )
{
  ss->waitForReadyRead( 10 );
  if ( ss->bytesAvailable() > 0 ) {
    ss->read( ss->bytesAvailable() );
  }
}

void CT08::QGetData( int ch, int num, QVector<double> &data )
{
  int cnt = 0;
  data.clear();

  //  QString cmd = QString( "GSCRDX?%1%2%3%4%5" )
  QString cmd = QString( "GSCRDXH?%1%2%3%4%5" )
    .arg( ch,     2, 10, QChar( '0' ) )     // 指定チャンネル (ch) から
    .arg( ch,     2, 10, QChar( '0' ) )     // 指定チャンネル (ch) までの、要は ch だけの
    .arg( (int)1, 2, 10, QChar( '0' ) )     // タイマーも読み出して(0:w/o, 1:w timer)
    .arg( (int)0, 4, 10, QChar( '0' ) )     // 0 番目から
    .arg( num,    4, 10, QChar( '0' ) );    // num 番目までのデータを読みだす
  SendACmd( cmd );
  ss->waitForReadyRead();
  int len = DATALEN * num + 5;
  qDebug() << "len " << len;
  while( ss->bytesAvailable() < len ) { ss->waitForReadyRead(); }
  QString Rbuf = ss->read( ss->bytesAvailable() );
  qDebug() << "bytes" << ss->bytesAvailable() << Rbuf.size();
  double time0 = 0;
  double time = 0;
  while( Rbuf.size() >= DATALEN ) {
    QString rbuf = Rbuf.mid( 0, DATALEN );
    Rbuf = Rbuf.mid( DATALEN );
    QStringList vals = QString( rbuf ).simplified().remove( ' ' ).split( ',' );
    if ( vals.count() == 2 ) {
      time = (double)vals[1].toInt( NULL, 16 ) / 1e6;
      data << (double)vals[0].toInt( NULL, 16 ) / ( time - time0 );
      time0 = time;
      if (( cnt == 0 )||( cnt == 1 )||( cnt > num -2 ))
	qDebug() << "time" << ch << cnt << num << time << data[ data.count() - 1 ]
		 << "vals : " << QString( rbuf ).simplified();
      cnt++;
    }
  }
  qDebug() << "time" << ch << cnt << num << time << data[ data.count() - 1 ];
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



