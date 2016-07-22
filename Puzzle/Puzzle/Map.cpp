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
}

Map::~Map( ) {
}

void Map::update( ) {
	
}

int Map::getChipSize( ) {
	return _chip_size;
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