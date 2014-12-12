#ifndef QCT08_H
#define QCT08_H

#include <QtCore>
#include <QtNetwork>

#include <QTimer>

#include "MsgType.h"
#include "SMsg.h"
#include "ct08Msg.h"

#define BUFSIZE ( 2047 )

struct aQue {
  SMsg smsg;
  QString cmd;
  QString params;

  aQue( void ) { cmd.clear(); params.clear(); };
};

class CT08 : public QObject
{
  Q_OBJECT

  bool Connected;

  QString CTIP;
  QString CTPORT;
  QTcpSocket *ss;

  char rBuf[ BUFSIZE + 1 ];
  char RBuf[ BUFSIZE + 1 ];
  
private slots:
  void RcvMessage( void );
  
public:
  CT08( void );
  ~CT08( void );

  void Connect( QString aip, QString aport );
  void SendCMD( QString cmd );

public slots:

signals:
  void NewMsg( CTMsg amsg );
 
};

#endif
