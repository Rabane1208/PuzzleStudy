#include "UI.h"
#include "Framework.h"

UIPtr UI::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< UI >( fw->getTask( UI::getTag( ) ) );
}

UI::UI( ) {
}


UI::~UI( ) {
}

void UI::update( ) {
}
