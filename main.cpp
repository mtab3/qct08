#include <QCoreApplication>

#include "main.h"
#include "Body.h"

int main( int argc, char *argv[] )
{
  QCoreApplication app( argc, argv );
  //Body *body = new Body;
  new Body;
  
  return app.exec();
}

