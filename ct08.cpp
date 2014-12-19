
#include "ct08.h"

CT08::CT08( void )
{
  CTIP = "192.168.51.204";
  CTPORT = "7777";
  ss = NULL;

  cmdq.clear();
  RBuf[0] = '\0';

  Connected = false;
  t = new QTimer;
  t->setInterval( 100 );
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
    connect( ss, SIGNAL( readyRead( void ) ),
	     this, SLOT( RcvMessage( void ) ), Qt::UniqueConnection );
    ss->connectToHost( CTIP, CTPORT.toInt() );
    Connected = true;
    t->start();
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

    CTMsg ctmsg;
    ctmsg.ParseMsg( QString( RBuf ) );
    RBuf[0] = '\0';
    emit received( ctmsg );
  }
}

void CT08::QueCmd( bool waitf, QString cmd )
{
  aQue *que = new aQue;
  que->cmd = cmd;
  que->waitf = waitf;

  cmdq << que;
}

void CT08::SendCmd( void )
{
  // タイマーをかけて コマンド送信のサブファンクションを呼ぶ
  // 先頭が % のコマンドは応答を待つ、# は応答を待たない
  while( cmdq.count() > 0 ) {

    QByteArray Cmd = cmdq[0]->cmd.toLatin1() + "\x0d\x0a\0";
    ss->write( Cmd.data() );
    RBuf[0] = '\0';

    cmdq.remove( 0 );
  }
}

void CT08::watch( void )
{
}



