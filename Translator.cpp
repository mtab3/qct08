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
  CT->SendACmd( "STOP" );
  CT->SendACmd( "CLAL" );
  CT->SendACmd( "GATEIN_EN" );   // default �Ǥ���ˤʤäƤ�Ϥ���ǰ�ΰ�

  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // �������Ԥ��� Ok:
}

void Body::AnsGetValue( SMsg msg )
{
  smsg = msg;
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, "@GetValue Er:" );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];
    QString cmd = QString( "CTR?%1" ).arg( ch, 2, 10, QChar( '0' ) );
    CT->QueCmd( true, cmd, msg,
		CT, SIGNAL( received( CTMsg, SMsg ) ),
		this, SLOT( ansGetValue( CTMsg, SMsg ) ) );
    recSeq = 0;
    CT->SendCmd();
  }
}

void Body::simpleSend( QString cmd, SMsg msg )
{
  smsg = msg;
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
    simpleSend( cmd, msg );
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

void Body::AnsQInitialize( SMsg msg )
{
  smsg = msg;
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];
    if ( ! initialized ) {          // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendACmd( "STOP" );       // ������Ȥ��ƤƤ�ߤ��
      CT->SendACmd( "CLGSDN" );     // �ǡ�����Ͽ���� 0 �˥��å�
      CT->SendACmd( "GSED9999" ); // �ǡ�����Ͽ�ǽ�����(�����ޤ����ȼ����ϻߤޤ�)
      CT->SendACmd( "GT_ACQ_DIF" ); // ������Ȥκ�ʬ��Ͽ
      CT->SendACmd( "GESTRT" );     // �����ȥ��å��ǡ��������⡼��
                                    // �ǽ�Υ�����Ω���夬��ǥ�����ȥ��ꥢ
                                    // �ʹߤΥ�����Ω���夬��ǥ�����ȵ�Ͽ
      initialized = true;
      gotData = false;
      finalized = false;
    }

    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate �� H�λ��֤�L�λ��֤ι�פϺ��� 1ms ɬ�� !!

void Body::AnsQGetData( SMsg msg )
{
  qDebug() << "a";
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
    qDebug() << "b";
  } else {
    qDebug() << "c";
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! gotData ) {         // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendACmd( "STOP" );   // �Ȥˤ������
      CT->QueCmd( true, "GSDN?", msg, // ���ߥǡ����ֹ���ɤ߼��
		  CT, SIGNAL( received( CTMsg, SMsg ) ),
		  this, SLOT( ansNowDataNo( CTMsg, SMsg ) ) );
      CT->QueCmd( true, "GSDAL?", msg, // ���ߥǡ����ֹ�ޤǤΥǡ����ɤ߼��
		  CT, SIGNAL( received( CTMsg, SMsg ) ),
		  this, SLOT( ansGetData( CTMsg, SMsg ) ) );

      initialized = false;
      gotData = true;
      finalized = false;

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

    if ( ! finalized ) {        // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendACmd( "STOP" );    // �Ȥˤ����ߤ�Ƥ���
      
      initialized = false;
      gotData = false;
      finalized = true;
    }

    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}

void Body::ansGetValue( CTMsg msg, SMsg smsg )
{
  qDebug() << "ctmsg " << msg.msg();
  // recSeq �˽��ä�ư��򤹤���� (GetValue �� 1step)
  disconnect( CT, SIGNAL( received( CTMsg, SMsg ) ),
	      this, SLOT( ansGetValue( CTMsg, SMsg ) ) );
  s->SendAns( smsg, QString( "@GetValue %1" ).arg( msg.msg().toInt() ) );
}

void Body::ansNowDataNo( CTMsg msg, SMsg /* smsg */ )
{
  disconnect( CT, SIGNAL( received( CTMsg, SMsg ) ),
	      this, SLOT( ansNowDataNo( CTMsg, SMsg ) ) );
  dataNo = msg.msg().toInt();
  nowDataNo = 0;
  qDebug() << "ans now data no" << dataNo;
}

void Body::ansGetData( CTMsg msg, SMsg smsg )
{
  nowDataNo++;
  qDebug() << "ans get data" << nowDataNo << dataNo;
  if ( nowDataNo >= dataNo ) {
    disconnect( CT, SIGNAL( received( CTMsg, SMsg ) ),
		this, SLOT( ansGetData( CTMsg, SMsg ) ) );
    s->SendAns( smsg, QString( "@qGetData %1" ).arg( nowDataNo ) );
  }
}





