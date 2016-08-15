#include "Result.h"
#include "UI.h"
#include "Chip.h"
#include "ChipSetting.h"
#include "Map.h"
#include "Mouse.h"

Result::Result( ) {
	_ui = UIPtr( new UI );
}

Result::~Result( ) {
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
	ChipSettingPtr chip_setting = ChipSetting::getTask( );
	ChipPtr chip = chip_setting->getChipPtr( );
	if ( mouse->getStatus( ) >= 2 ) {
		return false;
	}
	if ( _ui->canChangeNum( ) < 0 ) {
		return false;
	}
	if ( goal_type == TYPE::TYPE_NONE ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( chip->getChip( i ).type != chip->getChip( 0 ).type ) {
				return false;
			}
		}
	} else {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( chip->getChip( i ).type != goal_type ) {
				return false;
			}
		}
	}
	return true;
}
