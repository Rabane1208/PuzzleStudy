#include "Select.h"
#include "sstream"
#include "Framework.h"

const int MAX_ICON_IN_LINE = 4;
const int MAX_LINE = 5;

Select::Select( ) {
}

Select::~Select( ) {
}

void Select::makeIcon( ) {

}

int Select::getIconPosX( int idx ) {
	FrameworkPtr fw = Framework::getInstance( );
	int dis = fw->getWindowWidth( ) / ( MAX_ICON_IN_LINE + 1 );
	int x = dis * ( idx % MAX_ICON_IN_LINE ) + dis;
	return x;
}

int Select::getIconPosY( int idx ) {
	FrameworkPtr fw = Framework::getInstance( );
	int dis = fw->getWindowHeight( ) / ( MAX_LINE + 1 );
	int y = dis * ( idx / MAX_ICON_IN_LINE ) + dis;
	return y;
}

int Select::getIconNum( ) {
	FILE *fh;

	std::string         filename;
	std::ostringstream  ost;
	int i = 1;
	while ( 1 ) {
		filename.clear( );
		ost.str( "" );
		ost << i;
		filename += "../Data/Map/" + ost.str( ) + ".map";
		errno_t err = fopen_s( &fh, filename.c_str( ), "rb" );
		if ( err != 0 ) {
			break;
		}
		i++;
	}

	return i - 1;
}
