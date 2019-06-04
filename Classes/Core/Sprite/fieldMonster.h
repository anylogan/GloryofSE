#pragma once
#include"cocos2d.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Progress.h"

USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	Progress * blood;   //血量
	int bloodNum;  //血量
	Sprite* image;
	//void attack();
	Vec2 initPos;
	int deadRewardmoney;	//打死奖励金币数量
	int deadRewardExp;		//打死奖励经验的数量
	int attackMinusNum;		//每次打人的
	virtual bool init();   //  野怪总的控制
	Rect* attack_rect;
	void initBloodBar();
	void initMonsterAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp);//用这个初始化怪物属性
	bool checkHeroInRect(Hero* hero1,Hero* hero2);
	void attackHero(float dt);
	void minusBlood(int num,Hero* hero);
	Hero* heroInRect;
	bool isAttacking;
	void scheduleAttack();
	void unscheduleAttack();
};