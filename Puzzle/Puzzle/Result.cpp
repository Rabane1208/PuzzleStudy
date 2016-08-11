#include "Result.h"
#include "Framework.h"

ResultPtr Result::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Result >( fw->getTask( Result::getTag( ) ) );
}

Result::Result( ) {
}

Result::~Result( ) {
}
