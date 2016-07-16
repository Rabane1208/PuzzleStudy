#include "Drawer.h"
#include "Framework.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	
	TaskPtr drawer = DrawerPtr( new Drawer );
	fw->addTask( Drawer::getTag( ), drawer );
}