#include "Chip.h"
#include "Framework.h"
#include "DxLib.h"
#include "Map.h"
#include "Mouse.h"

ChipPtr Chip::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Chip >( fw->getTask( Chip::getTag( ) ) );
}

Chip::Chip( ) {
	_mouse = Mouse::getTask( );
	_map = Map::getTask( );

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		chip[ i ].type = ( TYPE )( GetRand( 5 ) + 1 );
		chip[ i ].status = STATUS::STATUS_NONE;
	}
}

Chip::~Chip( ) {
}

void Chip::update( ) {
	if ( _mouse->getStatus( ) != 1 ) {
		return;
	}

	//違うChipをClickしたら、初期化
	int before_idx = mouse_idx;
	mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	if ( before_idx != mouse_idx && chip[ mouse_idx ].status != STATUS::STATUS_LOCKED ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			chip[ i ].status = STATUS::STATUS_NONE;
		}
	}

	//LockされてないChipをClickしたら、Lockする
	//std::vector< int > group = scanCross( mouse_idx );
	if ( chip[ mouse_idx ].status != STATUS::STATUS_LOCKED ) {
		chip[ mouse_idx ].status = STATUS::STATUS_LOCKED;
		groupLock( mouse_idx );
	} else { //LockされたChipをClickしたら、色を変えてLockを解除
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( chip[ i ].status != STATUS::STATUS_LOCKED ) {
				continue;
			}
			chip[ i ].type = ( TYPE )( ( chip[ i ].type + 1 ) % TYPE::TYPE_MAX );
			chip[ i ].status = STATUS::STATUS_NONE;
			if ( chip[ i ].type == TYPE::TYPE_NONE ) {
				chip[ i ].type = TYPE::TYPE_A;
			}
		}
	}
	//group.clear( );
}

bool Chip::isLockInCross( int idx ) {
	//右を検査
	if ( idx % Map::MAP_X_NUM != ( Map::MAP_X_NUM - 1 ) ) {
		if ( chip[ idx + 1 ].status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//左を検査
	if ( idx % Map::MAP_X_NUM != 0 ) {
		if ( chip[ idx - 1 ].status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//上を検査
	if ( idx >= Map::MAP_X_NUM ) {
		if ( chip[ idx - Map::MAP_X_NUM ].status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//下を検査
	if ( idx < Map::MAP_MAX - Map::MAP_X_NUM ) {
		if ( chip[ idx + Map::MAP_X_NUM ].status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	return false;
}

void Chip::groupLock( int idx ) {
	for ( int j = 0; j < Map::MAP_X_NUM + Map::MAP_Y_NUM; j++ ) { //無駄にメモリ使っている。直す必要がある。
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( chip[ i ].type != chip[ idx ].type ) {
				continue;
			}
			if ( isLockInCross( i ) ) {
				chip[ i ].status = STATUS::STATUS_LOCKED;
			}
		}
	}
}


void Chip::setType( int idx, TYPE type ) {
	chip[ idx ].type = type;
}

void Chip::setStatus( int idx, STATUS status ) {
	chip[ idx ].status = status;
}

CHIP Chip::getChip( int idx ) {
	return chip[ idx ];
}