#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Result );

class Result : public Task {
public:
	static std::string getTag( ) { return "RESULT"; }
	static ResultPtr getTask( );
public:
	Result( );
	virtual ~Result( );
};

