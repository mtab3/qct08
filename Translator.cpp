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
  gotData = false;
  finalized = false;
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

    if ( ! initialized ) {          // 連続で何回も呼ばれても先頭の一回だけ
      CT->SendCMD( "STOP" );        // カウントしてても止める
      CT->SendCMD( "CLGSDN" );      // データ記録番地 0 にセット
      // CT->SendCMD( "GSED9999" ); // データ記録最終番地(ここまで来ると収集は止まる)
      CT->SendCMD( "GT_ACQ_DIF" );  // カウントの差分を記録
      CT->SendCMD( "GESTRT" );      // ゲートエッジデータ収集モード
                                    // 最初のゲート立ち上がりでカウントクリア
                                    // 以降のゲート立ち上がりでカウント記録
      initialized = true;
      gotData = false;
      finalized = false;
    }
    
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate の Hの時間とLの時間の合計は最低 1ms 必要 !!

void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! gotData ) {         // 連続で何回も呼ばれても先頭の一回だけ
      CT->SendCMD( "STOP" );   // とにかく停止
      CT->SendCMD( "GSDN?" );  // 現在データ番号の読み取り
      CT->SendCMD( "GSDAL?" ); // 現在データ番号までのデータ読み取り
                               // 各行に全チャンネル+カウンタの値がカンマ区切りで並び
                               // 現在データ番号分の行数が来る
      initialized = false;
      gotData = true;
      finalized = false;
    };
    
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Body::AnsQFinalize( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! finalized ) {        // 連続で何回も呼ばれても先頭の一回だけ
      CT->SendCMD( "STOP" );    // とにかく止めておく
      initialized = false;
      gotData = false;
      finalized = true;
    }

    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}
