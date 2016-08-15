#include "UI.h"
#include "ChipSetting.h"

UI::UI( ) {
	_chip_setting = ChipSetting::getTask( );
}

UI::~UI( ) {
}

int UI::canChangeNum( ) {
	int can_change_num = 0;
	can_change_num = _chip_setting->getChangeNum( );
	return can_change_num;
}