#include "Map.h"
#include "DxLib.h"
#include "Framework.h"

MapPtr Map::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Map >( fw->getTask( Map::getTag( ) ) );
}

Map::Map( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_chip_size = fw->getWindowWidth( ) / MAP_X_NUM;

	for ( int i = 0; i < MAP_MAX; i++ ) {
		map[ i ] = 0;
	}
}

Map::~Map( ) {
}

void Map::update( ) {

}

double Map::getChipSize( ) {
	return _chip_size;
}

int Map::getMap( int idx ) {
	return map[ idx ];
}
