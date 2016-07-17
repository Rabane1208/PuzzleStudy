#include "Map.h"
#include "Mouse.h"
#include "DxLib.h"
#include "Framework.h"

MapPtr Map::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Map >( fw->getTask( Map::getTag( ) ) );
}

Map::Map( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_chip_size = fw->getWindowWidth( ) / MAP_X_NUM;
	_mouse = Mouse::getTask( );

	for ( int i = 0; i < MAP_MAX; i++ ) {
		map[ i ] = GetRand( 5 );
	}
}

Map::~Map( ) {
}

void Map::update( ) {
	int t = posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	DrawFormatString( 0, 0, 0xff0000, "Map : %d", t );
	DrawFormatString( 0, 20, 0xff0000, "Click Status : %d", _mouse->getStatus( ) );
}

int Map::getChipSize( ) {
	return _chip_size;
}

int Map::getMap( int idx ) {
	return map[ idx ];
}

int Map::posToIdx( int x, int y ) {
	int idx_x = x / _chip_size;
	int idx_y = y / _chip_size;
	int idx = idx_x + ( idx_y - 2 ) * MAP_X_NUM;
	if ( idx < 0 || idx >= MAP_MAX ) {
		idx = -1;
	}
	return idx;
}

bool Map::isPush( int idx ) {
	if ( posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) ) != idx ) { 
		return false;
	}
	if ( _mouse->getStatus( ) != 2 ) {
		return false;
	}
	return true;
}