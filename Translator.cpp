#include "MainWindow.h"

#if 0
void Main::AnsIsBusy( SMsg msg )
{
  CT->SendCMD( msg, "Busy ?" );
}
#endif

#if 0
void Main::AnsGetValue( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg.To(), msg.From(), "@GetValue Er:" );
  } else {
    CT->SendCMD( msg, "get value" );
  }
}
#endif

void MainWindow::AnsReset( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
  }
}

void Main::AnsQInitialize( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];




    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Main::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];




    
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Main::AnsQFinalize( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];










    A->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}



void Main::ParseAns( SMsg smsg, CTMsg ctmsg )
{
  if ( ctmsg.cmd() == "MPI" ) {// MPI ���б����륢��������̵��
    return;
  }

  QString ans = QString( "@%1 " ).arg( smsg.Msg() );
#if 0
  if ( amsg.stat() == QString( "E" ) ) {  // ARIES ����������ϥ��顼���ä�
    if ( smsg.Msgt() != NOTMSG ) {
      s->SendCMD( smsg.From(), ans + "Er:" );
    }
  } else {                    // ARIES ��������������ｪλ���ä�
    switch( smsg.Msgt() ) {
      // �ͤ��֤����������
    case ISBUSY:
    case GETVALUE:
      s->SendAns( smsg.To(), smsg.From(), QString( "%1%2" ).arg( ans ).arg( amsg.val() ) );
      break;

      // Ok: ���֤����������
    case STOP:
    case STOPEMERGENCY:
    case SETHIGHSPEED:
    case SETMIDDLESPEED:
    case SETLOWSPEED:
      s->SendAns( smsg.To(), smsg.From(), QString( "%1Ok:" ).arg( ans ) );
      break;

      // �����Ϥ��Ǥ˽���äƤ��ơ��ӥ����Υե饰��Ϥ�������������
    case SETVALUE:
    case SETVALUEREL:
      s->SendEvent( smsg.To(), QString( "_ChangedIsBusy 0" ) );
      break;

      // �����Ϥ��Ǥ˽���äƤ��ơ��ӥ����ե饰��Ϥ�������������Ϣ��������ͥ����������Τ��ʤ��Ȥ����ʤ�
    case SYNCRUN:
      for ( int i = 0; i < StandbyAxes; i++ ) {
        s->SendEvent( QString( "%1.%2" ).arg(smsg.ToDev()).arg(AxNum2Name[StandbyTable[i].ax]),
            "_ChangedIsBusy 0" );
      }
      SyncRunning = false;
      break;

      // �ʲ��Υ��ޥ�ɤ� ARIES ���̿������˴��뤷�Ƥ���
    case GETSPEEDSELECTED:
    case SPEEDHIGH:
    case SPEEDMIDDLE:
    case SPEEDLOW:
    case REMOTE:
    case STANDBY:
      break;

      // �ʲ��Υ�å�������������ȯ���������Τ� Stars �������ʤ�
    case INTERNALMSG:
      s->SendEvent( smsg.To(), QString( "_ChangedValue %1" ).arg( amsg.val() ) );
      break;
    case INARIES:
    case NOTMSG:
      break;
  //default: // �����ơ�default ��ʤ����ƥ��顼�����å��򸷤�������
    }
  }
#endif
}
