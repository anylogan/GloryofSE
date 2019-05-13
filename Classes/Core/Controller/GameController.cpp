#include"Core/Controller/GameController.h"
#define hero_moonGoddess "hero/change/zhan/0649-3ea35add-00000.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"
#define hero_moonGoddess_pao " "
USING_NS_CC;
extern hero_role HeroRole;
GameController* GameController::createScene()
{
	return (GameController*)GameController::create();
}
void GameController::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

bool GameController::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	createHero();
	/*创建地图*/
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	mapElementsInit();
	this->setViewpointCenter(hero1->getPosition());
	//createEnemySoldier();  //创建EnemySoldier

				   //创建CannonFodder     简单起见  实现隔一段时间创建一队炮灰让他们沿着固定路径前进  
	//createCannonFodder();  //创建炮灰
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	//log("monster pos %f,%f", monster1->getPositionX(), monster1->getPositionY());
	this->schedule(schedule_selector(GameController::updateView), 0.01f);
	this->schedule(schedule_selector(GameController::spriteRectCheck), 1.0f);

	return true;
	
}
void GameController::mapElementsInit() {
	/*创建对象元素-Players*/

	TMXObjectGroup* group = _tileMap->getObjectGroup("Objects");
	auto spawnPoint = group->getObject("Player1");
	_collidable = _tileMap->getLayer("Collidable");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	hero1->initPos = Vec2(x, y);
	hero1->setPosition(Vec2(x, y));
	/*创建对象元素-Monsters*/
	spawnPoint = group->getObject("fieldMonster1");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	monster1 = (fieldMonster*)fieldMonster::create("monster/monsterofField_1.png");
	monster1->initPos = Vec2(x, y);	//初始位置供死亡以后用
	monster1->setPosition(Vec2(x, y));
	spawnPoint = group->getObject("fieldMonster2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	monster2 = (fieldMonster*)fieldMonster::create("monster/monsterofField_2.png");
	monster2->initPos = Vec2(x, y);
	monster2->setPosition(Vec2(x, y));
	monster1->initMonsterAttr(2, 100, 150, 20); //初始化属性，相当于构造函数 仍需更改其他！
	monster2->initMonsterAttr(2, 100, 150, 20);
	/*创建对象元素-Soldiers*/
	spawnPoint = group->getObject("soldier1");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier1 = (EnemySoldier*)EnemySoldier::create("monster/kongjumo/pao/1004-6579bfb5-00000.png");
	clientSoldier1->initPos = Vec2(x, y);
	clientSoldier1->setPosition(Vec2(x, y));
	clientSoldier1->enemyHero = hero1;
	clientSoldierVector.pushBack(clientSoldier1);
	spawnPoint = group->getObject("soldier2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier2 = (EnemySoldier*)EnemySoldier::create("monster/kongjumo/pao/1004-6579bfb5-00000.png");
	clientSoldier2->initPos = Vec2(x, y);
	clientSoldier2->setPosition(Vec2(x, y));
	clientSoldier2->enemyHero = hero1;
	clientSoldierVector.pushBack(clientSoldier2);
	spawnPoint = group->getObject("soldier3");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier3 = (EnemySoldier*)EnemySoldier::create("monster/kongjumo/pao/1004-6579bfb5-00000.png");
	clientSoldier3->initPos = Vec2(x, y);
	clientSoldier3->setPosition(Vec2(x, y));
	clientSoldier3->enemyHero = hero1;
	clientSoldierVector.pushBack(clientSoldier3);
	/*建塔—Tower*/
	spawnPoint = group->getObject("Tower1");
	auto tower1 = (Tower*)Tower::create("towerTile.png");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.pushBack(tower1);
	tower1->setPosition(Vec2(x, y));
	addChild(monster1, 100);
	addChild(monster2, 200);
	addChild(hero1, 300);
	for (auto it = TowerVector.begin(); it != TowerVector.end(); it++) {
		(*it)->initTowerAttr(10, 1000, 150, 20,hero1);	//应该分开！
		//(*it)->initBloodBar();
		(*it)->enemySoldierOfTower = new Vector<EnemySoldier*>;
		addChild(*it);
	}
	//因为tower没有初始化，所以hero放在这里初始化。
	hero1->initHeroAttr(100, 1.0, 1000, 10, 0, TowerVector.at(0)); //如果是tower1，就是0号 这里做测试用 记得改回来
	hero1->initBloodBar();

	for (auto it = clientSoldierVector.begin(); it != clientSoldierVector.end(); it++) {
		(*it)->initMonsterAttr(20, 100, 150, 20,tower1->getPosition()); //先设置小怪攻击量20
		//(*it)->initBloodBar();
		addChild(*it);
		(*it)->enemyTower = tower1;		//后需修改！！
		tower1->enemySoldierOfTower->pushBack(*it);
	}

}
void GameController::onEnter()  //  主要用来注册键盘和鼠标事件监听器
{

	Layer::onEnter();
	////注册事件监听器  监听键盘  hero可以释放技能
	auto releaseSkillListener = EventListenerKeyboard::create();
	releaseSkillListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			//换成clientPlayer
			clientPlayerAttack();
		}
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	eventDispatcher->addEventListenerWithSceneGraphPriority(releaseSkillListener, this);

}
void GameController::clientPlayerAttack() {
	//换成clientPlayer,加死亡判断；
	hero1->attackEnemyAnimation(getAttackDir(hero1->currentPos));//播放攻击动画
	auto monster1Hit = checkHit(hero1->currentPos, getNowPointDir(hero1,monster1->getPosition()));
	auto monster2Hit = checkHit(hero1->currentPos, getNowPointDir(hero1,monster1->getPosition()));

	if (monster1Hit && monster1->blood>=0) //可以再加入hero2
		if(monster1->attack_rect->containsPoint(hero1->getPosition()))
			monster1->minusBlood(hero1->getCommonAttack(),hero1);
		
	if (monster2Hit && monster1->blood >= 0)//可以再加入hero2
		if (monster2->attack_rect->containsPoint(hero1->getPosition()))
			monster2->minusBlood(hero1->getCommonAttack(), hero1);
	for (int i = 0; i < 3; i++) {
		auto testEnemy = clientSoldierVector.at(i);
		auto checkPlayerHit = checkHit(hero1->currentPos, getNowPointDir(hero1, testEnemy->getPosition()));
		if (checkPlayerHit && testEnemy->attack_rect->containsPoint(hero1->getPosition()))
			testEnemy->minusBlood(hero1->getCommonAttack());
	}
	auto testTower = hero1->enemyTower;
	auto checkPlayerHit = checkHit(hero1->currentPos, getNowPointDir(hero1, testTower->getPosition()));
	if (checkPlayerHit && testTower->attack_rect->containsPoint(hero1->getPosition()))
			testTower->minusBlood(hero1->getCommonAttack(),hero1);
	
}
void GameController::collidableCheck()
{
	//日后改成clientPlayer
		auto pos = hero1->getPosition();
		Vec2 tileCoord = this->tileCoordFromPosition(pos);
		//获得瓦片的GID
		int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
		if (tileGid > 0 && lastCollidablePos!=pos) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
			hero1->stopAllActions();
			//thisCollidableCheck = false;
			lastCollidablePos = pos;
		}
	}


