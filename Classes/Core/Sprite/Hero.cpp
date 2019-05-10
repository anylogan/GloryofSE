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
void Hero::initBloodBar() {	//初始化血条
	auto bgSprite = Sprite::create("empty_bar.png");
	bgSprite->setPosition(Vec2(getContentSize().width/2, getContentSize().height / 1.1));//坐标点，相对于背景的

	addChild(bgSprite);
	auto hpSprite = Sprite::create("full_bar.png");
	blood = ProgressTimer::create(hpSprite);
	blood->setType(ProgressTimer::Type::BAR);
	blood->setPosition(Vec2(getContentSize().width/2, getContentSize().height / 1.1));//坐标点，相对于背景的
	blood->setMidpoint(cocos2d::ccp(1, 0.5));
	blood->setBarChangeRate(cocos2d::ccp(1, 0));
	blood->setMidpoint(Point(0, 0.5));
	blood->setBarChangeRate(Point(1, 0));
	blood->setPercentage(100);//满值 100%
	addChild(blood, 0, 0);
}