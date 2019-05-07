#pragma once

#include"cocos2d.h"

#include"Scene/SelectHeroScene.h"
//包含层类头文件
#include"Scene/ButtonLayer.h"

//包含精灵类头文件
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Buff.h"
#include"Core/Sprite/CannonFodder .h"
#include"Core/Sprite/Tower.h"
USING_NS_CC;
class GameController : public Layer   //游戏控制类
{
	
public:
//属性
	//层属性
	ButtonLayer*button;
	//
	//属性
	TMXTiledMap * _tileMap;
	Hero * hero1, *hero2;
	Vector<Buff*> BuffVector;    //存放Buff对象的容器
	Vector<CannonFodder*>CannonFodderVector;  //存放炮灰对象的容器
	Vector<Tower*>TowerVector;      //存放塔指针的容器
	Vec2 mouse_up;      //鼠标离开坐标
	Vec2 mouse_down;    //鼠标点下坐标
	bool ismousedown;
	char *bigSkillFormat;    //大招路径
	char *mediumSkillFormat;  //中招路径
	char *smallSkillFormat;   //小招路径
	int bigSkillNum;    //大招动画的照片数
	int mediumSkillNum;    //大招动画的照片数
	int smallSkillNum;    //大招动画的照片数
//方法

    static GameController* createScene(); //创建对象
	virtual bool init(); //初始化控制层

	void onEnter();//   重写onEnter 函数
	void onExit();   //重写onExit 函数


	void createHero();//hero_role HeroRole);  //创建英雄
	void createBuff();  //创建Buff
	void createCannonFodder();  //创建炮灰
	void createTower();    //创建塔

	void updateGame(float dt);  //刷新函数

	void CannonFodderMoving();   //炮灰移动函数
	void backHome();  //回城



	bool isHeroDeath();           //判断英雄是否死亡
	bool isCannonFodderDeath(); //判断炮灰是否死亡
	bool isBuffDeath();         //判断Buff是否死亡
	bool isHeroResurrection();//英雄复活函数
	bool isGameOver(); //判断游戏是否结束
	bool isTowerPushed();   //判断塔是否被推
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameController);    

};