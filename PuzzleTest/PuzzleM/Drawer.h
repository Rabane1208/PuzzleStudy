#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Drawer );

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
};

