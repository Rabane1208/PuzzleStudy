#include "MapMaker.h"
#include "Framework.h"
#include "DxLib.h"
#include "Mouse.h"
#include "Keyboard.h"

const int INPUT_X = 105;
const int INPUT_Y = 100;
const int STAGE_MAX = 999;
const int STAGE_MIN = 1;

MapMakerPtr MapMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< MapMaker >( fw->getTask( MapMaker::getTag( ) ) );
}

MapMaker::MapMaker( ) {
	_chip = ChipPtr( new Chip );
	_map = MapPtr( new Map );
	_mouse = Mouse::getTask( );
	_keyboard = Keyboard::getTask( );
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, TYPE::TYPE_OCTOPUS );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
	_stage_num = 1;
	_state = STATE::STATE_MAPMAKER;
}

MapMaker::~MapMaker( ) {
}

void MapMaker::update( ) {
	switch ( _state ) {
	case STATE_INPUT_STAGE:
		inputStageNum( );
		break;
	case STATE_SAVE_STAGE:
		saveStage( );
		break;
	case STATE_LOAD_STAGE:
		loadStage( );
		break;
	case STATE_MAPMAKER:
		changeChip( );
		break;
	default:
		break;
	}

	if ( _keyboard->isPushKey( "F1" ) ) {
		_state = STATE::STATE_INPUT_STAGE;
	}
	if ( _keyboard->isPushKey( "F3" ) ) {
		_state = STATE::STATE_LOAD_STAGE;
	}
	if ( _keyboard->isPushKey( "F4" ) ) {
		_state = STATE::STATE_SAVE_STAGE;
	}
}

void MapMaker::changeChip( ) {
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

void MapMaker::inputStageNum( ) {
	DrawString( 0, 100, "STAGE NUM : ", GetColor( 255, 255, 255 ) );
	_stage_num = KeyInputNumber( INPUT_X, INPUT_Y, STAGE_MAX, STAGE_MIN, TRUE );

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, TYPE::TYPE_OCTOPUS );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
	_state = STATE::STATE_MAPMAKER;
}

void MapMaker::saveStage( ) {
	data[ _stage_num ].num = _stage_num;
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		data[ _stage_num ].chip_type[ i ] = _chip->getChip( i ).type;
	}
	_state = STATE::STATE_MAPMAKER;
}

void MapMaker::loadStage( ) {
	if ( data[ _stage_num ].num == NULL ) {
		_state = STATE::STATE_MAPMAKER;
		return;
	}
	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		_chip->setType( i, data[ _stage_num ].chip_type[ i ] );
	}
	_state = STATE::STATE_MAPMAKER;
}

int MapMaker::getStageNum( ) {
	return _stage_num;
}

ChipPtr MapMaker::getChipPtr( ) {
	return _chip;
}
