#include"Core/Sprite/Hero.h"




bool Hero::init()  //  英雄的总的控制
{
	return true;
}


bool Hero::checkIsAttack()  //检查是否受到攻击
{

	return true;
}

void Hero::attackEnemyAnimation(int dir)   //播放动画
{
	this->stopAllActions();
	Animation *animation = Animation::create();
	for (int i = 0; i < 10; i++)
	{
		__String *frameName = __String::createWithFormat(hero_moonGoddess_attack, dir, i);
		log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	this->runAction(Repeat::create(action,1)); //播放一次
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
	blood->setPercentage(((float)bloodNum)/10.0);//满值 100%
	log("Hero blood percentage %f", ((float)bloodNum) / 10.0);
	//addChild(blood, 0, 0);
	addChild(blood);
}
void Hero::minusBlood(int num) {
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(((float)bloodNum) / 10.0);
	}
	else {//离世判断
		blood->setPercentage(0);
		this->setVisible(false);	//离世了，不可见
		bloodNum = 0;
		this->setPosition(initPos);

	}
}