/* WASD
Key with keycode 146 released
Key with keycode 124 released
Key with keycode 142 released
Key with keycode 127 released
*/
void GameController::createHero()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	switch (HeroRole)       //创建英雄
	{
	case moonGoddess:
	{
		hero1 = (Hero*)Hero::create(hero_moonGoddess);
		hero1->isHeroWalking = false;
		break;
	}
	case yase:
	{
		hero1 = (Hero*)Hero::create(hero_yase);
		break;
	}
	case houyi:
	{
		hero1 = (Hero*)Hero::create(hero_houyi);
		break;
	}
	default:break;
	}
}

void  GameController::updateView(float dt)  //刷新函数
{
	this->setViewpointCenter(hero1->getPosition());
	//CannonFodderMoving();  //让炮灰走几步   
	collidableCheck();
}

void GameController::spriteRectCheck(float dt) {
	if (monster1->checkHeroInRect(hero1, hero2) == true) {
		if (monster1->isAttacking == false && monster1->bloodNum>=0) {
			monster1->isAttacking = true;
			monster1->scheduleAttack();
		}
	}
	if (monster2->checkHeroInRect(hero1, hero2) == true && monster2->bloodNum >= 0) {
		if (monster2->isAttacking == false) {
			monster2->isAttacking = true;
			monster2->scheduleAttack();
		}
	}
	for (auto it = clientSoldierVector.begin(); it != clientSoldierVector.end(); it++) {
		log("A new judge");
		(*it)->setNewAttackRect();
		bool judge = (*it)->checkHeroInRect();
		bool towerJudge = (*it)->enemyTower->attack_rect->containsPoint((*it)->getPosition());
		/*
		if(judge==false)
			log ("Enemy is not in rect");
		else log("Enemy is  in rect");
		*/
		if ((*it)->isAttacking == false && (*it)->isWalking == false) {
			int tempDir = getNowPointDir(*it, TowerVector.at(0)->getPosition()); //改一下
			int attackDir = getAttackDir(tempDir);
			(*it)->startWalkTowardsTower(attackDir);
			(*it)->isWalking = true;
			log("enemy is walking");
			continue;
		}
		if ((*it)->isAttacking == false && (*it)->isWalking == true) {
			if (towerJudge && (*it)->enemyTower->bloodNum>0) {		//英雄没有死才可以进入攻击状态
				(*it)->isWalking = false;
				(*it)->isAttacking = true;
				(*it)->stopAllActions();
				(*it)->scheduleAttack(1);
				log("enemy is attacking");
				continue;
			}
			if (judge && (*it)->enemyHero->getBloodNum()>0) {		//英雄没有死才可以进入攻击状态
				(*it)->isWalking = false;
				(*it)->isAttacking = true;
				(*it)->stopAllActions();
				(*it)->scheduleAttack(0);//0打人
				log("enemy is attacking");
				continue;
			}
		}
		if ((*it)->isAttacking == true && (*it)->isWalking == false) {
			if (!judge) {
				if (!towerJudge) {
					(*it)->isAttacking = false;
					(*it)->isWalking = true;
					(*it)->stopAllActions();
					(*it)->unscheduleAttack();
					int tempDir = getNowPointDir(*it, TowerVector.at(0)->getPosition()); //改一下
					int attackDir = getAttackDir(tempDir);
					(*it)->startWalkTowardsTower(attackDir);
					log("enemy stop attacking");
					continue;
				}
			}
		}
	}
	for (auto it1 = TowerVector.begin(); it1 != TowerVector.end(); it1++) {
		for (auto it2 = (*it1)->enemySoldierOfTower->begin(); it2 != (*it1)->enemySoldierOfTower->end(); it2++) {
			if ((*it1)->attack_rect->containsPoint((*it2)->getPosition()))
				(*it2)->minusBlood((*it1)->attackMinusNum);
		}
		if ((*it1)->attack_rect->containsPoint((*it1)->enemyHero->getPosition()))
			(*it1)->enemyHero->minusBlood((*it1)->attackMinusNum);
	}
}

