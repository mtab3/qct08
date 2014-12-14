#ifndef STARS_H
#define STARS_H

#include <QTcpSocket>
#include <QStringList>
#include <QString>

#include "SMsg.h"

//#define ERROR   "Error!!"        // string を返す関数のエラー通知用

// デバイス名の定義
//#define MYNAME      "BLC"       // 自分が名乗る名前 config で変えられる様にするべき


#define STARSSERVER "localhost" // config で変えられるようにするべき
#define STARSPORT   ( 6057 )         // config で変えられるようにするべき

class Stars : public QObject 
{
  Q_OBJECT

  QString MyNameOnStars;

  QString StarsServer;
  qint16  StarsSPort;

  QStringList keys;
  int MaxKeys;
  QTcpSocket *ss;
  bool newSetting;

  void ReadHistory( void );

  int ConnectionStage;

public:
  Stars( void );
  void ReadStarsKeys( QString SelectedName, QString DefaultName );
  QString GetKey( int nkey );

  void MakeConnection( void );
  bool SendCMD( QString dev, QString cmd1, QString cmd2 = "" );
  bool SendCMD2( QString fromCh, QString dev, QString cmd1, QString cmd2 = "" );
  void SendAns( SMsg msg, QString ans );
  void SendEvent( QString from, QString msg );

private:
  QString nextItem( QString start, QString &item );

public slots:
  void SetNewSVAddress( const QString &item );
  void SetNewSVPort( const QString &item );
  void ReceiveMessageFromStars( void );
  void ReConnect( void );

signals:
  void ConnectionIsReady( Stars *s );
  void ReConnected( void );

  void AskIsBusy( SMsg msg );
  void AskGetValue( SMsg msg );
  void AskReset( SMsg msg );
  void AskQInitialize( SMsg msg );
  void AskQGetData( SMsg msg );
  void AskQFinalize( SMsg msg );
};

#endif
