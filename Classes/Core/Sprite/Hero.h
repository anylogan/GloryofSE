#pragma once
//http://www.87g.com/zixun/16123.html    一个链接   王者荣耀英雄图
#include"cocos2d.h"
#include<vector>
using namespace std;
USING_NS_CC;
typedef enum {
	shooter = 0,    //射手
	Master = 1,     //法师
	auxiliary = 2,   //辅助
	Assassin=3,       //刺客
	tank=4			 //坦克
}hero_type;
//typedef enum {
//	bestteammate = 0,    //  最佳队友
//	slaughter = 1,     //   血雨腥风
//	lifewinner = 2,   //    人生赢家
//       //·······
//}achievement_type;
//typedef enum {
//	daji = 0,    //妲己
//	houyi = 1,     //后羿
//	yase = 2,   //亚瑟
//
//}hero_role;
class Hero:public Sprite
{
private:
	Sprite * blood;   //血量
	//vector<achievement_type> Achievement;  //所获得的成就
	hero_type type;                //英雄属于那种角色  
	//hero_role role;
	int money;       //经济
public:
    //static Hero * createSprite();
	//Hero(hero_role role);  //重载构造函数
	
	virtual bool init();   //  英雄的总的控制
    //void createHero(hero_role role);  //创建英雄的函数
	virtual bool attack();   //攻击
	virtual bool checkIsAttack();  //检查是否受到攻击
	virtual void move();           //移动
	virtual void backHome();     //回城
	
	//CREATE_FUNC(Hero);
};