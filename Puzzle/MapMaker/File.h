#pragma once
#include "smart_ptr.h"
#include <string>

PTR( File );

class File {
public:
	File( );
	virtual ~File( );
public:
	void saveFile( std::string filename );
	void loadFile( std::string filename );
};

