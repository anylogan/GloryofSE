#include"Core/Sprite/Tower.h"


void Tower::initTowerAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp,Hero* hero)
{
	attack_rect = new Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200);
	isAttacking = false;
	attackMinusNum = attackAbility;
	bloodNum = _bloodNum;
	deadRewardmoney = _rewardMoney;
	deadRewardExp = _rewardExp;
	enemyHero = hero;
	blood = Progress::create("empty_bar.png", "full_bar.png");
	blood->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 1.1));
	this->addChild(blood);
	this->retain();

}

void Tower::minusBlood(int num, Node * attacker)
{
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(((float)bloodNum)/10.0);
	}
	else {//离世判断
		blood->setPercentage(0);
		this->setVisible(false);	//离世了，不可见
		bloodNum = 0;
		//this->setPosition(initPos);
		if (attacker == enemyHero)
			enemyHero->addReward(deadRewardmoney, deadRewardExp);
		this->unscheduleAllSelectors();
	}
}

void Tower::soldierAttackMinusBlood(int num)
{
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(((float)bloodNum) / 10.0);
	}
	else {//离世判断
		blood->setPercentage(0);
		this->setVisible(false);	//离世了，不可见
		bloodNum = 0;
		this->unscheduleAllSelectors();
	}
}
