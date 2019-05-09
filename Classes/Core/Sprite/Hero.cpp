#include"Core/Sprite/Hero.h"




bool Hero::init()  //  英雄的总的控制
{
	return true;
}


bool Hero::checkIsAttack()  //检查是否受到攻击
{

	return true;
}

bool Hero::attackTrick(const char *format,int num)   //攻击方法  放大招
{
	Animation *animation = Animation::create();

	for (int i = 0; i < num; i++)
	{
		__String *frameName = __String::createWithFormat(format, i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName
			->getCString());
		animation->addSpriteFrame(spriteFrame);

	}
	animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	this->runAction(RepeatForever::create(action));
	return true;
}
void Hero::updateHeroSpeed(float newspeed)
{
	speed = newspeed;
}
float Hero::getHeroSpeed()
{
	return speed;
}