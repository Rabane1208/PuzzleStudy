#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include "Chip.h"

PTR( ChipSetting );
PTR( Mouse );
PTR( Map );
PTR( Chip );

class ChipSetting : public Task {
public:
	static std::string getTag( ) { return "CHIPSETTING"; }
	static ChipSettingPtr getTask( );
public:
	ChipSetting();
	virtual ~ChipSetting();
public:
	int getChangeNum( );
	void setInit( );
	ChipPtr getChipPtr( );
private:
	bool isLockInCross( int idx );
	void update( );
	void groupLock( int idx );
private:
	MousePtr _mouse;
	MapPtr _map;
	ChipPtr _chip;
	int mouse_idx;
	int _change_num;
};

