#ifndef MAIN_H
#define MAIN_H

#include <QObject>

#include "qct08.h"
#include "Stars.h"

class Main : public QObject
{
  Q_OBJECT

  QMap<QString,QString> Config, ConfigL;
  QMap<int,QString> ChNum2Name;
  QMap<QString,int> ChName2Num;

  CT08 *CT;
  Stars *s;

  bool ReadConfig( void );
  void SetUp( void );
  void SetUpStarsConnection( void );

public:
  Main();
  ~Main();

private slots:
  void ParseAns( SMsg smsg, AMsg amsg );

  void AnsIsBusy( SMsg msg );
  void AnsGetValue( SMsg msg );
  void AnsReset( SMsg msg );
  void AnsQGetData( SMsg msg );
  void AnsQFinalize( SMsg msg );
signals:
  
};

#endif
