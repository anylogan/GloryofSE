#pragma once
#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
#include"proj.win32/MyUtility.h"
using namespace cocos2d::ui;
using namespace CocosDenshion;
class HelpScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuItemGoBackCallback(cocos2d::Ref*pSender);

	/*void menuSoundCallback(cocos2d::Ref*pSender);
	void menuMusicCallback(cocos2d::Ref*pSender);*/
	// implement the "static create()" method manually
	CREATE_FUNC(HelpScene);
};