#pragma once
//考虑在选择英雄的时候背景音是王者荣耀中英雄专属的那种
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Core/Controller/GameScene.h"
#include"Core/Controller/GameController.h"
USING_NS_CC;



typedef enum {
	daji = 0,    //妲己
	houyi = 1,     //后羿
	yase = 2,   //亚瑟

}hero_role;


//hero_role HeroRole=daji; //定义一个全局变量  并且初始化
//extern hero_role HeroRole; 

class SelectHeroScene :public Scene
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

	void DajiCallback(Ref *pSender);

    // implement the "static create()" method manually



	CREATE_FUNC(SelectHeroScene);


};