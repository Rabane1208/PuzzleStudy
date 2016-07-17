#include "Drawer.h"
#include "DxLib.h"
#include "Framework.h"
#include "Map.h"

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( Drawer::getTag( ) ) );
}

Drawer::Drawer( ) {
	_map = Map::getTask( );
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	drawMap( );

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		if ( _map->isPush( i ) ) {
			drawChip( i, _map->getChipSize( ) * 6 / 10 );
		}
	}
}

void Drawer::drawMap( ) {
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		drawChip( i, _map->getChipSize( ) / 2 );
	}
}

void Drawer::drawChip( int idx, int size ) {
		int map_type = _map->getMap( idx );
		int x = ( idx % Map::MAP_X_NUM ) * _map->getChipSize( ) + _map->getChipSize( ) / 2;
		int y = ( idx / Map::MAP_X_NUM ) * _map->getChipSize( ) + _map->getChipSize( ) * 5 / 2;
		int r = size;
		DrawCircle( x, y, r, getMapResource( map_type ), TRUE );
}

int Drawer::getMapResource( int type ) {
	switch ( type ) {
	case 0:
		return 0xff0000;
		break;
	case 1:
		return 0x00ff00;
		break;
	case 2:
		return 0x0000ff;
		break;
	case 3:
		return 0xffff00;
		break;
	case 4:
		return 0x00ffff;
		break;
	case 5:
		return 0xff00ff;
		break;
	default:
		return 0xffffff;
		break;
	}
}