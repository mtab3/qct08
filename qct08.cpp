
#include "qct08.h"

CT08::CT08( void )
{
  CTIP = "192.168.1.1";
  CTPORT = "4001";
  ss = NULL;

  RBuf[0] = '\0';

  Connected = false;
  Waiting = false;
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
    connect( ss, SIGNAL( readyRead( void ) ), this, SLOT( RcvMessage( void ) ), Qt::UniqueConnection );
    ss->connectToHost( CTIP, CTPORT.toInt() );
    Connected = true;
  }
}

void CT08::RcvMessage( void )
{
  ss->readLine( rBuf, BUFSIZE );
  strcat( RBuf, rBuf );
  char *p = strchr( RBuf, '\x0d' );

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

    aQue q;
    if ( WaitingAnsQ.count() > 0 ) {
      q = WaitingAnsQ[0];
      WaitingAnsQ.removeAt(0);
    };

    CTMsg ctmsg;
    ctmsg.ParseMsg( QString( RBuf ) );
    RBuf[0] = '\0';
    emit NewMsg( q.smsg, ctmsg );

    Waiting = false;
  }
}

void CT08::SendCMD( SMsg msg, QString cmd )
{
  if ( ! Connected )
    return;

  aQue q;
  q.smsg = msg;
  q.cmd = cmd;
  BeforeThrowQ << q;

  SendCMD0();
}

void CT08::SendCMD0( void )
{
  if ( Waiting )
    return;

  if ( BeforeThrowQ.count() > 0 ) {
    Waiting = true;
    aQue q = BeforeThrowQ.dequeue();
    WaitingAnsQ << q;

    QByteArray cmd = q.cmd.toLatin1() + "\x0d\x0a\0";
    ss->write( cmd.data() );
    RBuf[0] = '\0';
  }
}
