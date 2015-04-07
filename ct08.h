#ifndef QCT08_H
#define QCT08_H

#include <QtCore>
#include <QtNetwork>

#include <QTimer>

#include "MsgType.h"
#include "SMsg.h"
#include "ct08Msg.h"

#define BUFSIZE ( 2049 )

struct aQue {
  QString cmd;
  SMsg msg;
  int size;

  QObject *from, *to;
  char *signal, *slot;

  aQue( void ) { cmd.clear(); size = 0; from = to = NULL; signal = slot = NULL; };
};

class CT08 : public QObject
{
  Q_OBJECT

  bool Connected;
  bool busy;
  bool blocking;
  QTimer *t;

  QString CTIP;
  QString CTPORT;
  QTcpSocket *ss;

  QVector<aQue*> cmdq;
  SMsg sMsg;

  char rBuf[ BUFSIZE + 1 ];
  char RBuf[ BUFSIZE + 1 ];
  
private slots:
  void RcvMessage( void );
  void watch( void );
  
public:
  CT08( void );
  ~CT08( void );

  bool isBusy( void ) { return busy; };
  void Block( bool block ) { blocking = block; };
  void Connect( QString aip, QString aport );
  void QueCmd( QString cmd, int size, SMsg smsg, 
	       QObject *from = NULL, const char *signal = NULL,
	       QObject *to = NULL,   const char *slot = NULL );
  void SendCmd( void );
  void SendACmd( QString cmd );
  QString SendAndRead( QString cmd, int size );
		      
public slots:

signals:
  void received( CTMsg msg, SMsg smsg );
  void changedIsBusy( bool busy );
};

#endif
