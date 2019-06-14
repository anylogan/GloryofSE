#include"Core/Sprite/Hero.h"
#include"Core/Sprite/EnemySoldier.h"
#include<vector>
extern Hero* clientPlayer;

bool Hero::init()  //  英雄的总的控制
{
	return true;
}

bool Hero::checkIsAttack()  //检查是否受到攻击
{
	return true;
}
void Hero::autoAttack(Node* thisSoldier) {
	if (thisSoldier == this->enemyTower) {
		Tower* tempSoldier = static_cast<Tower*> (thisSoldier);
		bool checkInRect = tempSoldier->attack_rect->containsPoint(this->getPosition());
		if (checkInRect && tempSoldier->bloodNum>0) {
			int attackDir = getAttackDir(getNowPointDir(this, tempSoldier->getPosition()));
			attackEnemyAnimation(attackDir);
			tempSoldier->minusBlood(commonAttack, this);
		}
	} 
	else if(thisSoldier==clientPlayer){
		Hero* tempSoldier = static_cast<Hero*> (thisSoldier);
		bool checkInRect = tempSoldier->inRect->containsPoint(this->getPosition());
		if (checkInRect && tempSoldier->getBloodNum()>0) {
			int attackDir = getAttackDir(getNowPointDir(this, tempSoldier->getPosition()));
			attackEnemyAnimation(attackDir);
			tempSoldier->minusBlood(commonAttack);
		}
	}
	else {
		EnemySoldier* tempSoldier = static_cast<EnemySoldier*> (thisSoldier);
		bool checkInRect = tempSoldier->attack_rect->containsPoint(this->getPosition());
		if (checkInRect  && tempSoldier->bloodNum>0) {
			int attackDir = getAttackDir(getNowPointDir(this, tempSoldier->getPosition()));
			attackEnemyAnimation(attackDir);
			tempSoldier->minusBlood(commonAttack, this);
		}
	}
	
}

