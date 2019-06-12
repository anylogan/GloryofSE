#pragma once
#include"cocos2d.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Progress.h"
#include <vector>
class EnemySoldier;		//声明类

USING_NS_CC;
class Tower :public Sprite
{
public:
	Progress * blood;   //血量
	Sprite* image;
	int bloodNum;  //血量
	int fullBlood;
	Vec2 initPos;
	Vec2 attackTowerPos;
	int deadRewardmoney;	//打死奖励金币数量
	int deadRewardExp;		//打死奖励经验的数量
	int attackMinusNum;		//每次打人的掉血数
	Rect* attack_rect;
	void initBloodBar();
	void initTowerAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp,Hero* hero);//用这个初始化怪物属性
	void attackHero(float dt);
	void minusBlood(int num, Node* attacker);
	void soldierAttackMinusBlood(int num);
	Hero* enemyHero;
	Vector<EnemySoldier*> *enemySoldierOfTower;
	bool isAttacking;
	void scheduleAttack();
	void unscheduleAttack();
};