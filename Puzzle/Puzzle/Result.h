#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "Chip.h"
#include <string>

PTR( Result );
PTR( UI );
PTR( Chip );

class Result : public Task {
public:
	static std::string getTag( ) { return "RESULT"; }
	static ResultPtr getTask( );
public:
	Result( );
	virtual ~Result( );
public:
	bool isFail( );
	bool isClear( TYPE goal_type );
private:
	void update( );
private:
	UIPtr _ui;
	ChipPtr _chip;
};

