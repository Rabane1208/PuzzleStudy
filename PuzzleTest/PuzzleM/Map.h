#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <array>
#include <string>

PTR( Map );

class Map : public Task {
public:
	static std::string getTag( ) { return "MAP"; }
	static MapPtr getTask( );
public:
	Map( );
	virtual ~Map( );
public:
	double getChipSize( );
	int getMap( int idx );
public:
	static const int MAP_X_NUM = 9;
	static const int MAP_Y_NUM = 17;
	static const int MAP_MAX = MAP_X_NUM * MAP_Y_NUM;
private:
	void update( );
private:
	double _chip_size;
	std::array< int, MAP_MAX >map;
};

