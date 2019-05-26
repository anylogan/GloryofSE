#pragma once
//考虑在选择英雄的时候背景音是王者荣耀中英雄专属的那种
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Core/Controller/GameScene.h"
#include"Core/Controller/GameController.h"
#include"Scene/GlobalDefine.h"
USING_NS_CC;


//hero_role HeroRole=moonGoddess; //定义一个全局变量  并且初始化
//extern hero_role HeroRole; 

class SelectHeroScene :public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void ChangeCallBack(Ref *pSender);
	void HuamulanCallBack(Ref *pSender);
	void SunCallBack(Ref *pSender);

    // implement the "static create()" method manually

	CREATE_FUNC(SelectHeroScene);


};