#pragma once

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
class BattleHistory : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void BackToMain(cocos2d::Ref*pSender);
	CREATE_FUNC(BattleHistory);
};
