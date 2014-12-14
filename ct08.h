#ifndef QCT08_H
#define QCT08_H

#include <QtCore>
#include <QtNetwork>

#include <QTimer>

#include "MsgType.h"
#include "SMsg.h"
#include "ct08Msg.h"

#define BUFSIZE ( 2047 )

#if 0
struct aQue {
  QString cmd;
  QString params;

  aQue( void ) { cmd.clear(); params.clear(); };
};
#endif

class CT08 : public QObject
{
  Q_OBJECT

  bool Connected;

  QString CTIP;
  QString CTPORT;
  QTcpSocket *ss;

  QStringList cmdq;

  char rBuf[ BUFSIZE + 1 ];
  char RBuf[ BUFSIZE + 1 ];
  
private slots:
  void RcvMessage( void );
  
public:
  CT08( void );
  ~CT08( void );

  void Connect( QString aip, QString aport );
  void QueCmd( bool waitf, QString cmd );
  void SendCmd( void );

public slots:

signals:
  void NewMsg( CTMsg amsg );
  void received( void );
};

#endif
