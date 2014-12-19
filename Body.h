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

  bool busy;
  bool initialized;
  bool gotData;
  bool finalized;

  int recSeq;
  
  SMsg smsg;

  bool ReadConfig( void );
  void SetUp( void );
  void SetUpCT08Connection( void );
  void SetUpStarsConnection( void );

public:
  Body();
  ~Body();

private slots:
  void AnsIsBusy( SMsg msg );
  void AnsGetValue( SMsg msg );
  void AnsReset( SMsg msg );
  void AnsQInitialize( SMsg msg );
  void AnsQGetData( SMsg msg );
  void AnsQFinalize( SMsg msg );

  void ansGetValue( CTMsg msg );
  void ansGetData( void );
signals:
  
};

#endif
