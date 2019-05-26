#include"Core/Controller/GameController.h"
#include"Scene/GameResultSuccess.h"
#include"Scene/GameResultFailure.h"

USING_NS_CC;
//初始化全局变量
extern hero_role HeroRole;
Hero* clientPlayer;
Hero* serverPlayer;
int GameResult[4]; //传递游戏结果
int playTime = 0;
GameController* GameController::createScene()
{
	return GameController::create();
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
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	createHero();
	hero2 = (Hero*)Hero::create(hero_ChangE); //Just for test,revise;

	/*创建地图*/
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	mapElementsInit();
	this->setViewpointCenter(clientPlayer->getPosition());
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->schedule(schedule_selector(GameController::updateView), 0.01f);
	//spriteRectCheck 也做结束检查、时间增加
	this->schedule(schedule_selector(GameController::spriteRectCheck), 1.0f);
	AI_Hero_Run(0);//执行一次；
	this->schedule(schedule_selector(GameController::AI_Hero_Run), 6.0f);
	this->schedule(schedule_selector(GameController::AI_Hero_Attack), 2.0f);

	return true;
}
inline void GameController::mapElementsInit() {
	/*创建对象元素-Players*/
	//创建player1
	hero1->thisSoldierVector = new std::vector<EnemySoldier*>;
	hero2->thisSoldierVector = new std::vector<EnemySoldier*>;
	hero1->retain();
	hero2->retain();
	TMXObjectGroup* group = _tileMap->getObjectGroup("Objects");
	auto spawnPoint = group->getObject("Player1");
	_collidable = _tileMap->getLayer("Collidable");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	hero1->initPos = Vec2(x, y);
	hero1->setPosition(Vec2(x, y));
	//这里加判断clientPlayer、serverPlayer
	clientPlayer = hero1;
	serverPlayer = hero2;
	//创建player2
	spawnPoint = group->getObject("Player2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	hero2->initPos = Vec2(x, y);
	hero2->setPosition(Vec2(x, y));
	/*建塔—Tower*/
	spawnPoint = group->getObject("Tower1");
	auto tower1 = static_cast<Tower*>(Tower::create("towerTile.png"));
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.push_back(tower1);
	tower1->setPosition(Vec2(x, y));

	spawnPoint = group->getObject("Tower2");
	auto tower2 = static_cast<Tower*>(Tower::create("towerTile.png"));
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.push_back(tower2);
	tower2->setPosition(Vec2(x, y));
	/*hero 初始化*/
	hero1->initHeroAttr(100, 1.0, 1000, 10, 0, tower2); //如果是tower1，就是0号 这里做测试用 记得改回来
	hero2->initHeroAttr(100, 1.0, 1000, 10, 0, tower1); //如果是tower1，就是0号 这里做测试用 记得改回来
														/*创建对象元素-Monsters*/
	spawnPoint = group->getObject("fieldMonster1");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	monster1 = static_cast<fieldMonster*>(fieldMonster::create("monster/monsterofField_1.png"));
	monster1->initPos = Vec2(x, y);	//初始位置供死亡以后用
	monster1->setPosition(Vec2(x, y));
	spawnPoint = group->getObject("fieldMonster2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	monster2 = static_cast<fieldMonster*>(fieldMonster::create("monster/monsterofField_2.png"));
	monster2->initPos = Vec2(x, y);
	monster2->setPosition(Vec2(x, y));
	monster1->initMonsterAttr(2, 100, 150, 20); //初始化属性，相当于构造函数 仍需更改其他！
	monster2->initMonsterAttr(2, 100, 150, 20);
	/*创建对象元素-Soldiers*/
	spawnPoint = group->getObject("soldier1");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier1 = static_cast<EnemySoldier*>(EnemySoldier::create(xixuebianfu_init));
	clientSoldier1->initPos = Vec2(x, y);
	clientSoldier1->setPosition(Vec2(x, y));
	clientSoldier1->enemyHero = hero1;
	clientSoldier1->monsterType = 1;
	clientSoldierVector.push_back(clientSoldier1);
	hero1->thisSoldierVector->push_back(clientSoldier1);
	spawnPoint = group->getObject("soldier2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier2 = static_cast<EnemySoldier*>(EnemySoldier::create(kongjumo_init));
	clientSoldier2->initPos = Vec2(x, y);
	clientSoldier2->setPosition(Vec2(x, y));
	clientSoldier2->enemyHero = hero1;
	clientSoldier2->monsterType = 2;
	clientSoldierVector.push_back(clientSoldier2);
	hero1->thisSoldierVector->push_back(clientSoldier2);

	spawnPoint = group->getObject("soldier3");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier3 = static_cast<EnemySoldier*>((EnemySoldier*)EnemySoldier::create(houjing_init));
	clientSoldier3->initPos = Vec2(x, y);
	clientSoldier3->setPosition(Vec2(x, y));
	clientSoldier3->monsterType = 3;
	clientSoldier3->enemyHero = hero1;
	clientSoldierVector.push_back(clientSoldier3);
	hero1->thisSoldierVector->push_back(clientSoldier3);

	spawnPoint = group->getObject("soldier4");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier4 = static_cast<EnemySoldier*>(EnemySoldier::create(xixuebianfu_init));
	clientSoldier4->initPos = Vec2(x, y);
	clientSoldier4->setPosition(Vec2(x, y));
	clientSoldier4->enemyHero = hero2;
	clientSoldier4->monsterType = 1;
	clientSoldierVector.push_back(clientSoldier4);
	hero2->thisSoldierVector->push_back(clientSoldier4);
	spawnPoint = group->getObject("soldier5");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier5 = static_cast<EnemySoldier*>(EnemySoldier::create(kongjumo_init));
	clientSoldier5->initPos = Vec2(x, y);
	clientSoldier5->setPosition(Vec2(x, y));
	clientSoldier5->enemyHero = hero2;
	clientSoldier5->monsterType = 2;
	clientSoldierVector.push_back(clientSoldier5);
	hero2->thisSoldierVector->push_back(clientSoldier5);

	spawnPoint = group->getObject("soldier6");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier6 = static_cast<EnemySoldier*>((EnemySoldier*)EnemySoldier::create(houjing_init));
	clientSoldier6->initPos = Vec2(x, y);
	clientSoldier6->setPosition(Vec2(x, y));
	clientSoldier6->enemyHero = hero2;
	clientSoldier6->monsterType = 3;
	clientSoldierVector.push_back(clientSoldier6);
	hero2->thisSoldierVector->push_back(clientSoldier6);

	/*addchild 设置初值*/
	addChild(monster1, 100);
	addChild(monster2, 200);
	addChild(hero1, 300);
	addChild(hero2, 400);
	int i = 0;
	for (auto it = TowerVector.begin(); it != TowerVector.end(), i<2; it++, i++) {
		if (i == 0)
			(*it)->initTowerAttr(10, 1000, 150, 20, hero2);	//应该分开！
		else  (*it)->initTowerAttr(10, 1000, 150, 20, hero1);	//应该分开！
																//(*it)->initBloodBar();
		(*it)->enemySoldierOfTower = new Vector<EnemySoldier*>;
		addChild(*it);
	}
	//因为tower没有初始化，所以hero放在这里初始化。


	i = 0;
	for (auto it = clientSoldierVector.begin(); it != clientSoldierVector.end(), i<6; it++, i++) {
		if (i <= 2) {
			(*it)->initMonsterAttr(20, 100, 150, 20, tower1->getPosition()); //先设置小怪攻击量20
																			 //(*it)->initBloodBar();
			addChild(*it);
			(*it)->enemyTower = tower1;		//后需修改！！
			tower1->enemySoldierOfTower->pushBack(*it);
		}
		else {
			(*it)->initMonsterAttr(20, 100, 150, 20, tower2->getPosition()); //先设置小怪攻击量20
																			 //(*it)->initBloodBar();
			addChild(*it);
			(*it)->enemyTower = tower2;		//后需修改！！
			tower2->enemySoldierOfTower->pushBack(*it);
		}
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
	clientPlayer->attackEnemyAnimation(getAttackDir(hero1->currentPos));//播放攻击动画
	auto monster1Hit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer,monster1->getPosition()));
	auto monster2Hit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer,monster1->getPosition()));
	auto serverPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, serverPlayer->getPosition()));
	if (serverPlayerHit && serverPlayer->getBloodNum() >= 0) //可以再加入hero2
		if (clientPlayer->inRect->containsPoint(serverPlayer->getPosition()))
			serverPlayer->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack);

	if (monster1Hit && monster1->blood>=0) //可以再加入hero2
		if(monster1->attack_rect->containsPoint(clientPlayer->getPosition()))
			monster1->minusBlood(clientPlayer->getCommonAttack()+clientPlayer->bonusAttack, clientPlayer);
		
	if (monster2Hit && monster1->blood >= 0)//可以再加入hero2
		if (monster2->attack_rect->containsPoint(clientPlayer->getPosition()))
			monster2->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);
	for (int i = 0; i < 3; i++) {
		auto testEnemy = clientSoldierVector[i];
		auto checkPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, testEnemy->getPosition()));
		if (checkPlayerHit && testEnemy->attack_rect->containsPoint(clientPlayer->getPosition()))
			testEnemy->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack,clientPlayer);
	}
	auto testTower = clientPlayer->enemyTower;
	auto checkPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, testTower->getPosition()));
	if (checkPlayerHit && testTower->attack_rect->containsPoint(clientPlayer->getPosition()))
			testTower->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);
	
}
void GameController::collidableCheck()
{
	//日后改成clientPlayer
		auto pos = clientPlayer->getPosition();
		Vec2 tileCoord = this->tileCoordFromPosition(pos);
		//获得瓦片的GID
		int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
		if (tileGid > 0 && lastCollidablePos!=pos) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
			clientPlayer->stopAllActions();
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
	case ChangE:
	{
		hero1 = (Hero*)Hero::create(hero_ChangE);
		break;
	}
	case SunWukong:
	{
		hero1 = (Hero*)Hero::create(hero_SunWukong);
		break;
	}
	case HuaMulan:
	{
		hero1 = (Hero*)Hero::create(hero_HuaMulan);
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
void GameController::AI_Hero_Run(float dt) {
	log("First soldier %d", serverPlayer->thisSoldierVector->at(0)->bloodNum);

	if ((serverPlayer->thisSoldierVector->at(0))->bloodNum >0) {
		serverPlayer->autoRun(serverPlayer->thisSoldierVector->at(0)->getPosition());
		log("First soldier %d", serverPlayer->thisSoldierVector->at(0)->bloodNum);
	}
	else if (serverPlayer->thisSoldierVector->at(1)->bloodNum>0) {
			serverPlayer->autoRun(serverPlayer->thisSoldierVector->at(1)->getPosition());
	}
	else if (serverPlayer->thisSoldierVector->at(2)->bloodNum>0) {
		serverPlayer->autoRun(serverPlayer->thisSoldierVector->at(2)->getPosition());
	}
	else {
		serverPlayer->autoRun(serverPlayer->enemyTower->getPosition());
	}
}

void GameController::AI_Hero_Attack(float dt) {
	/*
	if ((serverPlayer->thisSoldierVector->at(0))->bloodNum > 0) {
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(0));
	}
	else if (serverPlayer->thisSoldierVector->at(1)->bloodNum>0) {
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(1));
	}
	else if (serverPlayer->thisSoldierVector->at(2)->bloodNum >0) {
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
	}
	else if (hero1->getBloodNum() >0) {
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
	}
	else {
		serverPlayer->autoAttack(serverPlayer->enemyTower);
	}
	*/
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(0));
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(1));
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
		//serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
		serverPlayer->autoAttack(serverPlayer->enemyTower);
		serverPlayer->autoAttack(clientPlayer);

}


