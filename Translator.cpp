#include "Body.h"

void Body::AnsIsBusy( SMsg msg )
{
  smsg = msg;
  s->SendAns( msg,
	      QString( "@%1 %2" ).arg( msg.Msg() ).arg( CT->isBusy() ? 1 : 0 ) );
}

void Body::changedCTIsBusy( bool busy )
{
  qDebug() << Config[ "NAME_ON_STARS" ] << QString( "_ChangedIsBusy %1" ).arg( busy ? 1 : 0 );
  s->SendEvent( Config[ "NAME_ON_STARS" ], QString( "_ChangedIsBusy %1" ).arg( busy ? 1 : 0 ) );
}

void Body::AnsReset( SMsg msg )
{
  initialized = false;
  gotData = false;
  finalized = false;

  smsg = msg;
  CT->QueCmd( false, "STOP" );
  CT->QueCmd( false, "CLAL" );
  CT->QueCmd( false, "GATEIN_EN" );   // default でこれになってるはず。念の為

  disconnect( CT, SIGNAL( received( CTMsg ) ) );
  CT->SendCmd();
  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // 返答を待たず Ok:
}

void Body::AnsGetValue( SMsg msg )
{
  smsg = msg;
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, "@GetValue Er:" );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];
    QString cmd = QString( "CTR?%1" ).arg( ch, 2, 10, QChar( '0' ) );
    CT->QueCmd( false, cmd );
    
    recSeq = 0;
    connect( CT, SIGNAL( received( CTMsg ) ), this, SLOT( ansGetValue( CTMsg ) ) );
    CT->SendCmd();
  }
}


void Body::simpleSend( QString cmd, SMsg msg )
{
  smsg = msg;
  CT->QueCmd( false, cmd );

  recSeq = 0;
  disconnect( CT, SIGNAL( received( CTMsg ) ) );
  CT->SendCmd();
  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // 返答を待たず Ok:
}

void Body::AnsSetTimerPreset( SMsg msg )
{
  QString cmd = QString( "STPRF%1" ).arg( msg.Val() );
  simpleSend( cmd, msg );
}

void Body::AnsCounterReset( SMsg msg )
{
  simpleSend( "CLAL", msg );
}

void Body::AnsCountStart( SMsg msg )
{
  simpleSend( "STRT", msg );
};

void Body::AnsSetStopMode( SMsg msg )
{
  QString cmd = "";
  if ( msg.Val() == "N" )
    cmd = "DSAS";
  if ( msg.Val() == "T" )
    cmd = "ENTS";
  if ( msg.Val() == "C" )
    cmd = "ENCS";

  if ( cmd == "" ) {
    s->SendAns( msg, "@SetStopMode Er:" );
  } else {
    simpleSend( cmd, msg );
  }
}

void Body::AnsStop( SMsg msg )
{
  simpleSend( "STOP", msg );
}

void Body::AnsQInitialize( SMsg msg )
{
  smsg = msg;
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! initialized ) {          // 連続で何回も呼ばれても先頭の一回だけ
      CT->QueCmd( false, "STOP" );        // カウントしてても止める
      CT->QueCmd( false, "CLGSDN" );      // データ記録番地 0 にセット
      // CT->SendCMD( "GSED9999" ); // データ記録最終番地(ここまで来ると収集は止まる)
      CT->QueCmd( false, "GT_ACQ_DIF" );  // カウントの差分を記録
      CT->QueCmd( false, "GESTRT" );      // ゲートエッジデータ収集モード
                                    // 最初のゲート立ち上がりでカウントクリア
                                    // 以降のゲート立ち上がりでカウント記録
      initialized = true;
      gotData = false;
      finalized = false;

      disconnect( CT, SIGNAL( received( CTMsg ) ) );
      CT->SendCmd();
    }
    
    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate の Hの時間とLの時間の合計は最低 1ms 必要 !!

void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! gotData ) {         // 連続で何回も呼ばれても先頭の一回だけ
      CT->QueCmd( false, "STOP" );   // とにかく停止
      CT->QueCmd( true, "GSDN?" );  // 現在データ番号の読み取り
      CT->QueCmd( true, "GSDAL?" ); // 現在データ番号までのデータ読み取り
                               // 各行に全チャンネル+カウンタの値がカンマ区切りで並び
                               // 現在データ番号分の行数が来る
      initialized = false;
      gotData = true;
      finalized = false;

      recSeq = 0;
      disconnect( CT, SIGNAL( received( CTMsg ) ) );
      connect( CT, SIGNAL( received() ), this, SLOT( ansGetData() ) );
      CT->SendCmd();
    };
    
    //    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Body::AnsQFinalize( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! finalized ) {        // 連続で何回も呼ばれても先頭の一回だけ
      CT->QueCmd( false, "STOP" );    // とにかく止めておく
      
      initialized = false;
      gotData = false;
      finalized = true;

      disconnect( CT, SIGNAL( received( CTMsg ) ) );
      CT->SendCmd();
    }

    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}

void Body::ansGetValue( CTMsg msg )
{
  // recSeq に従って動作をすすめる (GetValue は 1step)
  disconnect( CT, SIGNAL( received( CTMsg ) ), this, SLOT( ansGetValue( CTMsg ) ) );
  s->SendAns( smsg, QString( "@GetValue %1" ).arg( msg.msg().toInt() ) );
}

void Body::ansGetData( void )
{
  // recSeq に従って動作をすすめる (GetData は 2step)
  s->SendAns( smsg, QString( "@qGetData %1" ).arg( msg.msg().toInt() ) );
}





