#include "Result.h"
#include "Framework.h"
#include "UI.h"
#include "Chip.h"
#include "Map.h"
#include "Mouse.h"

ResultPtr Result::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Result >( fw->getTask( Result::getTag( ) ) );
}

Result::Result( ) {
	_ui = UI::getTask( );
	_chip = Chip::getTask( );
}

Result::~Result( ) {
}

void Result::update( ) {

}

bool Result::isFail( ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getStatus( ) >= 2 ) {
		return false;
	}
	if ( _ui->canChangeNum( ) <= 0 ) {
		return true;
	}
	return false;
}

bool Result::isClear( TYPE goal_type ) {
	MousePtr mouse = Mouse::getTask( );
	if ( mouse->getStatus( ) >= 2 ) {
		return false;
	}
	if ( _ui->canChangeNum( ) < 0 ) {
		return false;
	}
	if ( goal_type == TYPE::TYPE_NONE ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).type != _chip->getChip( 0 ).type ) {
				return false;
			}
		}
	} else {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).type != goal_type ) {
				return false;
			}
		}
	}
	return true;
}
