#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Chip.h"
#include <string>

PTR( Drawer );
PTR( Map );
PTR( Chip );
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
	void drawChip( int idx, int size );
	void drawUI( );
	void drawBackground( );
	void drawNum( int x, int y, int num );
	void drawClear( );
	void drawFail( );
	void drawTitle( );
	int getChipIMG( TYPE type );
private:
	ChipPtr _chip;
	MapPtr _map;
	ScenePtr _scene;
private:
	int _num_img;
	int _chip_img;
	int _background_img;
	int _seeweed_img;
	int _ani_timer;
};

