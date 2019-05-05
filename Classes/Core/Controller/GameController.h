#pragma once
#include"cocos2d.h"
#include"Scene/SelectHeroScene.h"
#include"Scene/GameScene.h"
#include"Core/Sprite/Hero.h"
USING_NS_CC;
class GameController : public Scene    //游戏控制类
{
public:
//属性
	Sprite * hero1, *hero2;
	Layer *map;


//方法




	virtual bool init();
	void createHero();//hero_role HeroRole);  //创建英雄
	static cocos2d::Scene* createScene();


	//判断英雄是否死亡
	//判断游戏是否结束
	//判断小兵是否死亡
	//判断Buff是否死亡
	//英雄复活函数
	

	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameController);

};