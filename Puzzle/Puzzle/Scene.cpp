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
}

Scene::~Scene( ) {
}

void Scene::update( ) {
	StageToPlay( );
	titleToSelect( );
	playToFail( );
	playToClear( );
	failToPlay( );
	clearToPlay( );
}

SCENE Scene::getScene( ) {
	return _scene;
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
	if ( _select->selectStage( ) ) {
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

void Scene::option( ) {
	if ( _mouse->getStatus( ) >= 2 ) {
		_scene = SCENE::SCENE_PLAY;
	}
}