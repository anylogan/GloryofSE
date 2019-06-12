#pragma once
//简便起见  先不实现炮灰对战功能  只让炮灰沿着固定的路线走抗塔的伤害  并且给英雄送金币就行
#include"cocos2d.h"
#include"Core/Sprite/Progress.h"
#include"Core/Sprite/Hero.h"

USING_NS_CC;
class BaseEnemy : public Sprite
{
private:
	Progress * bloodBar;
	int bloodNum;  //血量
	Vec2 initPos;
	Vec2 attackTowerPos;
	int deadRewardmoney;	//打死奖励金币数量
	int deadRewardExp;		//打死奖励经验的数量
	int attackMinusNum;		//每次打人的掉血数

};