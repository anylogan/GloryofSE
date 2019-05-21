#include"Core/Sprite/fieldMonster.h"

bool fieldMonster::init()  //  Ӣ�۵��ܵĿ���
{
	Sprite::init();
	return true;
}


void fieldMonster::initMonsterAttr(int attackAbility,int _bloodNum,int _rewardMoney,int _rewardExp)
{
	attack_rect = new Rect(this->getPositionX()- 100, this->getPositionY() - 100, 200, 200);
	isAttacking = false;
	attackMinusNum = attackAbility;
	bloodNum = 100;
	deadRewardmoney = _rewardMoney;
	deadRewardExp = _rewardExp;
	blood = Progress::create("empty_bar.png", "full_bar.png");
	blood->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 1.1));
	this->addChild(blood);
	this->retain();

}

bool fieldMonster::checkHeroInRect(Hero * hero1, Hero * hero2)
{
	auto pos1 = hero1->getPosition();
	if (attack_rect->containsPoint(pos1)) {
		heroInRect = hero1;
		log("hero1 in rect");
		return true;
	}
	/*
	if (hero2 != NULL) {
		auto pos2 = hero2->getPosition();
		if (attack_rect->containsPoint(pos2)) {
			heroInRect = hero2;
			log("hero2 in rect");
			return true;
		}
	}
	*/
	heroInRect = NULL;
	return false;
}
void fieldMonster::scheduleAttack()
{
	log("schedule");

	this->schedule(schedule_selector(fieldMonster::attackHero), 1.0f); //��1.0f֮��ִ�У�����ִֻ��һ�Ρ�
}
void fieldMonster::unscheduleAttack()
{
	log("unschedule");
	this->unschedule(schedule_selector(fieldMonster::attackHero)); //��1.0f֮��ִ�У�����ִֻ��һ�Ρ�

}
void fieldMonster::attackHero(float dt) {
	log("heroInrect minusBloos %d", attackMinusNum);

	if (heroInRect != NULL && isAttacking == true) {
		heroInRect->minusBlood(attackMinusNum);
		log("heroInrect minusBloos %d", attackMinusNum);
	}
	else {
		isAttacking = false;
		this->unscheduleAttack(); //��1.0f֮��ִ�У�����ִֻ��һ�Ρ�
	}
}
void fieldMonster::minusBlood(int num,Hero* hero) {
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(bloodNum);
	}
	else {//�����ж�
		blood->setPercentage(0);
		this->setVisible(false);	//�����ˣ����ɼ�
		bloodNum = 0;
		//this->setPosition(initPos);
		hero->addReward(deadRewardmoney, deadRewardExp);
		this->unscheduleAllSelectors();
	}
}