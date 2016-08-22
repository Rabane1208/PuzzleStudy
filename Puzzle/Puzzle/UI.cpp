#include "UI.h"
#include "Play.h"

UI::UI( ) {
	_play = Play::getTask( );
}

UI::~UI( ) {
}

int UI::canChangeNum( ) {
	int can_change_num = 0;
	can_change_num = _play->getChangeNum( );
	return can_change_num;
}