#include "Body.h"

void Body::AnsIsBusy( SMsg msg )
{
  s->SendAns( msg,
	      QString( "@%1 %2" ).arg( msg.Msg() ).arg( CT->isBusy() ? 1 : 0 ) );
}

void Body::changedCTIsBusy( bool busy )
{
  s->SendEvent( Config[ "NAME_ON_STARS" ],
		QString( "_ChangedIsBusy %1" ).arg( busy ? 1 : 0 ) );
}

void Body::AnsReset( SMsg msg )  // QXAFS 
{
  initialized = false;
  gotData = false;
  finalized = false;

  //  CT->SendACmd( "REST" );
  //  CT->SendACmd( "STOP" );
  CT->SendACmd( "CLAL" );
  CT->SendACmd( StopModeCMD );
  //  CT->SendACmd( "GATEIN_EN" );   // default でこれになってるはず。念の為

  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // 返答を待たず Ok:
}

void Body::AnsGetValue( SMsg msg )
{
  QString Ch = msg.ToCh();
  if ( NormalChNames.contains( Ch ) ) {
    int ch = ChName2Num[ Ch ];
    QString cmd = QString( "CTR?%1" ).arg( ch, 2, 10, QChar( '0' ) );
    QString ans = CT->SendAndRead( cmd, 10 );
    s->SendAns( msg, QString( "@GetValue %1" ).arg( ans.toInt() ) );
  } else if ( ExtraChNames.contains( Ch ) ) {
    long ans = 0;
    for ( int i = 0; i < ExtraChs[ Ch ].count(); i++ ) {
      int ch = ChName2Num[ ExtraChs[ Ch ][ i ] ];
      QString cmd = QString( "CTR?%1" ).arg( ch, 2, 10, QChar( '0' ) );
      ans += CT->SendAndRead( cmd, 10 ).toInt();
    }
    s->SendAns( msg, QString( "@GetValue %1" ).arg( ans ) );
  } else {
    s->SendAns( msg, "@GetValue Er:" );
  }
}

void Body::simpleSend( QString cmd, SMsg msg )
{
  qDebug() << "sending " << cmd << msg.Msg();
  CT->SendACmd( cmd );
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
  CT->SendACmd( "STOP" );
  CT->SendACmd( StopModeCMD );
  CT->SendACmd( "CLAL" );
  CT->SendACmd( "GATEIN_DS" );
  CT->SendACmd( "STRT" );
  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
}

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
    StopModeCMD = cmd;
    simpleSend( StopModeCMD, msg );
  }
}

void Body::AnsStop( SMsg msg )
{
  simpleSend( "STOP", msg );
}

void Body::AnsRaw( SMsg msg )
{
  simpleSend( msg.Val(), msg );
}

void Body::AnsRawRead( SMsg msg )
{
  if ( msg.Vals().count() > 1 ) {
    qDebug() << CT->SendAndRead( msg.Vals()[0], msg.Vals()[1].toInt() );
  } 

  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
}

void Body::AnsQInitialize( SMsg msg )
{
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];
    if ( ! initialized ) {          // 連続で何回も呼ばれても先頭の一回だけ
      CT->clearBuffer();
      CT->SendACmd( "STOP" );       // カウントしてても止める
      CT->SendACmd( "CLGSDN" );     // データ記録番地 0 にセット
      CT->SendACmd( "GSED55000" ); // データ記録最終番地(ここまで来ると収集は止まる)
      //      CT->sendACmd( "DSAS" );
      CT->SendACmd( "GATEIN_EN" );
      CT->SendACmd( "GT_ACQ_DIF" ); // カウントの差分を記録
      CT->SendACmd( "GESTRT" );     // ゲートエッジデータ収集モード
                                    // 最初のゲート立ち上がりでカウントクリア
                                    // 以降のゲート立ち上がりでカウント記録
      dataNo = 0;
      initialized = true;
      gotData = false;
      finalized = false;
    }

    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate の Hの時間とLの時間の合計は最低 1ms 必要 !!

// AnsGetData が返すのは Count ではなく cps (count per sec)
// ct08.cpp の側で、時間で割り算した値を返すようになっている
void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];
    if ( initialized ) {
      CT->SendACmd( "STOP" );   // とにかく停止
      dataNo = CT->SendAndRead( "GSDN?", 4 ).toInt();
    }
    qDebug() << "asking" << ch << dataNo;
    if ( dataNo <= 0 ) {
      s->SendAns( msg, QString( "@qGetData 0" ) );
      return;
    }
    
    QVector<double> ans;
    CT->QGetData( ch, dataNo, ans );
    CT->clearBuffer();

    QString ret;
    if ( ans.count() > 1 ) {
      //      ret += " " + QString::number( ans[1].toInt( NULL, 16 ) );
      ret += " " + QString::number( ans[1] );
    }
    for ( int i = 1; i < ans.count() - 1; i++ ) {
      //      ret += " " + QString::number( ans[i].toInt( NULL, 16 ) );
      ret += " " + QString::number( ans[i] );
    }
    s->SendAns( msg, QString( "@qGetData %1 %2" ).arg( ans.count() - 1 ).arg( ret ) );
    
    initialized = false;
    gotData = true;
    finalized = false;
    // }
    //    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}
 
void Body::AnsQFinalize( SMsg msg )
{
#if 0
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
#endif
    //    int ch = ChName2Num[ msg.ToCh() ];
    
    if ( ! finalized ) {        // 連続で何回も呼ばれても先頭の一回だけ
      CT->SendACmd( "STOP" );    // とにかく止めておく

      StopModeCMD = "ENTS";
      CT->SendACmd( StopModeCMD );
      CT->SendACmd( "GATEIN_DS" );
      
      initialized = false;
      gotData = false;
      finalized = true;
    }
    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
#if 0
  }
#endif
}


