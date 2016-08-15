#include "ChipSetting.h"
#include "Framework.h"
#include "DxLib.h"
#include "Map.h"
#include "Mouse.h"
#include "Scene.h"
#include "Chip.h"

const int CHANGE_MAX = 9;

ChipSettingPtr ChipSetting::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< ChipSetting >( fw->getTask( ChipSetting::getTag( ) ) );
}

ChipSetting::ChipSetting( ) {
	_mouse = Mouse::getTask( );
	_map = MapPtr( new Map );
	_chip = ChipPtr( new Chip );
	
	setInit( );
}

ChipSetting::~ChipSetting( ) {
}

void ChipSetting::update( ) {
	if ( _mouse->getStatus( ) != 1 ) {
		return;
	}
	ScenePtr scene = Scene::getTask( ); 
	if ( scene->getScene( ) != SCENE::SCENE_PLAY ) {
		return;
	}

	//�ႤChip��Click������A������
	int before_idx = mouse_idx;
	mouse_idx = _map->posToIdx( _mouse->getPosX( ), _mouse->getPosY( ) );
	if ( mouse_idx == -1 ) { //Chip����Ȃ�������return
		return;
	}
	if ( before_idx != mouse_idx && _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			_chip->setStatus( i, STATUS::STATUS_NONE );
		}
	}

	//Lock����ĂȂ�Chip��Click������ALock����
	if ( _chip->getChip( mouse_idx ).status != STATUS::STATUS_LOCKED ) {
		_chip->setStatus( mouse_idx, STATUS::STATUS_LOCKED );
		groupLock( mouse_idx );
	} else { //Lock���ꂽChip��Click������A�F��ς���Lock������
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).status != STATUS::STATUS_LOCKED ) {
				continue;
			}
			_chip->setType( i, ( TYPE )( ( _chip->getChip( i ).type + 1 ) % TYPE::TYPE_MAX ) );
			_chip->setStatus( i, STATUS::STATUS_NONE );
			if ( _chip->getChip( i ).type == TYPE::TYPE_NONE ) {
				_chip->setType( i, TYPE::TYPE_OCTOPUS );
			}
		}
		_change_num++;
	}
}

bool ChipSetting::isLockInCross( int idx ) {
	//�E������
	if ( idx % Map::MAP_X_NUM != ( Map::MAP_X_NUM - 1 ) ) {
		if ( _chip->getChip( idx + 1 ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//��������
	if ( idx % Map::MAP_X_NUM != 0 ) {
		if ( _chip->getChip( idx - 1 ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//�������
	if ( idx >= Map::MAP_X_NUM ) {
		if ( _chip->getChip( idx - Map::MAP_X_NUM ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	//��������
	if ( idx < Map::MAP_MAX - Map::MAP_X_NUM ) {
		if ( _chip->getChip( idx + Map::MAP_X_NUM ).status == STATUS::STATUS_LOCKED ) {
			return true;
		}
	}
	return false;
}

void ChipSetting::groupLock( int idx ) {
	for ( int j = 0; j < Map::MAP_X_NUM + Map::MAP_Y_NUM; j++ ) { //���ʂɃ������g���Ă���B�����K�v������B
		for ( int i = 0; i < Map::MAP_MAX; i++ ) {
			if ( _chip->getChip( i ).type != _chip->getChip( idx ).type ) {
				continue;
			}
			if ( isLockInCross( i ) ) {
				_chip->setStatus( i, STATUS::STATUS_LOCKED );
			}
		}
	}
}

void ChipSetting::setInit( ) {
	_change_num = 0;

	for ( int i = 0; i < Map::MAP_MAX; i++ ) {
		//chip[ i ].type = ( TYPE )( GetRand( 4 ) + 1 );
		_chip->setType( i, TYPE::TYPE_OCTOPUS );
		_chip->setStatus( i, STATUS::STATUS_NONE );
	}
	_chip->setType( 0, TYPE::TYPE_BLOWFISH );
}

int ChipSetting::getChangeNum( ) {
	return CHANGE_MAX - _change_num;
}

ChipPtr ChipSetting::getChipPtr( ) {
	return _chip;
}
