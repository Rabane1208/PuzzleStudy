#include "File.h"

File::File( ) {
	filename = "stage.dat";
}

File::~File( ) {
}

void File::addStage( ) {

}

void File::deleteStage( ) {

}

void File::save( ) {
	FILE *fp;
	errno_t err = fopen_s( &fp, filename.c_str( ), "wb" );
	if ( err != 0 ) {
		return;
	}
}

void File::load( ) {
}
