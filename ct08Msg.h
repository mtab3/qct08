#ifndef CT08MSG_H
#define CT08MSG_H

#include <QString>
#include <QStringList>

class CTMsg {
  QString Msg;
  
 public:
  CTMsg( void ) {};
  
  void ParseMsg( QString msg ) { Msg = msg; };
  QString msg( void ) { return Msg; };
};

#endif
