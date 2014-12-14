#include "Body.h"

void Body::AnsIsBusy( SMsg msg )
{
  smsg = msg;
  s->SendAns( msg,
	      QString( "@%1 %2" ).arg( msg.Msg() ).arg( busy ? 1 : 0 ) );
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
    disconnect( CT, SIGNAL( received() ) );
    connect( CT, SIGNAL( received() ), this, SLOT( ansGetValue() ) );
    CT->SendCmd();
  }
}

void Body::AnsReset( SMsg msg )
{
  initialized = false;
  gotData = false;
  finalized = false;
  busy = false;

  smsg = msg;
  CT->QueCmd( false, "STOP" );
  CT->QueCmd( false, "CLAL" );
  CT->QueCmd( false, "GATEIN_EN" );   // default �Ǥ���ˤʤäƤ�Ϥ���ǰ�ΰ�

  disconnect( CT, SIGNAL( received() ) );
  CT->SendCmd();
  s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // �������Ԥ��� Ok:
}

void Body::AnsQInitialize( SMsg msg )
{
  smsg = msg;
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! initialized ) {          // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->QueCmd( false, "STOP" );        // ������Ȥ��ƤƤ�ߤ��
      CT->QueCmd( false, "CLGSDN" );      // �ǡ�����Ͽ���� 0 �˥��å�
      // CT->SendCMD( "GSED9999" ); // �ǡ�����Ͽ�ǽ�����(�����ޤ����ȼ����ϻߤޤ�)
      CT->QueCmd( false, "GT_ACQ_DIF" );  // ������Ȥκ�ʬ��Ͽ
      CT->QueCmd( false, "GESTRT" );      // �����ȥ��å��ǡ��������⡼��
                                    // �ǽ�Υ�����Ω���夬��ǥ�����ȥ��ꥢ
                                    // �ʹߤΥ�����Ω���夬��ǥ�����ȵ�Ͽ
      initialized = true;
      gotData = false;
      finalized = false;

      disconnect( CT, SIGNAL( received() ) );
      CT->SendCmd();
    }
    
    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate �� H�λ��֤�L�λ��֤ι�פϺ��� 1ms ɬ�� !!

void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! gotData ) {         // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->QueCmd( false, "STOP" );   // �Ȥˤ������
      CT->QueCmd( true, "GSDN?" );  // ���ߥǡ����ֹ���ɤ߼��
      CT->QueCmd( true, "GSDAL?" ); // ���ߥǡ����ֹ�ޤǤΥǡ����ɤ߼��
                               // �ƹԤ��������ͥ�+�����󥿤��ͤ�����޶��ڤ���¤�
                               // ���ߥǡ����ֹ�ʬ�ιԿ������
      initialized = false;
      gotData = true;
      finalized = false;

      recSeq = 0;
      disconnect( CT, SIGNAL( received() ) );
      connect( CT, SIGNAL( received() ), this, SLOT( ansGetData() ) );
      CT->SendCmd();
    };
    
    s->SendAns( msg, QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

void Body::AnsQFinalize( SMsg msg )
{
  if ( msg.ToCh() != "" ) {
    s->SendAns( msg, QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! finalized ) {        // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->QueCmd( false, "STOP" );    // �Ȥˤ����ߤ�Ƥ���
      
      initialized = false;
      gotData = false;
      finalized = true;

      disconnect( CT, SIGNAL( received() ) );
      CT->SendCmd();
    }

    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}

void Body::ansGetValue( void )
{
  // recSeq �˽��ä�ư��򤹤���� (GetValue �� 1step)
}

void Body::ansGetData( void )
{
  // recSeq �˽��ä�ư��򤹤���� (GetData �� 2step)
}