void GameController::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

bool GameController::isHeroDeath()          //判断英雄是否死亡
{
	if (hero1->getBloodNum() < 0)
		return true;
	else
		return false;
}

void GameController::setViewpointCenter(Vec2 position)
{
	//log("setViewpointCenter");

	//log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);
	//log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	//log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);

}

Vec2 GameController::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}


int GameController::getNowPointDir(Node* player,Vec2 newpoint)
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
int GameController::getAttackDir(int tempDir) { //转换8个方向
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
void GameController::setPlayerPosition(Vec2 position) {
	//hero1->stopAllActions();


	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
	//log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
		hero1->stopAllActions();
		return;
	}
	//移动精灵
	hero1->setPosition(position);
	//滚动地图
	this->setViewpointCenter(hero1->getPosition());
	//hero1->stopAllActions();

}


bool GameController::onTouchBegan(Touch* touch, Event* event)
{

	log("onTouchBegan");
	return true;
}

void GameController::onTouchMoved(Touch *touch, Event *event)
{

	log("onTouchMoved");
}
bool GameController::checkHit(int standDir, int monsterDir) { //检查人物方向和怪物方向是否相符
	if (monsterDir == rigth_down) {
		if (standDir == down || standDir == rigth || standDir == rigth_down)
			return true;
	}
	if (monsterDir == rigth_up) {
		if (standDir == up || standDir == rigth || standDir == rigth_up)
			return true;
	}
	if (monsterDir == rigth) {
		if (standDir == rigth_up || standDir == rigth || standDir == rigth_down)
			return true;
	}
	if (monsterDir == down) {
		if (standDir == left_down || standDir == down || standDir == rigth_down)
			return true;
	}
	if (monsterDir == lefts) {
		if (standDir == left_up || standDir == lefts || standDir == left_down)
			return true;
	}
	if (monsterDir == left_up) {
		if (standDir == left_up || standDir == lefts || standDir == up)
			return true;
	}
	if (monsterDir == left_down) {
		if (standDir == left_down || standDir == lefts || standDir == down)
			return true;
	}
	if (monsterDir == up) {
		if (standDir == up || standDir == left_up || standDir == rigth_up)
			return true;
	}
	return false;
}
void GameController::onTouchEnded(Touch *touch, Event *event)
{
	if (hero1->isHeroWalking == true)
		return;
	hero1->isHeroWalking = true;
	hero1->stopAllActions();
	//log("onTouchEnded");
	//获得在OpenGL坐标
	Vec2 touchLocation = touch->getLocation();
	//转换为当前层的模型坐标系
	touchLocation = this->convertToNodeSpace(touchLocation);

	Vec2 playerPos = hero1->getPosition();
	Vec2 diff = touchLocation - playerPos;
	int newDir = getNowPointDir(hero1,touchLocation);
	hero1->currentPos = newDir;
	Animation* animation = Animation::create();
	for (int i = 0; i <= 7; i++)
	{
		__String *frameName = __String::createWithFormat("hero/change/pao/2154-e1380841-0%d00%d.png", newDir, i);
		log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(false);
	Animate* action = Animate::create(animation);
	hero1->runAction(RepeatForever::create(action));
	//log(_tileMap->getTileSize().height);
	Vec2 tileCoord = this->tileCoordFromPosition(touchLocation);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
	//log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
		hero1->isHeroWalking = false;
		hero1->stopAllActions();
		return;
	}
	float speed = hero1->getHeroSpeed();
	float x1 = playerPos.x;
	float y1 = playerPos.y;
	float x2 = touchLocation.x;
	float y2 = touchLocation.y;
	float dif_x = x1 - x2;
	float dif_y = y1 - y2;
	float dis = sqrt(dif_x*dif_x + dif_y * dif_y);
	//log("dis is %f", dis);
	hero1->runAction(MoveTo::create(dis*speed / 100, touchLocation));
	hero1->isHeroWalking = false;
	//hero1->stopAllActions();
	//this->setViewpointCenter(hero1->getPosition()); //放到updateGame里实现顺滑滚动
}



