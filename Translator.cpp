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
    CT->SendCMD( cmd );
  }
}

void Body::AnsReset( SMsg msg )
{
  initialized = false;
  busy = false;
  CT->SendCMD( "STOP" );
  CT->SendCMD( "CLAL" );
  CT->SendCMD( "GATEIN_EN" );   // default でこれになってるはず。念の為
  s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // 返答を待たず Ok:
}

void Body::AnsQInitialize( SMsg msg )
{
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! initialized ) {        // 連続で何回も呼ばれても先頭の一回だけ
      CT->SendCMD( "CLAL" );        // 全チャンネルデータクリア
      CT->SendCMD( "START" );
      initialized = true;
    }
    
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

    if ( initialized ) {        // 連続で何回も呼ばれても先頭の一回だけ
      CT->SendCMD( "STOP" );
      initialized = false;
    }

    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}
