#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "MsgType.h"
#include "SMsg.h"

SMsg::SMsg( void )
{
}

MSGOREVENT SMsg::ParseMsg( QString Message )
{
  int i1, i2, i3;

  from.clear();
  fromDev.clear();
  fromCh.clear();
  to.clear();
  toDev.clear();
  toCh.clear();
  msg.clear();
  val.clear();
  vals.clear();

  Message = Message.simplified();

  i1 = Message.indexOf( '>' );      // i1 : '>' の位置
  if ( i1 < 0 ) {
    MorE = RES_OTHER;         // '>' がないと、Stars server からのメッセージの構造
    val = Message;            // としてはおかしいが、とりあえずその内容だけは
    return RES_OTHER;         // val に残して return
  }
  from = Message.mid( 0, i1 );         // from にチャンネルがあっても無くても気にしない
  i2 = from.indexOf( '.' );
  if ( i2 >= 0 ) {
    fromDev = from.left( i2 );
    fromCh = from.mid( i2 + 1 );
  } else {
    fromDev = from;
    fromCh = "";
  }
  i3 = Message.indexOf( ' ' );
  if ( i3 < 0 ) {
    MorE = RES_OTHER;
    val = Message.mid( i1 + 1 );
    return RES_OTHER;
  }

  to = Message.mid( i1 + 1, i3 - i1 - 1 );
  i2 = Message.indexOf( '.', i1 + 1 );
  if ( ( i1 < i2 )&&( i2 < i3 ) ) {       // to に ch 名があれば
    toDev = Message.mid( i1 + 1, i2 - i1 - 1 );
    toCh = Message.mid( i2 + 1, i3 - i2 - 1 );
  } else {                                 // なければ to だけセット ch は空のまま
    toDev = Message.mid( i1 + 1, i3 - i1 - 1 );
  }

  i2 = Message.indexOf( ' ' );  // i2 : 最初の ' ' の位置
  if ( Message.at( i2 + 1 ) == '_' )
    MorE = RES_EVENT;
  else
    MorE = RES_MSG;

  i3 = Message.indexOf( ' ', i2 + 1 );
  if ( i3 < 0 ) {
    msg = Message.mid( i2 + 1 );
    setMsgType();
    if ( ! toCh.isEmpty() ) {
      val = toCh;
      vals.insert( 0, toCh );
    }
    return MorE;
  }
  msg = Message.mid( i2 + 1, i3 - i2 - 1 );
  setMsgType();

  val = Message.mid( i3 + 1 ).simplified();
  vals = val.split( QRegExp( "\\s+" ) );
  if ( ! toCh.isEmpty() ) {
    vals.insert( 0, toCh );
    val = toCh;
  }

  return MorE;
}

void SMsg::setMsgType( void )
{
  int i = 0;

  msgt = NOTMSG;
  while ( MsgT[i].V != NOTMSG ) {
    if ( msg == MsgT[i].T ) {
      msgt = MsgT[i].V;
      break;
    }
    i++;
  }
}

bool SMsg::isOk( void )
{
  if ( val.mid( 0, 3 ) == "Ok:" )
    return true;
  if ( val.mid( 0, 2 ) == "OK" )
    return true;
  return false;
}
