#include "UI.h"
#include "Chip.h"
#include "Framework.h"

const int CHANGE_MAX = 9;

UIPtr UI::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< UI >( fw->getTask( UI::getTag( ) ) );
}

UI::UI( ) {
	_chip = Chip::getTask( );
}


UI::~UI( ) {
}

void UI::update( ) {
}

int UI::canChangeNum( ) {
	int can_change_num = 0;
	can_change_num = CHANGE_MAX - _chip->getChangeNum( );
	return can_change_num;
}