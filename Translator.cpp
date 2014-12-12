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
  CT->SendCMD( "GATEIN_EN" );   // default �Ǥ���ˤʤäƤ�Ϥ���ǰ�ΰ�
  s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  // �������Ԥ��� Ok:
}

void Body::AnsQInitialize( SMsg msg )
{
  if ( msg.ToCh() == "" ) {
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! initialized ) {          // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendCMD( "STOP" );        // ������Ȥ��ƤƤ�ߤ��
      CT->SendCMD( "CLGSDN" );      // �ǡ�����Ͽ���� 0 �˥��å�
      // CT->SendCMD( "GSED9999" ); // �ǡ�����Ͽ�ǽ�����(�����ޤ����ȼ����ϻߤޤ�)
      CT->SendCMD( "GT_ACQ_DIF" );  // ������Ȥκ�ʬ��Ͽ
      CT->SendCMD( "GESTRT" );      // �����ȥ��å��ǡ��������⡼��
                                    // �ǽ�Υ�����Ω���夬��ǥ�����ȥ��ꥢ
                                    // �ʹߤΥ�����Ω���夬��ǥ�����ȵ�Ͽ
      initialized = true;
      gotData = false;
      finalized = false;
    }
    
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Ok:" ).arg( msg.Msg() ) );
  }
}

// Gate �� H�λ��֤�L�λ��֤ι�פϺ��� 1ms ɬ�� !!

void Body::AnsQGetData( SMsg msg )
{
  if ( ( msg.ToCh() == "" ) || ( ! ChName2Num.contains( msg.ToCh() ) ) ){
    s->SendAns( msg.To(), msg.From(), QString( "@%1 Er:" ).arg( msg.Msg() ) );
  } else {
    //    int ch = ChName2Num[ msg.ToCh() ];

    if ( ! gotData ) {         // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendCMD( "STOP" );   // �Ȥˤ������
      CT->SendCMD( "GSDN?" );  // ���ߥǡ����ֹ���ɤ߼��
      CT->SendCMD( "GSDAL?" ); // ���ߥǡ����ֹ�ޤǤΥǡ����ɤ߼��
                               // �ƹԤ��������ͥ�+�����󥿤��ͤ�����޶��ڤ���¤�
                               // ���ߥǡ����ֹ�ʬ�ιԿ������
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

    if ( ! finalized ) {        // Ϣ³�ǲ����ƤФ�Ƥ���Ƭ�ΰ�����
      CT->SendCMD( "STOP" );    // �Ȥˤ����ߤ�Ƥ���
      initialized = false;
      gotData = false;
      finalized = true;
    }

    //    CT->SendCMD( msg, QString( "STP%1" ).arg( ch ), "/0" );
  }
}
