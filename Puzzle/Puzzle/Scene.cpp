#include "Scene.h"
#include "Framework.h"
#include "Result.h"

ScenePtr Scene::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Scene >( fw->getTask( Scene::getTag( ) ) );
}

Scene::Scene( ) {
	_result = Result::getTask( );
}

Scene::~Scene( ) {
}

void Scene::update( ) {

}

SCENE Scene::getScene( ) {
	if ( _result->isFail( ) ) {
		return SCENE::SCENE_FAIL;
	}
	if ( _result->isClear( TYPE::TYPE_NONE ) ) {
		return SCENE::SCENE_CLEAR;
	}
	return SCENE::SCENE_PLAY;
}