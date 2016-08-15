#include "Framework.h"
#include "UI.h"
#include "Drawer.h"
#include "Mouse.h"
#include "ChipSetting.h"
#include "Scene.h"

void main( ) {
    FrameworkPtr fw = Framework::getInstance( );

    TaskPtr mouse = MousePtr( new Mouse );
    fw->addTask( Mouse::getTag( ), mouse );
    
    TaskPtr chipSetting = ChipSettingPtr( new ChipSetting );
    fw->addTask( ChipSetting::getTag( ), chipSetting );

    TaskPtr scene = ScenePtr( new Scene );
    fw->addTask( Scene::getTag( ), scene );

    TaskPtr drawer = DrawerPtr( new Drawer );
    fw->addTask( Drawer::getTag( ), drawer );
}
