
#include "Body.h"

#define CONFIG_FILE   "qct08.cfg"

// 設定ファイルを読んで Config[] と ConfigL[] をセットアップ
// Config[] は、スペース区切りの最初の項目がキー、2番めの項目が値
// ConfigL[] は、スペース区切りの最初の項目がキー、スペース以降の全部が値

bool Body::ReadConfig( void )
{
  QFile f( CONFIG_FILE );
  if ( !f.open( QIODevice::ReadOnly ) ) {
    qDebug() << QString( "Can not open [%1]" ).arg( CONFIG_FILE );
    return false;
  }
  QTextStream in( &f );

  while( !in.atEnd() ) {
    QString line = in.readLine().simplified();
    int p = 0;
    if ( line.count() == 0 ) continue;
    if ( line[0] == '#' ) continue;
    if ( ( p = line.indexOf( QRegExp( "\\s+" ) ) ) < 0 ) continue;
    QString key = line.left( p ).toUpper();
    QString val = line.mid( p+1 );
    ConfigL[ key ] = val;
    // スペースで区切られた最初の項目をキーに、以降の文字列を全て値として持つ

    QStringList items = line.split( QRegExp( "\\s+" ) );
    if ( items.count() == 1 ) {
      Config[ items[0].toUpper() ] = "";
    }
    if ( items.count() > 1 ) {
      if ( items[1][0] == '#' ) {
	Config[ items[0].toUpper() ] = "";
      } else {
	Config[ items[0].toUpper() ] = items[1];
	// スペースで区切られた最初の項目をキーに、二番目の項目を値に持つ
      }
    }
  }

  f.close();

  SetUp();

  return true;
}

#define CH_NAME   ( "CH_NAME" )

void Body::SetUp( void )
{
  QList<QString> keys = Config.keys();
  
  for ( int i = 0; i < keys.count(); i++ ) {
    if ( keys[i].left( strlen( CH_NAME ) ) == CH_NAME ) {
      int ch = keys[i].mid( strlen( CH_NAME ) + 1 ).toInt();
      ChNum2Name[ ch ] = Config[ keys[i] ];
      ChName2Num[ Config[ keys[i] ] ] = ch;
    }
  }
}
