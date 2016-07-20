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
	int mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	if ( chip[ mouse_idx ].status != STATUS::STATUS_LOCKED ) {
		chip[ mouse_idx ].status = STATUS::STATUS_LOCKED;
	} else {
		chip[ mouse_idx ].type = ( TYPE )( ( chip[ mouse_idx ].type + 1 ) % TYPE::TYPE_MAX );
		chip[ mouse_idx ].status = STATUS::STATUS_NONE;
		if ( chip[ mouse_idx ].type == TYPE::TYPE_NONE ) {
			chip[ mouse_idx ].type = TYPE::TYPE_A;
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