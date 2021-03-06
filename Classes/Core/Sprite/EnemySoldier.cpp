#include"Core/Sprite/EnemySoldier.h"

bool EnemySoldier::init()  //  英雄的总的控制
{
	Sprite::init();
	return true;
}

void EnemySoldier::initMonsterAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp,Vec2 towerPos)
{
	attack_rect = new Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200);
	isAttacking = false;
	isWalking = false;
	attackMinusNum = attackAbility;
	bloodNum = _bloodNum;
	fullBlood = _bloodNum;
	deadRewardmoney = _rewardMoney;
	deadRewardExp = _rewardExp;
	attackTowerPos = towerPos;
	blood = Progress::create("Enemy_empty_bar.png", "Enemy_full_bar.png");
	blood->setPosition(Vec2(image->getContentSize().width / 2, image->getContentSize().height / 1.1));
	image->addChild(blood);
	this->retain();
}
void EnemySoldier::setNewAttackRect() {
	attack_rect = new Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200);
}
int EnemySoldier::getAttackDir(int tempDir) { //转换8个方向
												//int tempDir = getNowPointDir(newPoint);
	if (tempDir == rigth_down || tempDir == down)
		return 0;
	if (tempDir == left_down || tempDir == lefts)
		return 1;
	if (tempDir == left_up || tempDir == up)
		return 2;
	if (tempDir == rigth_up || tempDir == rigth)
		return 3;
}
int EnemySoldier::getNowPointDir(Node* player, Vec2 newpoint)
{
	int thisdir = rigth_down; //默认为右下
							  //计算移动数据
	float center_x, center_y, player_x, player_y;
	int move_x, move_y;
	//更新NPC方向，状态
	Size origin = Director::getInstance()->getVisibleSize();
	Size size = Director::getInstance()->getWinSize();

	center_x = size.width / 2;
	center_y = size.height / 2;
	player_x = player->getPositionX();
	player_y = player->getPositionY();

	move_x = (int)(player_x - newpoint.x);
	move_y = (int)(player_y - newpoint.y - 20);

	if (move_x >= 10 && move_y <= -10)
	{
		//左上
		thisdir = left_up;
	}
	else if (move_x >= 10 && move_y >= 10)
	{
		//左下
		thisdir = left_down;
	}
	else if (move_x <= -10 && move_y <= -10)
	{
		//右上
		thisdir = rigth_up;
	}
	else if (move_x <= -10 && move_y >= 10)
	{
		//右下
		thisdir = rigth_down;
	}
	else if (move_x>-10 && move_x<10 && move_y>0)
	{
		//下
		thisdir = down;
	}
	else if (move_x>-10 && move_x<10 && move_y<0)
	{
		//上
		thisdir = up;
	}
	else if (move_x>0 && move_y>-10 && move_y<10)
	{
		//左
		thisdir = lefts;
	}
	else if (move_x<0 && move_y>-10 && move_y<10)
	{
		//右
		thisdir = rigth;
	}
	return thisdir;
}
bool EnemySoldier::checkHeroInRect()
{
	Vec2 pos1 = this->enemyHero->getPosition();
	log("Soldier %f,%f", getPositionX(), getPositionY());
	log("Enemy %f,%f", enemyHero->getPositionX(), enemyHero->getPositionY());
	if (attack_rect->containsPoint(pos1)){	//特别注意要重新设置rect
		log("enemyHero in rect");
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
	return false;
}
void EnemySoldier::scheduleAttack(int way)
{
	log("schedule");
	//this->stopAllActions();
	if(way==0)
		this->schedule(schedule_selector(EnemySoldier::attackHero), 1.0f); //在2.0f之后执行，并且只执行一次。
	else this->schedule(schedule_selector(EnemySoldier::attackTower), 1.0f);
}
void EnemySoldier::unscheduleAttack()
{
	log("unschedule");
	//this->unschedule(schedule_selector(EnemySoldier::attackHero)); 
	this->unscheduleAllSelectors();

}
void EnemySoldier::attackHero(float dt) {
	//isWalking = false;
	//isAttacking = true;
	this->image->stopAllActions();
	if (enemyHero != NULL && isAttacking == true) {
		enemyHero->minusBlood(attackMinusNum);
		Animation *animation = Animation::create();
		int dir = getAttackDir(getNowPointDir(this, enemyHero->getPosition()));
		__String *frameName;
		for (int i = 0; i < 8; i++)
		{
			switch (monsterType) {
			case 1:
				frameName = __String::createWithFormat(xixuebianfu_attck, dir, i);
				break;
			case 2:
				frameName = __String::createWithFormat(kongjumo_attck, dir, i);
				break;
			case 3:
				frameName = __String::createWithFormat(houjing_attck, dir, i);
				break;
			}			
			//log("frameName = %s", frameName->getCString());
			//SpriteFrame *spriteFrame = SpriteFrame::
			animation->addSpriteFrameWithFile(frameName->getCString());
		}
		animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
		animation->setRestoreOriginalFrame(true);
		Animate *action = Animate::create(animation);
		this->image->runAction(Repeat::create(action, 1)); //播放一次
		log("enemyHero minusBloos %d", attackMinusNum);
	}
	else {
		isAttacking = false;
		this->unscheduleAttack();	//在1.0f之后执行，并且只执行一次。
	}
}
void EnemySoldier::attackTower(float dt) {
	//isWalking = false;
	//isAttacking = true;

	if (enemyTower != NULL && isAttacking == true) {
		enemyTower->soldierAttackMinusBlood(attackMinusNum);
		Animation *animation = Animation::create();
		int dir = getAttackDir(getNowPointDir(this, enemyTower->getPosition()));
		__String *frameName;
		for (int i = 0; i < 8; i++)
		{
			switch (monsterType) {
				case 1:
					frameName = __String::createWithFormat(xixuebianfu_attck, dir, i);
					break;
				case 2:
					frameName = __String::createWithFormat(kongjumo_attck, dir, i);
					break;
				case 3:
					frameName = __String::createWithFormat(houjing_attck, dir, i);
					break;
			}
			//log("frameName = %s", frameName->getCString());
			//SpriteFrame *spriteFrame = SpriteFrame::
			animation->addSpriteFrameWithFile(frameName->getCString());
		}
		animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
		animation->setRestoreOriginalFrame(true);
		Animate *action = Animate::create(animation);
		this->image->runAction(Repeat::create(action, 1)); //播放一次
		log("enemyTower minusBloos %d", attackMinusNum);
	}
	else if (enemyDefendTower != NULL && isAttacking == true) {
		enemyDefendTower->soldierAttackMinusBlood(attackMinusNum);
		Animation *animation = Animation::create();
		int dir = getAttackDir(getNowPointDir(this, enemyDefendTower->getPosition()));
		__String *frameName;
		for (int i = 0; i < 8; i++)
		{
			switch (monsterType) {
			case 1:
				frameName = __String::createWithFormat(xixuebianfu_attck, dir, i);
				break;
			case 2:
				frameName = __String::createWithFormat(kongjumo_attck, dir, i);
				break;
			case 3:
				frameName = __String::createWithFormat(houjing_attck, dir, i);
				break;
			}
			//log("frameName = %s", frameName->getCString());
			//SpriteFrame *spriteFrame = SpriteFrame::
			animation->addSpriteFrameWithFile(frameName->getCString());
		}
		animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
		animation->setRestoreOriginalFrame(true);
		Animate *action = Animate::create(animation);
		this->image->runAction(Repeat::create(action, 1)); //播放一次
		log("enemyDefendTower minusBloos %d", attackMinusNum);
	}else{
		isAttacking = false;
		this->unscheduleAttack();	//在1.0f之后执行，并且只执行一次。
	}
}
void EnemySoldier::minusBlood(int num,Hero* hero) {
	if (bloodNum - num > 0) {
		bloodNum -= num;
		blood->setPercentage(((float)bloodNum) / ((float)(fullBlood) / 100.0));
	}
	else {//离世判断
		this->unscheduleAllSelectors();
		blood->setPercentage(0);
		this->setVisible(false);	//离世了，不可见
		bloodNum = 0;
		isWalking = false;
		isAttacking = false;
		this->setPosition(initPos);
		hero->addReward(deadRewardmoney, deadRewardExp);
		this->scheduleOnce(schedule_selector(EnemySoldier::soldierRevive), 15.0f); //在2.0f之后执行，并且只执行一次。

	}
}
void EnemySoldier::startWalkTowardsTower(int dir) {
	//this->stopAllActions();
	Animation *animation = Animation::create();
	__String *frameName;

	for (int i = 0; i < 8; i++)
	{
		switch (monsterType) {
		case 1:
			frameName = __String::createWithFormat(xixuebianfu_pao, dir, i);
			break;
		case 2:
			frameName = __String::createWithFormat(kongjumo_pao, dir, i);
			break;
		case 3:
			frameName = __String::createWithFormat(houjing_pao, dir, i);
			break;
		}
		//log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	image->runAction(RepeatForever::create(action));
	auto soldierPos = getPosition();
	float x1 = soldierPos.x;
	float y1 = soldierPos.y;
	float x2 = attackTowerPos.x;
	float y2 = attackTowerPos.y;
	float dif_x = x1 - x2;
	float dif_y = y1 - y2;
	float dis = sqrt(dif_x*dif_x + dif_y * dif_y);
	//log("dis is %f", dis);
	runAction(MoveTo::create(dis*4 / 50, attackTowerPos));

}

void EnemySoldier::towerAttackMinusBlood(int num)
{
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(((float)bloodNum) / ((float)(fullBlood) / 100.0));
	}
	else {//离世判断
		this->unscheduleAllSelectors();
		blood->setPercentage(0);
		this->setVisible(false);	//离世了，不可见
		bloodNum = 0;
		isWalking = false;
		isAttacking = false;
		this->setPosition(initPos);
		this->scheduleOnce(schedule_selector(EnemySoldier::soldierRevive), 10.0f); //在2.0f之后执行，并且只执行一次。
	}
}

void EnemySoldier::soldierRevive(float dt) {//
	bloodNum = fullBlood;
	blood->setPercentage(100);
	this->setVisible(true);
	this->image->setVisible(true);
}