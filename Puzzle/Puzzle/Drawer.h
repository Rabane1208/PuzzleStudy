#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Drawer );
PTR( Map );

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
	int getMapResource( int type );
private:
	MapPtr _map;
};

