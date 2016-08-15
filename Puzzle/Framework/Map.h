#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Map );
PTR( Mouse );


class Map : public Task {
public:
	static const int MAP_X_NUM = 7;
	static const int MAP_Y_NUM = 9;
	static const int MAP_MAX = MAP_X_NUM * MAP_Y_NUM;
public:
	static std::string getTag( ) { return "MAP"; }
	static MapPtr getTask( );
public:
	Map( );
	virtual ~Map( );
public:
	int getChipSize( );
	int posToIdx( int x, int y );
private:
	void update( );
private:
	int _chip_size;
};

