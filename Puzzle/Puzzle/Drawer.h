#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "ChipSetting.h"
#include <string>

PTR( Drawer );
PTR( Map );
PTR( ChipSetting );
PTR( Scene );

class Drawer : public Task {
public:
	static std::string getTag( ) { return "DRAWER"; }
	static DrawerPtr getTask( );
public:
	Drawer( );
	virtual ~Drawer( );
private:
	void update( );
	void drawMap( );
	void drawUI( );
	void drawBackground( );
	void drawNum( int x, int y, int num );
	void drawClear( );
	void drawFail( );
	void drawTitle( );
private:
	ChipSettingPtr _chip_setting;
	MapPtr _map;
	ScenePtr _scene;
private:
	int _num_img;
	int _background_img;
	int _seeweed_img;
	int _ani_timer;
};

