#pragma once
#include "smart_ptr.h"
#include <string>

PTR( UI );
PTR( ChipSetting );

class UI {
public:
	UI( );
	virtual ~UI( );
public:
	int canChangeNum( );
private:
	ChipSettingPtr _chip_setting;
};

