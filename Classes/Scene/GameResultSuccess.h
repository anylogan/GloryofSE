#pragma once

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
class GameResultSuccess : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void BackToMain(float dt);
	CREATE_FUNC(GameResultSuccess);
};
