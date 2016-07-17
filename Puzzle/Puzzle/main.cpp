#include "Drawer.h"
#include "Mouse.h"
#include "Map.h"
#include "Framework.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	
	TaskPtr mouse = MousePtr( new Mouse );
	fw->addTask( Mouse::getTag( ), mouse );
	TaskPtr map = MapPtr( new Map );
	fw->addTask( Map::getTag( ), map );
	TaskPtr drawer = DrawerPtr( new Drawer );
	fw->addTask( Drawer::getTag( ), drawer );
}