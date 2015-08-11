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
  //  CT->SendACmd( "GATEIN_EN" );   // default �Ǥ���ˤʤäƤ�Ϥ���ǰ�ΰ�

  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // �������Ԥ��� Ok:
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
  // �������Ԥ��� Ok:
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
    if ( ! initialized ) {          // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->clearBuffer();
      CT->SendACmd( "STOP" );       // ������Ȥ��ƤƤ�ߤ��
      CT->SendACmd( "CLGSDN" );     // �ǡ�����Ͽ���� 0 �˥��å�
      CT->SendACmd( "GSED55000" ); // �ǡ�����Ͽ�ǽ�����(�����ޤ����ȼ����ϻߤޤ�)
      //      CT->sendACmd( "DSAS" );
      CT->SendACmd( "GATEIN_EN" );
      CT->SendACmd( "GT_ACQ_DIF" ); // ������Ȥκ�ʬ��Ͽ
      CT->SendACmd( "GESTRT" );     // �����ȥ��å��ǡ��������⡼��
                                    // �ǽ�Υ�����Ω���夬��ǥ�����ȥ��ꥢ
                                    // �ʹߤΥ�����Ω���夬��ǥ�����ȵ�Ͽ
      dataNo = 0;
      initialized = true;
      gotData = false;
      finalized = false;
    }

    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate �� H�λ��֤�L�λ��֤ι�פϺ��� 1ms ɬ�� !!

// AnsGetData ���֤��Τ� Count �ǤϤʤ� cps (count per sec)
// ct08.cpp ��¦�ǡ����֤ǳ�껻�����ͤ��֤��褦�ˤʤäƤ���
void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];
    if ( initialized ) {
      CT->SendACmd( "STOP" );   // �Ȥˤ������
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
    
    if ( ! finalized ) {        // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendACmd( "STOP" );    // �Ȥˤ����ߤ�Ƥ���

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


