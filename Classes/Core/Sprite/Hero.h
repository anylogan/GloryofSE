#pragma once
//http://www.87g.com/zixun/16123.html    一个链接   王者荣耀英雄图

//在SelectHero界面中会有选择英雄的界面，   用户点击某个英雄，通过一个回调函数，返回一个hero_role参数，
//然后对这个参数进行判断   根据不同情况生成英雄
#include"cocos2d.h"
#include<vector>
#include"Core/Sprite/Progress.h"
#include"Scene/GlobalDefine.h"


using namespace std;
USING_NS_CC;
class Tower;
class EnemySoldier;

enum {
	up = 6,
	down = 4,
	lefts = 5,//
	rigth = 7,//
	rigth_up = 3,//
	rigth_down = 0,//
	left_down = 1,//
	left_up = 2//
};

class Hero:public Sprite
{
	
private:
	Progress* blood;   //血量
	int bloodNum;
	//vector<achievement_type> Achievement;  //所获得的成就
	int money;				//经济
	float speed;			//人物移动速度
	int commonAttack;	   //普通攻击值
	int exp;
	int fullBlood;

public:
	Vec2 initPos;			//瓦片地图初始化位置
	int killCount;       //杀敌计数
	Tower* enemyTower;
	int bonusSpeed;
	Sprite* image;
	int bonusAttack;
	int bonusDefend;
	int bonusBlood;
	Tower* enemyDefendTower;
	Sprite* skillSprite;
	//EnemySoldier* thisSoldierVector[3];
	std::vector<EnemySoldier*> *thisSoldierVector; //定义的是客户端用户的soldier
	void addReward(int moneyNum,int expNum) {
		money += moneyNum;
		exp += expNum;
		killCount += 1;
	}
	virtual bool init();   //  精灵初始化
	//bool attackTrick(const char *format,int num);   //  放招
	virtual bool checkIsAttack();  //检查是否受到攻击   
	void autoAttack(Node * thisSoldier);
	void autoRun(Vec2 pos);
	int getAttackDir(int tempDir);
	bool isHeroWalking;
	Rect *inRect;
	int currentPos;
	float getHeroSpeed();	     //返回速度
	int getCommonAttack() { return commonAttack; }       //返回普通攻击值
	int getBloodNum() { return bloodNum; }	//返回血量
	void minusBlood(int num);
	int getNowPointDir(Node * player, Vec2 newpoint);
	//掉血&死亡判断
	void attackEnemyAnimation(int dir);
	void skillAnimation();
	void updateHeroSpeed(float newspeed);
	void setMoney(int num) { money = num; }
	int getMoney() { return money; }
	int getExp() { return exp; }
	void initHeroAttr(int _money, float _speed, int _blood, int _commonAttack, int _exp, Tower* _tower);
	void equipbonusBlood(int num);
	//CREATE_FUNC(Hero);   //这句代码不能写！！不然无法create英雄
};

