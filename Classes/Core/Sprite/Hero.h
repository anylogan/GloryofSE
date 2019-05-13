#pragma once
//http://www.87g.com/zixun/16123.html    一个链接   王者荣耀英雄图

//在SelectHero界面中会有选择英雄的界面，   用户点击某个英雄，通过一个回调函数，返回一个hero_role参数，
//然后对这个参数进行判断   根据不同情况生成英雄
#include"cocos2d.h"
#include<vector>
#define hero_moonGoddess_attack "hero/change/attck/1047-6a75dcb1-0%d00%d.png"
class Tower;
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
//	moonGoddess = 0,    //妲己
//	houyi = 1,     //后羿
//	yase = 2,   //亚瑟
//
//}hero_role;
class Hero:public Sprite
{
	
private:
	ProgressTimer* blood;   //血量
	int bloodNum;
	//vector<achievement_type> Achievement;  //所获得的成就
	hero_type type;                //英雄属于那种角色  
	int money;				//经济
	float speed;			//人物移动速度
	int commonAttack;	   //普通攻击值
	int exp;
public:
	Vec2 initPos;			//瓦片地图初始化位置
	Tower* enemyTower;
	void addReward(int moneyNum,int expNum) {
		money += moneyNum;
		exp += expNum;
	}
	virtual bool init();   //  精灵初始化
	//bool attackTrick(const char *format,int num);   //  放招
	virtual bool checkIsAttack();  //检查是否受到攻击   
	bool isHeroWalking;
	int currentPos;
	float getHeroSpeed();	     //返回速度
	int getCommonAttack() { return commonAttack; }       //返回普通攻击值
	int getBloodNum() { return bloodNum; }	//返回血量
	void initBloodBar();		 //初始化血条
	void minusBlood(int num);	//掉血&死亡判断
	void attackEnemyAnimation(int dir);
	void updateHeroSpeed(float newspeed);
	void initHeroAttr(int _money, float _speed,int _blood,int _commonAttack,int _exp,Tower* _tower) {
		money = _money;
		speed = _speed;
		bloodNum = _blood;
		commonAttack = _commonAttack;
		isHeroWalking = false;
		exp = _exp;
		enemyTower = _tower;
	}
	//CREATE_FUNC(Hero);   这句代码不能写！！不然无法create英雄
};

