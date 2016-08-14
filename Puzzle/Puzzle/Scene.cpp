#include "Scene.h"
#include "Framework.h"
#include "Result.h"
#include "Mouse.h"
#include "Chip.h"

ScenePtr Scene::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Scene >( fw->getTask( Scene::getTag( ) ) );
}

Scene::Scene( ) {
	_result = Result::getTask( );
	_mouse = Mouse::getTask( );
	_scene = SCENE::SCENE_TITLE;
}

Scene::~Scene( ) {
}

void Scene::update( ) {
	titleToPlay( );
	playToFail( );
	playToClear( );
	failToPlay( );
	clearToPlay( );
}

SCENE Scene::getScene( ) {
	return _scene;
}

void Scene::titleToPlay( ) {
	if ( _scene != SCENE::SCENE_TITLE ) {
		return;
	}
	if ( _mouse->getStatus( ) >= 2 ) {
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
	ChipPtr chip = Chip::getTask( );
	if ( _mouse->getStatus( ) >= 2 ) {
		chip->setInit( );
		_scene = SCENE::SCENE_PLAY;
	}
}

void Scene::clearToPlay( ) {
	if ( _scene != SCENE::SCENE_CLEAR ) {
		return;
	}
	ChipPtr chip = Chip::getTask( );
	if ( _mouse->getStatus( ) >= 2 ) {
		chip->setInit( );
		_scene = SCENE::SCENE_PLAY;
	}
}