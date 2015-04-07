
#include <stdio.h>

#include "MsgType.h"

const MsgTyp MsgT[] = {
  { "IsBusy", ISBUSY },
  
  { "Reset", RESET },              // �̾�⡼��
  { "GetValue", GETVALUE },
  { "SetTimerPreset", SETTIMERPRESET },
  { "CounterReset", COUNTERRESET },
  { "CountStart", COUNTSTART },

  { "SetStopMode", SETSTOPMODE },  // Ϣ³�������
  { "Stop", STOP },
  
  { "qInitialize", QINITIALIZE },  // Q-XAFS
  { "qGetData", QGETDATA },
  { "qFinalize", QFINALIZE }, 

  { "Raw", RAW },
  
  { "", NOTMSG },
};

const char *MType2String( MSGTYPE mtype )
{
  return MsgT[ mtype ].T.toLatin1().data();
}
