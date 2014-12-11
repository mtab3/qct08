
#include <stdio.h>

#include "MsgType.h"

const MsgTyp MsgT[] = {
  { "IsBusy", ISBUSY },
  { "GetValue", GETVALUE },

  { "Reset", RESET },
  { "qInitialize", QINITIALIZE },
  { "qGetData", QGETDATA },
  { "qFinalize", QFINALIZE }, 

  { "", NOTMSG },
};

const char *MType2String( MSGTYPE mtype )
{
  return MsgT[ mtype ].T.toLatin1().data();
}
