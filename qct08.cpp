
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

void CT08::SetChNames( QMap<int,QString> num2name, QMap<QString,int> name2num )
{
  Num2Name = num2name;
  Name2Num = name2num;
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

void CT08::SendCMD( SMsg msg, QString cmd0, QString params )
{
  if ( ! Connected )
    return;

  aQue q;
  q.smsg = msg;
  q.cmd = cmd0;
  q.params = params;
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

    QByteArray cmd = "\x02" + q.cmd.toLatin1() + q.params.toLatin1() + "\x0d\x0a\0";
    ss->write( cmd.data() );
    RBuf[0] = '\0';
  }
}

void CT08::RcvMessage( void )
{
#if 0
  ss->readLine( rBuf, BUFSIZE );
  strcat( RBuf, rBuf );
  char *p = strchr( RBuf, '\x0d' );

  if ( ( p != NULL ) && ( *(p+1) == '\x0a' ) ) {
    // ������ \r\n �����āA���؂�̒ʐM���b�Z�[�W�ł���Ɣ��f
    *p = '\0';
    p = RBuf;
    while( *p != '\0' ) {
      if ( *p < ' ' )
        *p = ' ';
      p++;
    }
    // ���䕶�����������ȒP�Ȑ��`����������
    // �p�[�X���Ă��� ( amsg )
    AMsg amsg;
    amsg.ParseMsg( QString( RBuf ) );
    RBuf[0] = '\0';

    // ���ʑ҂��̃L���[�̒��ɁA�����Ă������b�Z�[�W��҂��Ă���
    // ���̂����邩�ǂ����T��
    int i;
    for ( i = WaitingAnsQ.count() - 1; i >= 0; i-- ) {
      if ( WaitingAnsQ[i].cmd == amsg.cmd0() ) {
        break;
      }
    }
    if ( i >= 0 ) {
      aQue q = WaitingAnsQ[i];
      WaitingAnsQ.removeAt(i);
      // �󂯂Ƃ������b�Z�[�W���A�^�C�}�[�𔭓����Ă��郁�b�Z�[�W��������K���Ɏ~�߂�
      WatchTimerStop( q );
      if ( q.smsg.Msgt() != INARIES ) {     // INARIES �̏ꍇ��
        emit NewMsg( q.smsg, amsg );
      } else {
        Parse( amsg );   // �O���ɓn�����Ɏ��O�ŏ�������
      }
    }
    Waiting = false;
    if ( BeforeThrowQ.count() > 0 ) {
      SendCMD0();
    }
  }
#endif
}

void CT08::Parse( AMsg msg )
{
#if 0
  if ( msg.cmd() == "RTB" ) {
    int ax = msg.ax().toInt();
    int n = msg.vals()[0].toInt();
    vTable *t = &(vTables[ ax ][ n ]);
    QStringList vals = msg.vals();
    t->ax = ax;
    t->vNo = n;
    t->start_v = vals[1].toInt();
    t->max_v = vals[2].toInt();
    t->acc_time = vals[3].toInt();
    t->dec_time = vals[4].toInt();
    t->acc_mode = vals[5].toInt();
    t->acc_pulse = vals[6].toInt();
    t->dec_pulse = vals[7].toInt();
  }
#endif
}
