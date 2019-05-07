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

//游戏场景类
//在游戏场景中加载游戏地图
//#define GameSceneNodeTagStatusBarFighterNode		301
//#define GameSceneNodeTagStatusBarLifeNode			302
//#define GameSceneNodeTagStatusBarScore				303
//
//#define GameSceneNodeBatchTagBackground				800
//#define GameSceneNodeTagFighter						900
//#define GameSceneNodeTagExplosionParticleSystem		901
//技能标记
#define GameSceneNodeBatchTagSkill				   902  
#define GameSceneNodeBatchTagEnemy					903

//发射技能的速度
#define GameSceneSkillVelocity						300

typedef enum {
	daji = 0,    //妲己
	houyi = 1,     //后羿
	yase = 2,   //亚瑟

}hero_role;
class GameScene :public Layer
{
private:
	
public:	
	hero_role HeroRole;
//属性
	TMXTiledMap * _tileMap;
	Hero * hero1, *hero2;
	Vector<Buff*> BuffVector;    //存放Buff对象的容器
	Vector<CannonFodder*>CannonFodderVector;  //存放炮灰对象的容器
//方法
	static GameScene* createScene();
	virtual bool init();
	void createHero();//hero_role HeroRole);  //创建英雄
	void createBuff();  //创建Buff
	void createCannonFodder();  //创建炮灰
	void onEnter();//   重写onEnter 函数
	void onExit();   //重写onExit 函数

	void updateGame(float dt);  //刷新函数


	virtual bool attackBigTrick();   //  放大招
	virtual bool attackMediumTrick();   //  放中招
	virtual bool attackSmallTrick();   //  放小招


	//以下为移动精灵函数
	/*bool onTouchBegan(Touch *touch, Event*unused_event);
	void onTouchEnded(Touch *touch, Event*unused_event);
	void onTouchMoved(Touch *touch, Event*unused_event);
*/
	CREATE_FUNC(GameScene);
};





