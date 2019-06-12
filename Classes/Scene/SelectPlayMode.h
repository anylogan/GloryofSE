#pragma once

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Core/Net/Client.h"
#include"Core/Net/NetCommand.h"
USING_NS_CC;

class SelectPlayMode : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void OnlineModeCallBack(Ref *pSender);
	// a selector callback
	void SingleModeCallBack(Ref *pSender);
	void RuleCallBack(Ref *pSender);
	void BattleHistory(Ref * pSender);
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	CREATE_FUNC(SelectPlayMode);

};
