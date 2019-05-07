#pragma once
//在游戏中加载地图
//创建地图
//创建英雄，炮灰和野怪
//在SelectHero界面中会有选择英雄的界面，   用户点击某个英雄，通过一个回调函数，返回一个hero_role参数，
//然后对这个参数进行判断   根据不同情况生成英雄

#include"cocos2d.h"
//#include"Scene/SelectHeroScene.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Buff.h"
#include"Core/Sprite/CannonFodder .h"
#include"Core/Sprite/Skill.h"
USING_NS_CC;
#define GameMapNodeBatchTagSkill				   902  
#define GameMapNodeBatchTagEnemy					903

//发射技能的速度
#define GameMapSkillVelocity						300
class GameMap: public Layer
{
public:
	//属性
	TMXTiledMap * _tileMap;
	Hero * hero1, *hero2;
	Vector<Buff*> BuffVector;    //存放Buff对象的容器
	Vector<CannonFodder*>CannonFodderVector;  //存放炮灰对象的容器
	Vec2 mouse_up;      //鼠标离开坐标
	Vec2 mouse_down;    //鼠标点下坐标
	bool ismousedown;
	Vec2 repair; //坐标修正量
	DrawNode* drawNode;
//方法
	static GameMap* createScene();
	virtual bool init();
	

	void setHero();//hero_role HeroRole);  //创建英雄
	void createBuff();  //创建Buff
	void createCannonFodder();  //创建炮灰
	void onEnter();//   重写onEnter 函数
	void onExit();   //重写onExit 函数

	void updateGame(float dt);  //刷新函数



	//以下为移动精灵函数
	bool onTouchBegan(Touch *touch, Event*unused_event);
	void onTouchEnded(Touch *touch, Event*unused_event);
	void onTouchMoved(Touch *touch, Event*unused_event);
	bool moveHero(Vec2 targetPosition);
	CREATE_FUNC(GameMap);
};