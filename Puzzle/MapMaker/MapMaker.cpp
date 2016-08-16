#include "MapMaker.h"
#include "Framework.h"
#include "Chip.h"
#include "Mouse.h"

MapMakerPtr MapMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< MapMaker >( fw->getTask( MapMaker::getTag( ) ) );
}

MapMaker::MapMaker( ) {
	_chip = ChipPtr( new Chip );
	_map = MapPtr( new Map );
	_mouse = Mouse::getTask( );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, TYPE::TYPE_OCTOPUS );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
}

MapMaker::~MapMaker( ) {
}

void MapMaker::update( ) {
	if ( _mouse->getStatus( ) != 1 ) {
		return;
	}

	//違うChipをClickしたら、初期化
	int before_idx = mouse_idx;
	mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	if ( mouse_idx == -1 ) { //Chipじゃなかったらreturn
		return;
	}
	if ( before_idx != mouse_idx && _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			_chip->setStatus( i, STATUS::STATUS_NONE );
		}
	}

	//LockされてないChipをClickしたら、Lockする
	if ( _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		_chip->setStatus( mouse_idx, STATUS::STATUS_LOCKED );
	}
	else { //LockされたChipをClickしたら、色を変えてLockを解除
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).status != STATUS::STATUS_LOCKED ) {
				continue;
			}
			_chip->setType( i, ( TYPE ) ( ( _chip->getChip( i ).type + TYPE::TYPE_MAX - 1 ) % TYPE::TYPE_MAX ) );
			_chip->setStatus( i, STATUS::STATUS_NONE );
		}
	}
}

ChipPtr MapMaker::getChipPtr( ) {
	return _chip;
}

