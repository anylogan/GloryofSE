#pragma once
#include"cocos2d.h"
USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	Sprite * blood;   //血量
	int bloodNum;  //血量
	//void attack();
	ValueMap spawnPoint;
	virtual bool init();   //  英雄的总的控制

};