void GameController::spriteRectCheck(float dt) {
	playTime++;
	if (TowerVector.at(0)->bloodNum <= 0 || clientPlayer->getBloodNum()<=0) {
		this->unscheduleAllSelectors();
		GameResult[0] = playTime;
		GameResult[1] = clientPlayer->getExp();
		GameResult[2] = clientPlayer->killCount;
		GameResult[3] = clientPlayer->getMoney();
		auto sc = GameResultFailure::createScene();
		Director::getInstance()->pushScene(sc);
	}
	else {
		if (TowerVector.at(1)->bloodNum <= 0) {
			this->unscheduleAllSelectors();
			GameResult[0] = playTime;
			GameResult[1] = clientPlayer->getExp();
			GameResult[2] = clientPlayer->killCount;
			GameResult[3] = clientPlayer->getMoney();

			auto sc = GameResultSuccess::createScene();
			Director::getInstance()->pushScene(sc);
		}
	}

	clientPlayer->inRect= new Rect(clientPlayer->getPositionX() - 100, clientPlayer->getPositionY() - 100, 200, 200);
	//serverPlayer->inRect = new Rect(serverPlayer->getPositionX() - 100, clientPlayer->getPositionY() - 100, 200, 200);

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
	for (auto i=0; i<6; i++) {
		log("A new judge %d",i);
		clientSoldierVector[i]->setNewAttackRect();
		bool judge = clientSoldierVector[i]->checkHeroInRect();
		bool towerJudge = clientSoldierVector[i]->enemyTower->attack_rect->containsPoint(clientSoldierVector[i]->getPosition());
		/*
		if(judge==false)
			log ("Enemy is not in rect");
		else log("Enemy is  in rect");
		*/
		Tower* tempEnemyTower;
		if (i <= 2)
			tempEnemyTower = TowerVector.at(0);
		else tempEnemyTower = TowerVector.at(1);

		if (clientSoldierVector[i]->isAttacking == false && clientSoldierVector[i]->isWalking == false) {
			int tempDir = getNowPointDir(clientSoldierVector[i], tempEnemyTower->getPosition()); //改一下
			int attackDir = getAttackDir(tempDir);
			clientSoldierVector[i]->startWalkTowardsTower(attackDir);
			clientSoldierVector[i]->isWalking = true;
			log("enemy is walking");
			continue;
		}
		if (clientSoldierVector[i]->isAttacking == false && clientSoldierVector[i]->isWalking == true) {
			if (towerJudge &&clientSoldierVector[i]->enemyTower->bloodNum>0) {		//塔没有死才可以进入攻击状态
				clientSoldierVector[i]->isWalking = false;
				clientSoldierVector[i]->isAttacking = true;
				clientSoldierVector[i]->stopAllActions();
				clientSoldierVector[i]->scheduleAttack(1);
				log("enemy is attacking");
				continue;
			}
			if (judge && clientSoldierVector[i]->enemyHero->getBloodNum()>0) {		//英雄没有死才可以进入攻击状态
				clientSoldierVector[i]->isWalking = false;
				clientSoldierVector[i]->isAttacking = true;
				clientSoldierVector[i]->stopAllActions();
				clientSoldierVector[i]->scheduleAttack(0);//0打人
				log("enemy is attacking");
				continue;
			}
		}
		if (clientSoldierVector[i]->isAttacking == true && clientSoldierVector[i]->isWalking == false) {
			if (!judge) {
				if (!towerJudge) {
					clientSoldierVector[i]->isAttacking = false;
					clientSoldierVector[i]->isWalking = true;
					clientSoldierVector[i]->stopAllActions();
					clientSoldierVector[i]->unscheduleAttack();
					int tempDir = getNowPointDir(clientSoldierVector[i], tempEnemyTower->getPosition()); //改一下
					int attackDir = getAttackDir(tempDir);
					clientSoldierVector[i]->startWalkTowardsTower(attackDir);
					log("enemy stop attacking");
					continue;
				}
			}
		}
	}
	for (auto it1 = TowerVector.begin(); it1 != TowerVector.end(); it1++) {
		for (auto it2 = (*it1)->enemySoldierOfTower->begin(); it2 != (*it1)->enemySoldierOfTower->end(); it2++) {
			if ((*it1)->attack_rect->containsPoint((*it2)->getPosition()))
				(*it2)->towerAttackMinusBlood((*it1)->attackMinusNum);
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
		clientPlayer->stopAllActions();
		return;
	}
	//移动精灵
	clientPlayer->setPosition(position);
	//滚动地图
	this->setViewpointCenter(clientPlayer->getPosition());
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
	if (clientPlayer->isHeroWalking == true)
		return;
	clientPlayer->isHeroWalking = true;
	clientPlayer->stopAllActions();
	//log("onTouchEnded");
	//获得在OpenGL坐标
	Vec2 touchLocation = touch->getLocation();
	//转换为当前层的模型坐标系
	touchLocation = this->convertToNodeSpace(touchLocation);

	Vec2 playerPos = clientPlayer->getPosition();
	Vec2 diff = touchLocation - playerPos;
	int newDir = getNowPointDir(clientPlayer,touchLocation);
	clientPlayer->currentPos = newDir;
	Animation* animation = Animation::create();
	__String * frameName;
	for (int i = 0; i <= 7; i++)
	{

		switch (HeroRole) {
		case ChangE:
			frameName = __String::createWithFormat(hero_ChangE_pao, newDir, i); break;
		case HuaMulan:
			frameName = __String::createWithFormat(hero_HuaMulan_pao, newDir, i); break;
		case SunWukong:
			frameName = __String::createWithFormat(hero_SunWukong_pao, newDir, i);
		}
		log("frameName = %s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrame::
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setDelayPerUnit(0.15f);
	animation->setRestoreOriginalFrame(false);
	Animate* action = Animate::create(animation);
	clientPlayer->runAction(RepeatForever::create(action));
	//log(_tileMap->getTileSize().height);
	Vec2 tileCoord = this->tileCoordFromPosition(touchLocation);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//只有碰撞层时
	//log("new Gid %d", tileGid);
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//提醒碰撞
		clientPlayer->isHeroWalking = false;
		clientPlayer->stopAllActions();
		return;
	}
	float speed = clientPlayer->getHeroSpeed();
	float x1 = playerPos.x;
	float y1 = playerPos.y;
	float x2 = touchLocation.x;
	float y2 = touchLocation.y;
	float dif_x = x1 - x2;
	float dif_y = y1 - y2;
	float dis = sqrt(dif_x*dif_x + dif_y * dif_y);
	//log("dis is %f", dis);
	clientPlayer->runAction(MoveTo::create(dis*(speed-(float)(clientPlayer->bonusSpeed/100.0)) / 100.0, touchLocation));
	clientPlayer->isHeroWalking = false;
	//hero1->stopAllActions();
	//this->setViewpointCenter(hero1->getPosition()); //放到updateGame里实现顺滑滚动
}



