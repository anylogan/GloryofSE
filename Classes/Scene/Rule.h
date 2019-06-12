#pragma once
#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"proj.win32/MyUtility.h"
using namespace cocos2d::ui;
using namespace CocosDenshion;
class Rule : public cocos2d::Scene
{
public:
	static Rule* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuItemGoBackCallback(cocos2d::Ref*pSender);

	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	CREATE_FUNC(Rule);
};