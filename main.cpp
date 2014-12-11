#include <QCoreApplication>

#include "main.h"
#include "Main.h"

int main( int argc, char *argv[] )
{
  QCoreApplication app( argc, argv );
  Main *body = new Main;

  return app.exec();
}

