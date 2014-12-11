#ifndef MSGTYPE_H
#define MSGTYPE_H

#include <QString>

enum MSGOREVENT { RES_MSG, RES_EVENT, RES_OTHER };

enum MSGTYPE {
  ISBUSY,
  GETVALUE,

  RESET,
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

