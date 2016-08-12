#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Result );
PTR( UI );

class Result : public Task {
public:
	static std::string getTag( ) { return "RESULT"; }
	static ResultPtr getTask( );
public:
	Result( );
	virtual ~Result( );
public:
	bool isFail( );
	bool isClear( );
private:
	void update( );
private:
	UIPtr _ui;
};

