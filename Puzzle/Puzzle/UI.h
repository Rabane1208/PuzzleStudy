#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( UI );

class UI : public Task {
public:
	static std::string getTag( ) { return "UI"; }
	static UIPtr getTask( );
public:
	UI( );
	virtual ~UI( );
private:
	void update( );
};

