#include <QTimer>

#include "Body.h"

Body::Body()
{
  if ( ! ReadConfig() )
    return;

  busy = false;
  initialized = false;
  gotData = false;
  finalized = false;
  
  SetUpCT08Connection();
  SetUpStarsConnection();
}

Body::~Body()
{
  delete CT;
}

void Body::SetUpCT08Connection( void )
{
  CT = new CT08;

  connect( CT, SIGNAL( NewMsg( SMsg, CTMsg )), this, SLOT( ParseAns( SMsg, CTMsg ) ), Qt::UniqueConnection );
  CT->Connect( Config[ "CT08_IP" ], Config[ "CT08_PORT" ] );
}


void Body::SetUpStarsConnection( void )
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

