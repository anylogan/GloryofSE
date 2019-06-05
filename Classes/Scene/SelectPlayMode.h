#pragma once

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;

class SelectPlayMode : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void OnlineModeCallBack(Ref *pSender);
	// a selector callback
	void SingleModeCallBack(Ref *pSender);
	CREATE_FUNC(SelectPlayMode);
};