void Hero::autoRun(Vec2 pos) {
	isHeroWalking = true;
	this->stopAllActions();
	image->stopAllActions();
	Vec2 playerPos = this->getPosition();
	Vec2 diff = pos - playerPos;
	int newDir = getNowPointDir(this, pos);
	this->currentPos = newDir;
	Animation* animation = Animation::create();
	__String *frameName;
	for (int i = 0; i <= 7; i++)
	{
		switch (heroType) {
		case ChangE:
			frameName = __String::createWithFormat(hero_ChangE_pao, newDir, i); break;
		case HuaMulan:
			frameName = __String::createWithFormat(hero_HuaMulan_pao, newDir, i); break;
		case SunWukong:
			frameName = __String::createWithFormat(hero_SunWukong_pao, newDir, i);
		}		
		//log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(false);
	Animate* action = Animate::create(animation);
	image->runAction(RepeatForever::create(action));
	//log(_tileMap->getTileSize().height);
	float speed = this->getHeroSpeed();
	float x1 = playerPos.x;
	float y1 = playerPos.y;
	float x2 = pos.x;
	float y2 = pos.y;
	float dif_x = x1 - x2;
	float dif_y = y1 - y2;
	float dis = sqrt(dif_x*dif_x + dif_y * dif_y);
	//log("dis is %f", dis);
	this->runAction(MoveTo::create(dis*speed / 100, pos));
	this->isHeroWalking = false;

}
int Hero::getAttackDir(int tempDir) { //转换8个方向
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
int Hero::getNowPointDir(Node* player, Vec2 newpoint)
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
void Hero::attackEnemyAnimation(int dir)   //播放动画
{
	this->stopAllActions();
	image->stopAllActions();
	Animation *animation = Animation::create();
	__String *frameName;
	for (int i = 0; i < 10; i++)
	{

		switch (heroType) {
		case ChangE:
			frameName = __String::createWithFormat(hero_ChangE_attack, dir, i); break;
		case HuaMulan:
			frameName = __String::createWithFormat(hero_HuaMulan_attack, dir, i); break;
		case SunWukong:
			frameName = __String::createWithFormat(hero_SunWukong_attack, dir, i);
		}
		//log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	image->runAction(Repeat::create(action,1)); //播放一次
}
void Hero::skillAnimation()   //播放动画
{
	skillSprite->setVisible(true);
	skillSprite->stopAllActions();
	Animation *animation = Animation::create();
	__String *frameName;
	for (int i = 0; i < 10; i++)
	{

		switch (heroType) {
		case ChangE:
			frameName = __String::createWithFormat(hero_ChangE_skill,i); break;
		case HuaMulan:
			frameName = __String::createWithFormat(hero_HuaMulan_skill, i); break;
		case SunWukong:
			frameName = __String::createWithFormat(hero_SunWukong_skill,  i);
		}
		//log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);     //设置两个帧播放事件
	animation->setRestoreOriginalFrame(false);
	Animate *action = Animate::create(animation);
	skillSprite->runAction(Repeat::create(action, 1)); //播放一次
	this->scheduleOnce(schedule_selector(Hero::stopSkill), 4.0f); //在2.0f之后执行，并且只执行一次。

}
void Hero::stopSkill(float dt) {
	skillSprite->setVisible(false);
}
void Hero::updateHeroSpeed(float newspeed)
{
	speed = newspeed;
}
void Hero::initHeroAttr(int _money, float _speed, int _blood, int _commonAttack, int _exp, Tower * _tower)
{
	this->thisSoldierVector = new std::vector<EnemySoldier*>;
	inRect = new Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200);
	fullBlood = _blood;
	money = _money;
	speed = _speed;
	bloodNum = _blood;
	commonAttack = _commonAttack;
	isHeroWalking = false;
	exp = _exp;
	enemyTower = _tower;
	bonusSpeed = 0;
	bonusDefend = 0;
	bonusAttack = 0;
	bonusBlood = 0;
	blood = Progress::create("empty_bar.png", "full_bar.png");
	blood->setPosition(Vec2(image->getContentSize().width / 2, image->getContentSize().height / 1.0));
	hp = Progress::create("empty_bar_hp.png", "full_bar_hp.png");
	hp->setPosition(Vec2(image->getContentSize().width / 2, image->getContentSize().height / 1.1));
	isHeroWalking = false;
	killCount = 0;
	skillSprite = Sprite::create("towerTile.png");
	fullHP = 100;
	this->addChild(skillSprite);
	image->addChild(blood);
	image->addChild(hp);
	this->schedule(schedule_selector(Hero::updateHP), 0.5f); //在2.0f之后执行，并且只执行一次。

}

void Hero::equipbonusBlood(int num) {
	this->bloodNum += num;
	this->fullBlood += num;
}
float Hero::getHeroSpeed()
{
	return speed;
}

void Hero::minusBlood(int num) {
	int actualMinus = num - bonusAttack;		//bonus
	if (actualMinus > 0) {
		if (bloodNum - actualMinus >= 0) {
			bloodNum -= actualMinus;
			blood->setPercentage(((float)bloodNum) / ((float)(fullBlood)/100.0));
		}
		else {//离世判断
			this->unscheduleAllSelectors();
			blood->setPercentage(0);
			this->setVisible(false);	//离世了，不可见
			bloodNum = 0;
			this->setPosition(initPos);
			this->scheduleOnce(schedule_selector(Hero::HeroRevive), 15.0f); //在2.0f之后执行，并且只执行一次。
		}
	}
}
void Hero::updateHP(float dt) {
	fullHP += (fullHP + 2 <= 100) ? 2 : 0;
	hp->setPercentage(fullHP);
}

void Hero::HeroRevive(float dt) {//
	bloodNum = fullBlood;
	blood->setPercentage(100);
	this->setVisible(true);
	this->image->setVisible(true);
}
void Hero::minusHP(int num) {//
	int actualMinus = fullHP - num;		
	if (actualMinus >= 0) {
		fullHP = actualMinus;
		hp->setPercentage(fullHP);
	}
	else {
		fullHP = 0;
		hp->setPercentage(0);
	}

}
