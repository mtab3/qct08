#ifndef QCT08_H
#define QCT08_H

#include <QtCore>
#include <QtNetwork>

#include <QTimer>

#include "MsgType.h"
#include "SMsg.h"

#define BUFSIZE ( 2049 )

class CT08 : public QObject
{
  Q_OBJECT

  bool Connected;
  bool busy;
  QTimer *t;

  QString CTIP;
  QString CTPORT;
  QTcpSocket *ss;

  SMsg sMsg;

  char rBuf[ BUFSIZE + 1 ];
  char RBuf[ BUFSIZE + 1 ];
  
private slots:
  //  void RcvMessage( void );
  
public:
  CT08( void );
  ~CT08( void );

  bool isBusy( void ) { return busy; };
  void Connect( QString aip, QString aport );
  void SendCmd( void );
  void SendACmd( QString cmd );
  QString SendAndRead( QString cmd, int size );
  void QGetData( int ch, int num, QStringList &data );
		      
public slots:
  void watch( void );

signals:
  void changedIsBusy( bool busy );
};

#endif
