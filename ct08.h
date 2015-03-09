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
  QString cmd;
  bool waitf;

  aQue( void ) { cmd.clear(); waitf = false; };
};

class CT08 : public QObject
{
  Q_OBJECT

  bool Connected;
  bool busy;
  QTimer *t;

  QString CTIP;
  QString CTPORT;
  QTcpSocket *ss;

  QVector<aQue*> cmdq;

  char rBuf[ BUFSIZE + 1 ];
  char RBuf[ BUFSIZE + 1 ];
  
private slots:
  void RcvMessage( void );
  void watch( void );
  
public:
  CT08( void );
  ~CT08( void );

  bool isBusy( void ) { return busy; };
  void Connect( QString aip, QString aport );
  void QueCmd( bool waitf, QString cmd );
  void SendCmd( void );

public slots:

signals:
  void received( CTMsg msg );
  void changedIsBusy( bool busy );
};

#endif
