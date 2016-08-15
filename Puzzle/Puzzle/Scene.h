#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Scene );
PTR( Result );
PTR( Mouse );
PTR( ChipSetting );

enum SCENE {
	SCENE_TITLE,
	SCENE_STAGE,
	SCENE_PLAY,
	SCENE_FAIL,
	SCENE_CLEAR,
	SCENE_OPTION,
	SCENE_MAX,
};

class Scene : public Task {
public:
	static std::string getTag( ) { return "SCENE"; }
	static ScenePtr getTask( );
public:
	Scene( );
	virtual ~Scene( );
public:
	SCENE getScene( );
private:
	void update( );
	void titleToPlay( );
	void playToFail( );
	void playToClear( );
	void failToPlay( );
	void clearToPlay( );
private:
	ResultPtr _result;
	MousePtr _mouse;
	SCENE _scene;
	ChipSettingPtr _chip_setting;
};

