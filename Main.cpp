#include <QTimer>

#include "Main.h"

Main::Main()
{
  if ( ! ReadConfig() )
    return;

  SetUpCT08Connection();
  SetUpStarsConnection();
}

Main::~Main()
{
  delete A;
}

void Main::SetUpCT08Connection( void )
{
  CT = new CT08;

#if 0  
  CT->SetAxNames( AxNum2Name, AxName2Num );
  if ( Config.contains( "NAME_ON_STARS" ) )
    A->SetDriverName( Config[ "NAME_ON_STARS" ] );
  else
    A->SetDriverName( "ARIESDriver" );
  connect( A, SIGNAL( NewMsg( SMsg, AMsg )), this, SLOT( ParseAns( SMsg, AMsg ) ), Qt::UniqueConnection );
#endif
  
  CT->Connect( Config[ "CT08_IP" ], Config[ "CT08_PORT" ] );
}


void Main::SetUpStarsConnection( void )
{
  s = new Stars;

  QString DefaultKey  = "qct08";
  QString DefaultName = "qct08";
  if ( Config.contains( "KEY_FILE_NAME" ) )
    DefaultKey = Config[ "KEY_FILE_NAME" ];
  if ( Config.contains( "NAME_ON_STARS" ) )
    DefaultName = Config[ "NAME_ON_STARS" ];

  s->ReadStarsKeys( DefaultKey, DefaultName );

  // Stars Message
  connect( s, SIGNAL( AskIsBusy( SMsg ) ), this, SLOT( AnsIsBusy( SMsg ) ), Qt::UniqueConnection );
  connect( s, SIGNAL( AskGetValue( SMsg ) ), this, SLOT( AnsGetValue( SMsg ) ), Qt::UniqueConnection );
  connect( s, SIGNAL( AskReset( SMsg ) ), this, SLOT( AnsReset( SMsg ) ), Qt::UniqueConnection );
  connect( s, SIGNAL( AskQInitialize( SMsg ) ), this, SLOT( AnsQInitialize( SMsg ) ), Qt::UniqueConnection );
  connect( s, SIGNAL( AskQGetData( SMsg ) ), this, SLOT( AnsQGetData( SMsg ) ), Qt::UniqueConnection );
  connect( s, SIGNAL( AskQFinalize( SMsg ) ), this, SLOT( AnsQFinalize( SMsg ) ), Qt::UniqueConnection );

  s->SetNewSVAddress( Config["STARS_IP"] );
  s->SetNewSVPort( Config["STARS_PORT"] );
  s->MakeConnection();
}

