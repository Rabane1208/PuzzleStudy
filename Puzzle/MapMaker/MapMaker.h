#pragma once
#include "smart_ptr.h"
#include <string>
#include "Task.h"
#include <vector>
#include "Chip.h"

PTR( MapMaker );
PTR( Chip );
PTR( Mouse );
PTR( Keyboard );
PTR( Map );
PTR( File );

enum STATE {
	STATE_INPUT_STAGE,
	STATE_SAVE_STAGE,
	STATE_LOAD_STAGE,
	STATE_MAPMAKER,
};

struct STAGE {
	int num;
	std::array< TYPE, Map::MAP_MAX > chip_type;
};

class MapMaker : public Task {
public:
	static std::string getTag( ) { return "MAPMAKER"; }
	static MapMakerPtr getTask( );
public:
	MapMaker( );
	virtual ~MapMaker( );
public:
	ChipPtr getChipPtr( );
	int getStageNum( );
	std::array< TYPE, Map::MAP_MAX > getChipType( int stage_num );
	void MapMaker::setChipType( int stage_num, std::array< TYPE, Map::MAP_MAX > chip_type );
private:
	void update( );
	void changeChip( );
	void inputStageNum( );
	void saveStage( );
	void loadStage( );
private:
	MapPtr _map;
	ChipPtr _chip;
	MousePtr _mouse;
	FilePtr _file;
	KeyboardPtr _keyboard;
	int mouse_idx;
	unsigned int _stage_num;
	STATE _state;
	std::vector< STAGE > data;
};

