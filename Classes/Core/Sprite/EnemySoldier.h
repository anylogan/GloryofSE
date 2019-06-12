#pragma once
#include"cocos2d.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Tower.h"
#include"Core/Sprite/Progress.h"

USING_NS_CC;
//class Tower;

class EnemySoldier : public Sprite
{
public:
	Progress * blood;   //血量
	Sprite* image;
	int monsterType;
	int bloodNum;  //血量
	Vec2 initPos;
	Vec2 attackTowerPos;
	int deadRewardmoney;	//打死奖励金币数量
	int deadRewardExp;		//打死奖励经验的数量
	int attackMinusNum;		//每次打人的掉血数
	virtual bool init();   
	Rect* attack_rect;
	void initBloodBar();
	int fullBlood;
	void initMonsterAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp,Vec2 towerPos);
	void setNewAttackRect();
	int getAttackDir(int tempDir);
	int getNowPointDir(Node * player, Vec2 newpoint);
	bool checkHeroInRect();
	void attackHero(float dt);
	void attackTower(float dt);
	void minusBlood(int num,Hero* hero);
	void startWalkTowardsTower(int dir);
	void towerAttackMinusBlood(int num);
	void soldierRevive(float dt);
	//Hero* heroInRect;
	Hero* enemyHero;
	Tower* enemyTower;
	Tower* enemyDefendTower;
	bool isAttacking;
	bool isWalking;
	void scheduleAttack(int way);
	void unscheduleAttack();
};