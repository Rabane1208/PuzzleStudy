#include "Drawer.h"
#include "DxLib.h"
#include "Framework.h"
#include "Map.h"

DrawerPtr Drawer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( Drawer::getTag( ) ) );
}

Drawer::Drawer( ) {
}

Drawer::~Drawer( ) {
}

void Drawer::update( ) {
	drawMap( );
}

void Drawer::drawMap( ) {
	MapPtr map = Map::getTask( );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		switch ( map->getMap( i ) ) {
			case 0:

			break;
		}
	}
}
