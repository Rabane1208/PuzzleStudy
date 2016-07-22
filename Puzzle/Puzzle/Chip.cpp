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

	int before_idx = mouse_idx;
	mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );

	//違うChipをClickしたら、初期化
	if ( before_idx != mouse_idx && chip[ mouse_idx ].status != STATUS::STATUS_LOCKED ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			chip[ i ].status = STATUS::STATUS_NONE;
		}
	}

	std::vector< int > group = searchGroup( mouse_idx );
	//LockされてないChipをClickしたら、Lockする
	if ( chip[ mouse_idx ].status != STATUS::STATUS_LOCKED ) {
		for ( unsigned int i = 0; i < group.size( ); i++ ) {
			chip[ group[ i ] ].status = STATUS::STATUS_LOCKED;
		}
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
}

std::vector< int > Chip::searchGroup( int idx ) {
	std::vector< int > group;

	group.push_back( idx );

	//右を検査
	if ( idx % Map::MAP_X_NUM != ( Map::MAP_X_NUM - 1 ) ) {
		if ( chip[ idx ].type == chip[ idx + 1 ].type ) {
			group.push_back( idx + 1 );
		}
	}
	//左を検査
	if ( idx % Map::MAP_X_NUM != 0 ) {
		if ( chip[ idx ].type == chip[ idx - 1 ].type ) {
			group.push_back( idx - 1 );
		}
	}
	//上を検査
	if ( idx >= Map::MAP_X_NUM ) {
		if ( chip[ idx ].type == chip[ idx - Map::MAP_X_NUM ].type ) {
			group.push_back( idx - Map::MAP_X_NUM );
		}
	}
	//下を検査
	if ( idx <= Map::MAP_MAX - Map::MAP_X_NUM ) {
		if ( chip[ idx ].type == chip[ idx + Map::MAP_X_NUM ].type ) {
			group.push_back( idx + Map::MAP_X_NUM );
		}
	}

	return group;
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