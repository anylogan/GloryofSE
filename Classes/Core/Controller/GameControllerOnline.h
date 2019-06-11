//#pragma once
//
//#include"cocos2d.h"
//#include <vector>
//#include"Scene/SelectHeroScene.h"
////包含层类头文件
//#include"Scene/ButtonLayer.h"
////包含精灵类头文件
//#include"Core/Sprite/Hero.h"
//#include"Core/Sprite/EnemySoldier.h"
//#include"Core/Sprite/Tower.h"
//#include"Core/Sprite/fieldMonster.h"
//
//USING_NS_CC;
////全局变量
////extern int playMoney;
//class GameControllerOnline : public Layer   //游戏控制类
//{
//
//public:
//	//属性
//	//层属性
//	ButtonLayer * button;
//	//
//	//属性
//	TMXTiledMap * _tileMap;
//	TMXLayer * _collidable;
//	Hero * hero1, *hero2;
//	std::vector<EnemySoldier*> clientSoldierVector;    //存放EnemySoldier对象的容器
//	fieldMonster* monster1;
//	fieldMonster* monster2;
//	std::vector<Tower*>TowerVector;				//存放塔指针的容器
//						  //方法
//	ValueMap player1_initPos;
//	void setViewpointCenter(Vec2 position);
//	Vec2 tileCoordFromPosition(Vec2 pos);
//	int getNowPointDir(Node* player, Vec2 newpoint);
//	int getAttackDir(int tempDir);
//	void setPlayerPosition(Vec2 position);
//	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
//	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
//	bool checkHit(int standDir, int monsterDir);
//	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//	static GameControllerOnline* createScene(); //创建对象
//	virtual bool init(); //初始化控制层
//	void mapElementsInit();
//	int successPlayerID; //判断胜利的时候再用
//	Vec2 lastCollidablePos;
//	void onEnter();
//	void clientPlayerAttack();
//	void serverPlayerAttack();
//	void AI_Hero_Attack(float dt);
//	void spriteRectCheck(float dt);
//	//   重写onEnter 函数
//	void onExit();   //重写onExit 函数
//	void collidableCheck();
//	void createHero();
//	void updateView(float dt);
//	void AI_Hero_Run(float dt);
//	//hero_role HeroRole);  //创建英雄
//	bool isHeroDeath();           //判断英雄是否死亡
//	void menuCloseCallback(cocos2d::Ref* pSender);
//	CREATE_FUNC(GameControllerOnline);
//
//};