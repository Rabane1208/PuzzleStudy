#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( UI );
PTR( Chip );

class UI : public Task {
public:
	const int UI_UP_LENGTH = 2;
public:
	static std::string getTag( ) { return "UI"; }
	static UIPtr getTask( );
public:
	UI( );
	virtual ~UI( );
public:
	int canChangeNum( );
private:
	void update( );
private:
	ChipPtr _chip;
};

