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
  bool Waiting;

  QString CTIP;
  QString CTPORT;
  QTcpSocket *ss;

  QQueue<aQue> BeforeThrowQ;
  QQueue<aQue> WaitingAnsQ;

  char rBuf[ BUFSIZE + 1 ];
  char RBuf[ BUFSIZE + 1 ];
  
#if 0
  QMap<int,QString> Num2Name;
  QMap<QString,int> Name2Num;

  char wBuf[ BUFSIZE + 1 ];
#endif
			 
private slots:
  void RcvMessage( void );
  void SendCMD0( void );
#if 0
#endif
  
public:
  CT08( void );
  ~CT08( void );

  void Connect( QString aip, QString aport );
  void SendCMD( SMsg msg, QString cmd );

#if 0  
  void SetChNames( QMap<int,QString> num2name, QMap<QString,int> name2num );
  bool isBusy( void ) { return Waiting; };
#endif
							
public slots:

signals:
  void NewMsg( SMsg smsg, CTMsg amsg );
 
};

#endif
