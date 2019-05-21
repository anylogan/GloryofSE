#include"Core/Sprite/EnemySoldier.h"

bool EnemySoldier::init()  //  Ӣ�۵��ܵĿ���
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
	bloodNum = 100;
	deadRewardmoney = _rewardMoney;
	deadRewardExp = _rewardExp;
	attackTowerPos = towerPos;
	blood = Progress::create("Enemy_empty_bar.png", "Enemy_full_bar.png");
	blood->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 1.1));
	this->addChild(blood);
	this->retain();
}
void EnemySoldier::setNewAttackRect() {
	attack_rect = new Rect(this->getPositionX() - 100, this->getPositionY() - 100, 200, 200);
}
int EnemySoldier::getAttackDir(int tempDir) { //ת��8������
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
	int thisdir = rigth_down; //Ĭ��Ϊ����
							  //�����ƶ�����
	float center_x, center_y, player_x, player_y;
	int move_x, move_y;
	//����NPC����״̬
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
		//����
		thisdir = left_up;
	}
	else if (move_x >= 10 && move_y >= 10)
	{
		//����
		thisdir = left_down;
	}
	else if (move_x <= -10 && move_y <= -10)
	{
		//����
		thisdir = rigth_up;
	}
	else if (move_x <= -10 && move_y >= 10)
	{
		//����
		thisdir = rigth_down;
	}
	else if (move_x>-10 && move_x<10 && move_y>0)
	{
		//��
		thisdir = down;
	}
	else if (move_x>-10 && move_x<10 && move_y<0)
	{
		//��
		thisdir = up;
	}
	else if (move_x>0 && move_y>-10 && move_y<10)
	{
		//��
		thisdir = lefts;
	}
	else if (move_x<0 && move_y>-10 && move_y<10)
	{
		//��
		thisdir = rigth;
	}
	return thisdir;
}
bool EnemySoldier::checkHeroInRect()
{
	auto pos1 = enemyHero->getPosition();
	log("Soldier %f,%f", getPositionX(), getPositionY());
	log("Enemy %f,%f", enemyHero->getPositionX(), enemyHero->getPositionY());
	if (attack_rect->containsPoint(pos1)){	//�ر�ע��Ҫ��������rect
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
		this->schedule(schedule_selector(EnemySoldier::attackHero), 1.0f); //��2.0f֮��ִ�У�����ִֻ��һ�Ρ�
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

	if (enemyHero != NULL && isAttacking == true) {
		enemyHero->minusBlood(attackMinusNum);
		Animation *animation = Animation::create();
		int dir = getAttackDir(getNowPointDir(this, enemyHero->getPosition()));
		for (int i = 0; i < 10; i++)
		{
			__String *frameName = __String::createWithFormat(enemy_attck, dir, i);
			log("frameName = %s", frameName->getCString());
			//SpriteFrame *spriteFrame = SpriteFrame::
			animation->addSpriteFrameWithFile(frameName->getCString());
		}
		animation->setDelayPerUnit(0.15f);     //��������֡�����¼�
		animation->setRestoreOriginalFrame(true);
		Animate *action = Animate::create(animation);
		this->runAction(Repeat::create(action, 1)); //����һ��
		log("enemyHero minusBloos %d", attackMinusNum);
	}
	else {
		isAttacking = false;
		this->unscheduleAttack();	//��1.0f֮��ִ�У�����ִֻ��һ�Ρ�
	}
}
void EnemySoldier::attackTower(float dt) {
	//isWalking = false;
	//isAttacking = true;

	if (enemyTower != NULL && isAttacking == true) {
		enemyTower->soldierAttackMinusBlood(attackMinusNum);
		Animation *animation = Animation::create();
		int dir = getAttackDir(getNowPointDir(this, enemyTower->getPosition()));
		for (int i = 0; i < 10; i++)
		{
			__String *frameName = __String::createWithFormat(enemy_attck, dir, i);
			log("frameName = %s", frameName->getCString());
			//SpriteFrame *spriteFrame = SpriteFrame::
			animation->addSpriteFrameWithFile(frameName->getCString());
		}
		animation->setDelayPerUnit(0.15f);     //��������֡�����¼�
		animation->setRestoreOriginalFrame(true);
		Animate *action = Animate::create(animation);
		this->runAction(Repeat::create(action, 1)); //����һ��
		log("enemyTower minusBloos %d", attackMinusNum);
	}
	else {
		isAttacking = false;
		this->unscheduleAttack();	//��1.0f֮��ִ�У�����ִֻ��һ�Ρ�
	}
}
void EnemySoldier::minusBlood(int num,Hero* hero) {
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
void EnemySoldier::startWalkTowardsTower(int dir) {
	//this->stopAllActions();
	Animation *animation = Animation::create();
	for (int i = 0; i < 9; i++)
	{
		__String *frameName = __String::createWithFormat(enemy_pao, dir, i);
		log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);     //��������֡�����¼�
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	runAction(RepeatForever::create(action));
	auto soldierPos = getPosition();
	float x1 = soldierPos.x;
	float y1 = soldierPos.y;
	float x2 = attackTowerPos.x;
	float y2 = attackTowerPos.y;
	float dif_x = x1 - x2;
	float dif_y = y1 - y2;
	float dis = sqrt(dif_x*dif_x + dif_y * dif_y);
	//log("dis is %f", dis);
	runAction(MoveTo::create(dis*4 / 100, attackTowerPos));

}

void EnemySoldier::towerAttackMinusBlood(int num)
{
	if (bloodNum - num >= 0) {
		bloodNum -= num;
		blood->setPercentage(bloodNum);
	}
	else {//�����ж�
		blood->setPercentage(0);
		this->setVisible(false);	//�����ˣ����ɼ�
		bloodNum = 0;
		//this->setPosition(initPos);
		this->unscheduleAllSelectors();
	}
}
