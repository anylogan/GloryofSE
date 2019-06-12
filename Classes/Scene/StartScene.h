#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Scene/SettingScene.h"
#include"Scene/HelpScene.h"
#include"Scene/LoadingScene.h"
#include"Scene/LoginScene.h"
class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	//void menuItemStartCallback(cocos2d::Ref*pSender);
	//void menuItem2Callback(cocos2d::Ref*pSender);

	void menuItemLoginCallback(Ref *pSender);
	void menuItemSettingCallback(cocos2d::Ref*pSender);  //���ò˵��ص�
	void menuItemHelpCallback(cocos2d::Ref*pSender);   //  �����˵��ص�
	// implement the "static create()" method manually



	CREATE_FUNC(StartScene);
};

#endif // __HELLOWORLD_SCENE_H__
