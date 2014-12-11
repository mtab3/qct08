#include "Body.h"

void Body::AnsIsBusy( SMsg msg )
{
  s->SendAns( msg.To(), msg.From(),
	      QString( "@%1 %2" ).arg( msg.Msg() ).arg( busy ? 1 : 0 ) );
}

void Body::AnsGetValue( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg.To(), msg.From(), "@GetValue Er:" );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];
    QString cmd = QString( "CTR?%1" ).arg( ch, 2, 10, QChar( '0' ) );
    CT->SendCMD( msg, cmd );
  }
}

void Body::AnsReset( SMsg msg )
{
  CT->SendCMD( msg, "CLAL" );
  s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // 返答を待たず Ok:
}

void Body::AnsQInitialize( SMsg msg )
{
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];

    CT->SendCMD( msg, "CLAL" );        // 全チャンネルデータクリア
    CT->SendCMD( msg, "GATEIN_EN" );   // default でこれになってるはず。念の為
    


    
    
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];




    
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Body::AnsQFinalize( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];










    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}



void Body::ParseAns( SMsg smsg, CTMsg ctmsg )
{
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
