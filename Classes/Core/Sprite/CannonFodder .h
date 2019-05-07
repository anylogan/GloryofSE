#pragma once
//简便起见  先不实现炮灰对战功能  只让炮灰沿着固定的路线走抗塔的伤害  并且给英雄送金币就行
#include"cocos2d.h"
USING_NS_CC;
class CannonFodder : public Sprite
{
	Sprite * blood;   //血量
	int bloodnum;  //血量



	void attack();



};