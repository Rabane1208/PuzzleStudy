#include "Select.h"
#include "sstream"

const int MAX_ICON_IN_LINE = 4;

Select::Select( ) {
}

Select::~Select( ) {
}

void Select::makeIcon( ) {

}

int Select::getIconPosX( int idx ) {
	int x = ICON_SIZE * ( idx % MAX_ICON_IN_LINE ) + ICON_SIZE;
	return x;
}

int Select::getIconPosY( int idx ) {
	int y = ICON_SIZE * ( idx / MAX_ICON_IN_LINE ) + ICON_SIZE;
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
