#include "Scene.h"
#include "Framework.h"
#include "Result.h"
#include "Mouse.h"
#include "Play.h"
#include "Select.h"

ScenePtr Scene::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Scene >( fw->getTask( Scene::getTag( ) ) );
}

Scene::Scene( ) {
	_result = ResultPtr( new Result );
	_mouse = Mouse::getTask( );
	_play = Play::getTask( );
	_select = SelectPtr( new Select );

	_scene = SCENE::SCENE_TITLE;
	_stage = 1;
	_stage_max = _select->getIconNum( );
}

Scene::~Scene( ) {
}

void Scene::update( ) {
	titleToSelect( );
	playToFail( );
	playToClear( );
	StageToPlay( );
	failToPlay( );
	clearToPlay( );
}

SCENE Scene::getScene( ) {
	return _scene;
}

int Scene::getStage( ) {
	return _stage;
}

void Scene::titleToSelect( ) {
	if ( _scene != SCENE::SCENE_TITLE ) {
		return;
	}
	if ( _mouse->getStatus( ) >= 2 ) {
		_scene = SCENE::SCENE_SELECT;
	}
}

void Scene::StageToPlay( ) {
	if ( _scene != SCENE::SCENE_SELECT ) {
		return;
	}
	if ( _mouse->getStatus( ) < 2 ) {
		return;
	}
	for ( int i = 0; i < _stage_max; i++ ) {
		bool x_min = _mouse->getPosX( ) < _select->getIconPosX( i ) - Select::ICON_SIZE / 2;
		bool x_max = _mouse->getPosX( ) > _select->getIconPosX( i ) + Select::ICON_SIZE / 2;
		bool y_min = _mouse->getPosY( ) < _select->getIconPosY( i ) - Select::ICON_SIZE / 2;
		bool y_max = _mouse->getPosY( ) > _select->getIconPosY( i ) + Select::ICON_SIZE / 2;
		if ( x_min ) {
			continue;
		}
		if ( x_max ) {
			continue;
		}
		if ( y_min ) {
			continue;
		}
		if ( y_max ) {
			continue;
		}
		_stage = i + 1;
		_scene = SCENE::SCENE_PLAY;
	}
}

void Scene::playToFail( ) {
	if ( _result->isFail( ) ) {
		_scene = SCENE::SCENE_FAIL;
	}
}

void Scene::playToClear( ) {
	if ( _result->isClear( TYPE::TYPE_NONE ) ) {
		_scene = SCENE::SCENE_CLEAR;
	}
}

void Scene::failToPlay( ) {
	if ( _scene != SCENE::SCENE_FAIL ) {
		return;
	}
	if ( _mouse->getStatus( ) >= 2 ) {
		_scene = SCENE::SCENE_PLAY;
	}
}

void Scene::clearToPlay( ) {
	if ( _scene != SCENE::SCENE_CLEAR ) {
		return;
	}
	if ( _mouse->getStatus( ) >= 2 ) {
		_scene = SCENE::SCENE_PLAY;
	}
}