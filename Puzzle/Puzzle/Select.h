#pragma once
#include "DxLib.h"
#include "smart_ptr.h"
#include <vector>

PTR( Select );

class Select {
public:
	static const int ICON_SIZE = 30;
public:
	Select( );
	virtual ~Select( );
public:
	int getIconPosX( int idx );
	int getIconPosY( int idx );
	int getIconNum( );
private:
	void makeIcon( );
	std::vector< DxLib::VECTOR > _icon;
private:
	VECTOR _pos;
};

