#ifndef AMSG_H
#define AMSG_H

#include <QString>
#include <QStringList>

class AMsg {
  QString Msg;
  QString Stat;
  QString Cmd0;
  QString Cmd;
  QString Ch;
  QString Val;
  QStringList Vals;
  
 public:
  AMsg( void ) {};
  QString stat( void ) { return Stat; };
  QString msg( void ) { return Msg; };
  QString cmd0( void ) { return Cmd0; };
  QString cmd( void ) { return Cmd; };
  QString ch( void ) { return Ch; };
  QString val( void ) { return Val; };
  QStringList vals( void ) { return Vals; };

  void ParseMsg( QString comming );
};

#endif
