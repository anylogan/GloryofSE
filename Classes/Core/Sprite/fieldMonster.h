#pragma once
#include"cocos2d.h"
USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	ProgressTimer * blood;   //血量
	int bloodNum;  //血量
	//void attack();
	Vec2 initPos;
	virtual bool init();   //  野怪总的控制

	void initBloodBar();

};