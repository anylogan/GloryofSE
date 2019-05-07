#pragma once
#include "cocos2d.h"
#include"Core/Sprite/Hero.h"

class Skill : public cocos2d::Sprite
{
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);

public:

	void releaseSkillFromHero(Hero* hero);    //¥””¢–€ Õ∑≈’– ˝

	virtual void update(float dt);
	static Skill* createWithSpriteFrameName(const char* spriteFrameName);
};
