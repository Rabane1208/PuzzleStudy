#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <array>
#include <string>

PTR( Map );
PTR( Mouse );

class Map : public Task {
public:
	static const int MAP_X_NUM = 9;
	static const int MAP_Y_NUM = 12;
	static const int MAP_MAX = MAP_X_NUM * MAP_Y_NUM;
public:
	static std::string getTag( ) { return "MAP"; }
	static MapPtr getTask( );
public:
	Map( );
	virtual ~Map( );
public:
	int getChipSize( );
	int getMap( int idx );
	int posToIdx( int x, int y );
	bool isPush( int idx );
private:
	void update( );
private:
	int _chip_size;
	std::array< int, MAP_MAX >map;
	MousePtr _mouse;
};

