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
  if ( ctmsg.cmd() == "MPI" ) {// MPI に対応するアクションは無い
    return;
  }

  QString ans = QString( "@%1 " ).arg( smsg.Msg() );
#if 0
  if ( amsg.stat() == QString( "E" ) ) {  // ARIES からの返答はエラーだった
    if ( smsg.Msgt() != NOTMSG ) {
      s->SendCMD( smsg.From(), ans + "Er:" );
    }
  } else {                    // ARIES からの返答は正常終了だった
    switch( smsg.Msgt() ) {
      // 値を返す定形の返答
    case ISBUSY:
    case GETVALUE:
      s->SendAns( smsg.To(), smsg.From(), QString( "%1%2" ).arg( ans ).arg( amsg.val() ) );
      break;

      // Ok: を返す定形の返答
    case STOP:
    case STOPEMERGENCY:
    case SETHIGHSPEED:
    case SETMIDDLESPEED:
    case SETLOWSPEED:
      s->SendAns( smsg.To(), smsg.From(), QString( "%1Ok:" ).arg( ans ) );
      break;

      // 返答はすでに終わっていて、ビジーのフラグをはずすだけの返答
    case SETVALUE:
    case SETVALUEREL:
      s->SendEvent( smsg.To(), QString( "_ChangedIsBusy 0" ) );
      break;

      // 返答はすでに終わっていて、ビジーフラグをはずだけだが、関連するチャンネル全部に通知しないといけない
    case SYNCRUN:
      for ( int i = 0; i < StandbyAxes; i++ ) {
        s->SendEvent( QString( "%1.%2" ).arg(smsg.ToDev()).arg(AxNum2Name[StandbyTable[i].ax]),
            "_ChangedIsBusy 0" );
      }
      SyncRunning = false;
      break;

      // 以下のコマンドは ARIES と通信せずに完結している
    case GETSPEEDSELECTED:
    case SPEEDHIGH:
    case SPEEDMIDDLE:
    case SPEEDLOW:
    case REMOTE:
    case STANDBY:
      break;

      // 以下のメッセージは内部で発生させるもので Stars からは来ない
    case INTERNALMSG:
      s->SendEvent( smsg.To(), QString( "_ChangedValue %1" ).arg( amsg.val() ) );
      break;
    case INARIES:
    case NOTMSG:
      break;
  //default: // あえて、default をなくしてエラーチェックを厳しくする
    }
  }
#endif
}
