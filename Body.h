#ifndef BODY_H
#define BODY_H

#include <QObject>

#include "ct08.h"
#include "Stars.h"

class Body : public QObject
{
  Q_OBJECT

  QMap<QString,QString> Config, ConfigL;
  QMap<int,QString> ChNum2Name;
  QMap<QString,int> ChName2Num;

  CT08 *CT;
  Stars *s;

  bool initialized;
  bool gotData;
  bool finalized;
  int dataNo;
  int nowDataNo;

  int recSeq;
  
  SMsg smsg;

  void simpleSend( QString cmd, SMsg msg );
  bool ReadConfig( void );
  void SetUp( void );
  void SetUpCT08Connection( void );
  void SetUpStarsConnection( void );

public:
  Body();
  ~Body();

private slots:
  void AnsIsBusy( SMsg msg );

  void AnsReset( SMsg msg );
  void AnsGetValue( SMsg msg );
  void AnsSetTimerPreset( SMsg msg );
  void AnsCounterReset( SMsg msg );
  void AnsCountStart( SMsg msg );

  void AnsSetStopMode( SMsg msg );
  void AnsStop( SMsg msg );

  void AnsQInitialize( SMsg msg );
  void AnsQGetData( SMsg msg );
  void AnsQFinalize( SMsg msg );

  void AnsRaw( SMsg msg );

  void ansGetValue( CTMsg msg, SMsg smsg );
  void ansNowDataNo( CTMsg msg, SMsg smsg );
  void ansGetData( CTMsg msg, SMsg smsg );

  void changedCTIsBusy( bool busy );
signals:
  
};

#endif
