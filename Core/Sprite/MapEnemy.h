#pragma once
#include"cocos2d.h"
USING_NS_CC;

class MapElement :public Sprite
{
private:
	ProgressTimer * blood;   //血量
	int bloodNum;  //血量
	Vec2 initPos;
	int deadRewardmoney;	//打死奖励金币数量
	int deadRewardExp;		//打死奖励经验的数量
	int attackMinusNum;		//每次打人的掉血数
	Rect* attack_rect;
	char* attackURL;
	char* runURL;
public:
	//void attackHero(float dt);
	void minusBlood(int num, Node* attacker);
	bool isAttacking;
	void scheduleAttack();
	void unscheduleAttack();
	MapElement(int _deadRewardmoney, int _deadRewardExp, int _bloodNum, int _attackMinusNum, char* _attackURL, char* _runURl);
};