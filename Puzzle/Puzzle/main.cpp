#include "Framework.h"
#include "UI.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Play.h"
#include "Scene.h"

void main( ) {
    FrameworkPtr fw = Framework::getInstance( );

    TaskPtr mouse = MousePtr( new Mouse );
    fw->addTask( Mouse::getTag( ), mouse );
    
    TaskPtr play = PlayPtr( new Play );
    fw->addTask( Play::getTag( ), play );

    TaskPtr scene = ScenePtr( new Scene );
    fw->addTask( Scene::getTag( ), scene );

    TaskPtr drawer = DrawerPtr( new Drawer );
    fw->addTask( Drawer::getTag( ), drawer );
}
