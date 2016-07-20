#include "Framework.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Chip.h"
#include "Map.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	
	TaskPtr mouse = MousePtr( new Mouse );
	fw->addTask( Mouse::getTag( ), mouse );

	TaskPtr map = MapPtr( new Map );
	fw->addTask( Map::getTag( ), map );

	TaskPtr chip = ChipPtr( new Chip );
	fw->addTask( Chip::getTag( ), chip );

	TaskPtr drawer = DrawerPtr( new Drawer );
	fw->addTask( Drawer::getTag( ), drawer );
}