#ifndef MSGTYPE_H
#define MSGTYPE_H

#include <QString>

enum MSGOREVENT { RES_MSG, RES_EVENT, RES_OTHER };

enum MSGTYPE {
  ISBUSY,
  
  RESET,
  GETVALUE,
  SETTIMERPRESET,
  COUNTERRESET,
  COUNTSTART,

  SETSTOPMODE,
  STOP,
  
  QINITIALIZE,
  QGETDATA,
  QFINALIZE,

  NOTMSG,
};

struct MsgTyp {
  QString T;
  MSGTYPE V;
};

extern const MsgTyp MsgT[];

#endif

