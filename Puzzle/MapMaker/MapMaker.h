#pragma once
#include "smart_ptr.h"
#include <string>
#include "Task.h"

PTR( MapMaker );
PTR( Chip );
PTR( Mouse );
PTR( Map );

class MapMaker : public Task {
public:
	static std::string getTag( ) { return "MAPMAKER"; }
	static MapMakerPtr getTask( );
public:
	MapMaker( );
	virtual ~MapMaker( );
public:
	ChipPtr getChipPtr( );
private:
	void update( );
	MapPtr _map;
	ChipPtr _chip;
	MousePtr _mouse;
	int mouse_idx;
};

