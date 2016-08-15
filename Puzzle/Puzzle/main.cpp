#include "Framework.h"
#include "UI.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Chip.h"
#include "Map.h"
#include "Result.h"
#include "Scene.h"

void main( ) {
    FrameworkPtr fw = Framework::getInstance( );

    TaskPtr mouse = MousePtr( new Mouse );
    fw->addTask( Mouse::getTag( ), mouse );

    TaskPtr map = MapPtr( new Map );
    fw->addTask( Map::getTag( ), map );
    
    TaskPtr chip = ChipPtr( new Chip );
    fw->addTask( Chip::getTag( ), chip );
    
    TaskPtr ui = UIPtr( new UI );
    fw->addTask( UI::getTag( ), ui );

    TaskPtr result = ResultPtr( new Result );
    fw->addTask( Result::getTag( ), result );

    TaskPtr scene = ScenePtr( new Scene );
    fw->addTask( Scene::getTag( ), scene );

    TaskPtr drawer = DrawerPtr( new Drawer );
    fw->addTask( Drawer::getTag( ), drawer );
}
