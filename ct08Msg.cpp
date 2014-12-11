
#include "ct08Msg.h"

//  !!!!!
//  ���Υե�����Ϥޤ��꤬�Ĥ��Ƥʤ���
//  CT08 �Ȥ��̿���å������Υѥ���˹�碌�Ƥ������ѹ�����

void AMsg::ParseMsg( QString in )
{
  Stat.clear();
  Cmd0.clear();
  Cmd.clear();
  Ch.clear();
  Val.clear();

  in = in.simplified();
  Msg = in;
  Vals = in.split( QRegExp( "\\s+" ) );
  if ( Vals.count() > 0 ) {
    Stat = Vals[0];
    Vals.removeFirst();
    if ( Vals.count() > 0 ) {
      Cmd0 = Vals[0];
      Cmd = Cmd0.left( 3 );
      Ch = Cmd0.mid( 3 );
      Vals.removeFirst();
      if ( Vals.count() > 0 ) {
	Val = Vals[0];
      }
    }
  }
}
