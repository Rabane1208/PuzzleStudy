#pragma once
#include "smart_ptr.h"
#include <string>

PTR( File );

class File {
public:
	File( );
	virtual ~File( );
public:
	void deleteStage( );
	void addStage( );
	void save( );
	void load( );
private:
	std::string filename;
};

