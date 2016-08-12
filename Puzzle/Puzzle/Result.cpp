#include "Result.h"
#include "Framework.h"
#include "UI.h"

ResultPtr Result::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Result >( fw->getTask( Result::getTag( ) ) );
}

Result::Result( ) {
	_ui = UI::getTask( );
}

Result::~Result( ) {
}

void Result::update( ) {

}

bool Result::isFail( ) {
	if ( _ui->canChangeNum( ) <= 0 ) {
		return true;
	}
	return false;
}

bool Result::isClear( ) {
	return false;
}
