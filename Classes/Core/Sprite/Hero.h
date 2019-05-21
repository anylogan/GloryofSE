#pragma once
//http://www.87g.com/zixun/16123.html    一个链接   王者荣耀英雄图

//在SelectHero界面中会有选择英雄的界面，   用户点击某个英雄，通过一个回调函数，返回一个hero_role参数，
//然后对这个参数进行判断   根据不同情况生成英雄
#include"cocos2d.h"
#include<vector>
#include"Core/Sprite/Progress.h"

#define hero_moonGoddess_attack "hero/change/attck/1047-6a75dcb1-0%d00%d.png"
using namespace std;
USING_NS_CC;
class Tower;
class EnemySoldier;

typedef enum {
	shooter = 0,    //射手
	Master = 1,     //法师
	auxiliary = 2,   //辅助
	Assassin=3,       //刺客
	tank=4			 //坦克
}hero_type;
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
	Progress* blood;   //血量
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
	int bounsSpeed=0;
	int bounsAttack=0;
	int bounsDefend=0;
	int bounsBlood = 0;
	Vector<EnemySoldier*> *thisSoldierVector; //定义的是客户端用户的soldier
	void addReward(int moneyNum,int expNum) {
		money += moneyNum;
		exp += expNum;
	}
	virtual bool init();   //  精灵初始化
	//bool attackTrick(const char *format,int num);   //  放招
	virtual bool checkIsAttack();  //检查是否受到攻击   
	void autoAttack(Node * thisSoldier);
	void autoRun(Vec2 pos);
	int getAttackDir(int tempDir);
	bool isHeroWalking;
	int currentPos;
	float getHeroSpeed();	     //返回速度
	int getCommonAttack() { return commonAttack; }       //返回普通攻击值
	int getBloodNum() { return bloodNum; }	//返回血量
	void minusBlood(int num);
	int getNowPointDir(Node * player, Vec2 newpoint);
	//掉血&死亡判断
	void attackEnemyAnimation(int dir);
	void updateHeroSpeed(float newspeed);
	void setMoney(int num) { money = num; }
	int getMoney() { return money; }
	void initHeroAttr(int _money, float _speed, int _blood, int _commonAttack, int _exp, Tower* _tower);
	//CREATE_FUNC(Hero);   //这句代码不能写！！不然无法create英雄
};

