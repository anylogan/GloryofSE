#pragma once

#include"cocos2d.h"

#include"Scene/SelectHeroScene.h"
//包含层类头文件
#include"Scene/ButtonLayer.h"

//包含精灵类头文件
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/EnemySoldier.h"
#include"Core/Sprite/CannonFodder .h"
#include"Core/Sprite/Tower.h"
#include"Core/Sprite/fieldMonster.h"
#include"Core/Sprite/EnemySoldier.h"

USING_NS_CC;
//全局变量
extern int playMoney;

class GameController : public Layer   //游戏控制类
{
	
public:
//属性
	//层属性
	ButtonLayer*button;
	//
	//属性
	TMXTiledMap * _tileMap;
	TMXLayer * _collidable;
	Hero * hero1, *hero2;
	Vector<EnemySoldier*> clientSoldierVector;    //存放EnemySoldier对象的容器
	fieldMonster* monster1;
    fieldMonster* monster2;
	Vector<Tower*>TowerVector;				//存放塔指针的容器
	bool ismousedown;
	char *bigSkillFormat;    //大招路径
	char *mediumSkillFormat;  //中招路径
	char *smallSkillFormat;   //小招路径
	int bigSkillNum;    //大招动画的照片数
	int mediumSkillNum;    //大招动画的照片数
	int smallSkillNum;    //大招动画的照片数
//方法
	ValueMap player1_initPos;
	void setViewpointCenter(Vec2 position);
	Vec2 tileCoordFromPosition(Vec2 pos);
	 int getNowPointDir(Node* player, Vec2 newpoint);
	 int getAttackDir(int tempDir);
	void setPlayerPosition(Vec2 position);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	bool checkHit(int standDir, int monsterDir);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    static GameController* createScene(); //创建对象
	virtual bool init(); //初始化控制层
	void mapElementsInit();
	int successPlayerID; //判断胜利的时候再用
	Vec2 lastCollidablePos;
	void onEnter();
	void clientPlayerAttack();
	void spriteRectCheck(float dt);
	//   重写onEnter 函数
	void onExit();   //重写onExit 函数
	
	void collidableCheck();
	void createHero();
	void updateView(float dt);
	//hero_role HeroRole);  //创建英雄
	bool isHeroDeath();           //判断英雄是否死亡
	void menuCloseCallback(cocos2d::Ref* pSender);
	GameController() {
		lastCollidablePos = Vec2(0, 0);
	}
	CREATE_FUNC(GameController);    

};