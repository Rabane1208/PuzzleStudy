#include "Result.h"
#include "UI.h"
#include "Chip.h"
#include "Play.h"
#include "Map.h"
#include "Mouse.h"
#include "Scene.h"

Result::Result( ) {
	_ui = UIPtr( new UI );
}

Result::~Result( ) {
}

bool Result::isFail( ) {
	MousePtr mouse = Mouse::getTask( );
	ScenePtr scene = Scene::getTask( );
	PlayPtr play = Play::getTask( );
	if ( mouse->getStatus( ) >= 2 ) {
		return false;
	}
	if ( _ui->canChangeNum( ) <= 0 ) {
		play->setInit( scene->getStage( ) );
		return true;
	}
	return false;
}

bool Result::isClear( TYPE goal_type ) {
	MousePtr mouse = Mouse::getTask( );
	ScenePtr scene = Scene::getTask( );
	PlayPtr play = Play::getTask( );
	ChipPtr chip = play->getChipPtr( );
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
	int t = scene->getStage( );
	play->setInit( t );
	return true;
}
