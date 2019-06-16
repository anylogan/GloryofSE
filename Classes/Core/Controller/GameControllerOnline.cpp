#include"Core/Controller/GameControllerOnline.h"
#include"Scene/GameResultSuccess.h"
#include"Scene/GameResultFailure.h"

USING_NS_CC;
//��ʼ��ȫ�ֱ���
extern hero_role HeroRole;
extern hero_role EnemyHero;
extern int PlayMode;
extern Hero* clientPlayer;
extern Hero* serverPlayer;
extern int GameResult[4]; //������Ϸ���
extern int playTime;
GameControllerOnline* GameControllerOnline::createScene()
{
	return GameControllerOnline::create();
}
void GameControllerOnline::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

bool GameControllerOnline::init()
{
	if (!Layer::init())
	{
		return false;
	}
	playTime = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	createHero();
	/*������ͼ*/
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	NotificationCenter::getInstance()->removeAllObservers(this);
	mapElementsInit();
	this->setViewpointCenter(clientPlayer->getPosition());
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->schedule(schedule_selector(GameControllerOnline::updateView), 0.01f);
	//spriteRectCheck Ҳ��������顢ʱ������
	this->schedule(schedule_selector(GameControllerOnline::spriteRectCheck), 1.0f);
	//AI_Hero_Run(0);//ִ��һ�Σ�
	//this->schedule(schedule_selector(GameControllerOnline::AI_Hero_Run), 3.0f);
	//this->schedule(schedule_selector(GameControllerOnline::AI_Hero_Attack), 0.2f);
	this->schedule(schedule_selector(GameControllerOnline::updateEnemy), 0.01f);
	
	return true;
}
inline void GameControllerOnline::mapElementsInit() {
	/*��������Ԫ��-Players*/
	//����player1
	//hero1->retain();
	//hero2->retain();
	TMXObjectGroup* group = _tileMap->getObjectGroup("Objects");
	auto spawnPoint = group->getObject("Player1");
	_collidable = _tileMap->getLayer("Collidable");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	hero1->initPos = Vec2(x, y);
	hero1->setPosition(Vec2(x, y));
	//����player2
	spawnPoint = group->getObject("Player2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	hero2->initPos = Vec2(x, y);
	hero2->setPosition(Vec2(x, y));
	/*������Tower*/
	spawnPoint = group->getObject("Tower1");
	auto tower1 = new Tower();
	tower1->image = Sprite::create("towerTile.png");
	tower1->addChild(tower1->image);
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.push_back(tower1);
	tower1->setPosition(Vec2(x, y));

	spawnPoint = group->getObject("Tower2");
	auto tower2 = new Tower();
	tower2->image = Sprite::create("towerTile.png");
	tower2->addChild(tower2->image);
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.push_back(tower2);
	tower2->setPosition(Vec2(x, y));
	/*hero ��ʼ��*/
	hero1->friendTower = tower1;
	hero2->friendTower = tower2;
	switch (HeroRole)       //����Ӣ��
	{
	case ChangE:
	{
		if(clientPlayer==hero1)
			hero1->initHeroAttr(100, 1.0, 1000, 10, 0, tower2); //�����tower1������0�� ������������ �ǵøĻ���
		else hero2->initHeroAttr(100, 1.0, 1200, 10, 0, tower1); //�����tower1������0�� ������������ �ǵøĻ���		
		break;
	}
	case SunWukong:
	{
		if(clientPlayer==hero1)
			hero1->initHeroAttr(100, 0.9, 1200, 20, 0, tower2);//�����tower1������0�� ������������ �ǵøĻ���
		else hero2->initHeroAttr(100, 0.9, 1400, 20, 0, tower1);//�����tower1������0�� ������������ �ǵøĻ���	
		break;
	}
	case HuaMulan:
	{
		if(clientPlayer==hero1)
			hero1->initHeroAttr(100, 0.8, 1500, 10, 0, tower2); //�����tower1������0�� ������������ �ǵøĻ���
		else hero2->initHeroAttr(100, 0.8, 1700, 10, 0, tower1);//�����tower1������0�� ������������ �ǵøĻ���	
		break;
	}
	default:break;
	}
	
	switch (EnemyHero)       //����Ӣ��
	{
	case ChangE:
	{
		if(serverPlayer==hero1)
			hero1->initHeroAttr(100, 1.0, 1000, 10, 0, tower2); //�����tower1������0�� ������������ �ǵøĻ���
		else hero2->initHeroAttr(100, 1.0, 1200, 10, 0, tower1); //�����tower1������0�� ������������ �ǵøĻ���		
		break;
	}
	case SunWukong:
	{
		if(serverPlayer==hero1)
			hero1->initHeroAttr(100, 0.9, 1200, 20, 0, tower2);//�����tower1������0�� ������������ �ǵøĻ���
		else hero2->initHeroAttr(100, 0.9, 1400, 20, 0, tower1);//�����tower1������0�� ������������ �ǵøĻ���	
		break;
	}
	case HuaMulan:
	{
		if(serverPlayer==hero1)
			hero1->initHeroAttr(100, 0.8, 1500, 10, 0, tower2); //�����tower1������0�� ������������ �ǵøĻ���
		else hero2->initHeroAttr(100, 0.8, 1700, 10, 0, tower1);//�����tower1������0�� ������������ �ǵøĻ���	
		break;
	}
	default:break;
	}
	/*��������Ԫ��-DefendTowers*/
	spawnPoint = group->getObject("DefendTower1");
	auto DefendTower1 = new Tower();
	DefendTower1->image = Sprite::create("towerTile.png");	
	DefendTower1->addChild(DefendTower1->image);
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.push_back(DefendTower1);
	DefendTower1->setPosition(Vec2(x, y));
	hero2->enemyDefendTower = DefendTower1;
	spawnPoint = group->getObject("DefendTower2");
	auto DefendTower2 = new Tower();
	DefendTower2->image = Sprite::create("towerTile.png");	
	DefendTower2->addChild(DefendTower2->image);
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	//Tower1->initPos = Vec2(x, y);
	TowerVector.push_back(DefendTower2);
	DefendTower2->setPosition(Vec2(x, y));
	hero1->enemyDefendTower = DefendTower2;
	/*��������Ԫ��-Monsters*/
	spawnPoint = group->getObject("fieldMonster1");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	monster1 = new fieldMonster();
	monster1->image = Sprite::create("monster/monsterofField_1.png");
	monster1->addChild(monster1->image);
	monster1->initPos = Vec2(x, y);	//��ʼλ�ù������Ժ���
	monster1->setPosition(Vec2(x, y));
	spawnPoint = group->getObject("fieldMonster2");

	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	monster2 = new fieldMonster();
	monster2->image = Sprite::create("monster/monsterofField_2.png");
	monster2->addChild(monster2->image);
	monster2->initPos = Vec2(x, y);
	monster2->setPosition(Vec2(x, y));
	monster1->initMonsterAttr(2, 100, 150, 20); //��ʼ�����ԣ��൱�ڹ��캯�� �������������
	monster2->initMonsterAttr(2, 100, 150, 20);
	/*��������Ԫ��-Soldiers*/
	//hero1->thisSoldierVector = new std::vector<EnemySoldier*>;

	spawnPoint = group->getObject("soldier1");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier1 = new EnemySoldier();
	clientSoldier1->image = Sprite::create(xixuebianfu_init);
	clientSoldier1->addChild(clientSoldier1->image);
	clientSoldier1->initPos = Vec2(x, y);
	clientSoldier1->setPosition(Vec2(x, y));
	clientSoldier1->enemyHero = hero1;
	clientSoldier1->monsterType = 1;
	clientSoldierVector.push_back(clientSoldier1);
	hero1->thisSoldierVector->push_back(clientSoldier1);
	spawnPoint = group->getObject("soldier2");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier2 = new EnemySoldier();
	clientSoldier2->image = Sprite::create(kongjumo_init);
	clientSoldier2->addChild(clientSoldier2->image);
	clientSoldier2->initPos = Vec2(x, y);
	clientSoldier2->setPosition(Vec2(x, y));
	clientSoldier2->enemyHero = hero1;
	clientSoldier2->monsterType = 2;
	clientSoldierVector.push_back(clientSoldier2);
	hero1->thisSoldierVector->push_back(clientSoldier2);

	spawnPoint = group->getObject("soldier3");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier3 = new EnemySoldier();
	clientSoldier3->image = Sprite::create(houjing_init);	
	clientSoldier3->addChild(clientSoldier3->image);
	clientSoldier3->initPos = Vec2(x, y);
	clientSoldier3->setPosition(Vec2(x, y));
	clientSoldier3->monsterType = 3;
	clientSoldier3->enemyHero = hero1;
	clientSoldierVector.push_back(clientSoldier3);
	hero1->thisSoldierVector->push_back(clientSoldier3);
	//hero2->thisSoldierVector = new std::vector<EnemySoldier*>;
	spawnPoint = group->getObject("soldier4");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier4 = new EnemySoldier();
	clientSoldier4->image = Sprite::create(xixuebianfu_init);
	clientSoldier4->addChild(clientSoldier4->image);
	clientSoldier4->initPos = Vec2(x, y);
	clientSoldier4->setPosition(Vec2(x, y));
	clientSoldier4->enemyHero = hero2;
	clientSoldier4->monsterType = 1;
	clientSoldierVector.push_back(clientSoldier4);
	hero2->thisSoldierVector->push_back(clientSoldier4);
	spawnPoint = group->getObject("soldier5");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier5 = new EnemySoldier();
	clientSoldier5->image = Sprite::create(kongjumo_init);
	clientSoldier5->addChild(clientSoldier5->image);
	clientSoldier5->initPos = Vec2(x, y);
	clientSoldier5->setPosition(Vec2(x, y));
	clientSoldier5->enemyHero = hero2;
	clientSoldier5->monsterType = 2;
	clientSoldierVector.push_back(clientSoldier5);
	hero2->thisSoldierVector->push_back(clientSoldier5);

	spawnPoint = group->getObject("soldier6");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	auto clientSoldier6 = new EnemySoldier();
	clientSoldier6->image = Sprite::create(houjing_init);
	clientSoldier6->addChild(clientSoldier6->image);
	clientSoldier6->initPos = Vec2(x, y);
	clientSoldier6->setPosition(Vec2(x, y));
	clientSoldier6->enemyHero = hero2;
	clientSoldier6->monsterType = 3;
	clientSoldierVector.push_back(clientSoldier6);
	hero2->thisSoldierVector->push_back(clientSoldier6);

	/*addchild ���ó�ֵ*/
	addChild(monster1, 100);
	addChild(monster2, 200);
	addChild(hero1, 300);
	addChild(hero2, 400);

	int i = 0;
	for (auto it = TowerVector.begin(); it != TowerVector.end(), i<4; it++, i++) {
		switch (i) {
		case 0:
			(*it)->initTowerAttr(20, 1000, 500, 400, hero2);	
			break;
		case 1:
			(*it)->initTowerAttr(20, 1000, 500, 400, hero1);	
			break;
		case 2:
			(*it)->initTowerAttr(10, 300, 300, 200, hero2);	
			(*it)->attack_rect = new Rect((*it)->getPositionX() - 100, (*it)->getPositionY() - 100, 200, 200);
			break;
		case 3:
			(*it)->initTowerAttr(10, 300, 300, 200, hero1);	
			(*it)->attack_rect = new Rect((*it)->getPositionX() - 100, (*it)->getPositionY() - 100, 200, 200);
			break;
		}
		(*it)->enemySoldierOfTower = new Vector<EnemySoldier*>;
		addChild(*it);
	}
	//��Ϊtowerû�г�ʼ��������hero���������ʼ����

	i = 0;
	for (auto it = clientSoldierVector.begin(); it != clientSoldierVector.end(), i<6; it++, i++) {
		if (i <= 2) {
			switch ((*it)->monsterType) {
			case 1:
				(*it)->initMonsterAttr(20, 100, 150, 20, tower1->getPosition()); //������С�ֹ�����20
				break;
			case 2:
				(*it)->initMonsterAttr(30, 300, 300, 30, tower1->getPosition()); //������С�ֹ�����20
				break;
			case 3:
				(*it)->initMonsterAttr(40, 400, 400, 40, tower1->getPosition()); //������С�ֹ�����20
				break;
			}
			addChild(*it);
			(*it)->enemyTower = tower1;		
			(*it)->enemyDefendTower = DefendTower1;
			//(*it)->retain();
			tower1->enemySoldierOfTower->pushBack(*it);
			DefendTower1->enemySoldierOfTower->pushBack(*it);
		}
		else {
			switch ((*it)->monsterType) {
			case 1:
				(*it)->initMonsterAttr(20, 100, 150, 20, tower2->getPosition()); //������С�ֹ�����20
				break;
			case 2:
				(*it)->initMonsterAttr(30, 300, 300, 30, tower2->getPosition()); //������С�ֹ�����20
				break;
			case 3:
				(*it)->initMonsterAttr(40, 400, 400, 40, tower2->getPosition()); //������С�ֹ�����20
				break;
			}
			addChild(*it);
			(*it)->enemyTower = tower2;		
			(*it)->enemyDefendTower = DefendTower2;
			tower2->enemySoldierOfTower->pushBack(*it);
			DefendTower2->enemySoldierOfTower->pushBack(*it);
		}
	}
	spawnPoint = group->getObject("ReviveArea1");
	auto reviveArea1 = Sprite::create("towerTile.png");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	reviveArea1->setPosition(Vec2(x, y));
	reviveArea1->setTag(1);
	addChild(reviveArea1);
	spawnPoint = group->getObject("ReviveArea2");
	auto reviveArea2 = Sprite::create("towerTile.png");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();
	reviveArea2->setPosition(Vec2(x, y));
	reviveArea2->setTag(2);
	addChild(reviveArea2);
	
}
void GameControllerOnline::onEnter()  //  ��Ҫ����ע����̺�����¼�������
{

	Layer::onEnter();
	////ע���¼�������  ��������  hero�����ͷż���
	auto releaseSkillListener = EventListenerKeyboard::create();
	releaseSkillListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			//����clientPlayer
			clientPlayerAttack();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			//����clientPlayer
			/*
			clientPlayer->bonusAttack += 10;
			clientPlayerAttack();
			clientPlayer->skillAnimation();
			clientPlayer->bonusAttack -= 10;
			*/
		}
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	eventDispatcher->addEventListenerWithSceneGraphPriority(releaseSkillListener, this);

}
void GameControllerOnline::clientPlayerAttack() {
	//���͹�����Ϣ
	if (clientPlayer->getBloodNum() > 0) {
		Client::getInstance()->sendAttack();
		//����clientPlayer,�������жϣ�
		clientPlayer->attackEnemyAnimation(getAttackDir(clientPlayer->currentPos));//���Ź�������
		auto monster1Hit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, monster1->getPosition()));
		auto monster2Hit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, monster1->getPosition()));
		auto serverPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, serverPlayer->getPosition()));
		if (serverPlayerHit && serverPlayer->getBloodNum() >= 0) //�����ټ���hero2
			if (clientPlayer->inRect->containsPoint(serverPlayer->getPosition()))
				serverPlayer->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack);

		if (monster1Hit && monster1->blood >= 0) //�����ټ���hero2
			if (monster1->attack_rect->containsPoint(clientPlayer->getPosition()))
				monster1->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);

		if (monster2Hit && monster1->blood >= 0)//�����ټ���hero2
			if (monster2->attack_rect->containsPoint(clientPlayer->getPosition()))
				monster2->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);
		for (int i = 0; i < 3; i++) {
			auto testEnemy = clientPlayer->thisSoldierVector->at(i);
			auto checkPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, testEnemy->getPosition()));
			if (checkPlayerHit && testEnemy->attack_rect->containsPoint(clientPlayer->getPosition()))
				testEnemy->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);
		}
		auto testTower = clientPlayer->enemyTower;
		auto checkPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, testTower->getPosition()));
		if (checkPlayerHit && testTower->attack_rect->containsPoint(clientPlayer->getPosition()))
			testTower->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);
		auto testDefendTower = clientPlayer->enemyDefendTower;
		checkPlayerHit = checkHit(clientPlayer->currentPos, getNowPointDir(clientPlayer, testDefendTower->getPosition()));
		if (checkPlayerHit && testDefendTower->attack_rect->containsPoint(clientPlayer->getPosition())) {
			log("DefendTower minusBlood");
			testDefendTower->minusBlood(clientPlayer->getCommonAttack() + clientPlayer->bonusAttack, clientPlayer);
		}

	}
}
void GameControllerOnline::serverPlayerAttack() {
	//����clientPlayer,�������жϣ�
	serverPlayer->stopAllActions();
	serverPlayer->attackEnemyAnimation(getAttackDir(serverPlayer->currentPos));//���Ź�������
	serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(0));
	serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(1));
	serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
	//serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
	serverPlayer->autoAttack(serverPlayer->enemyDefendTower);
	serverPlayer->autoAttack(serverPlayer->enemyTower);
	serverPlayer->autoAttack(clientPlayer);
}
void GameControllerOnline::collidableCheck()
{
	//�պ�ĳ�clientPlayer
		auto pos = clientPlayer->getPosition();
		Vec2 tileCoord = this->tileCoordFromPosition(pos);
		//�����Ƭ��GID
		int tileGid = _collidable->getTileGIDAt(tileCoord);//ֻ����ײ��ʱ
		if (tileGid > 0 && lastCollidablePos!=pos) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//������ײ
			/*�����������stopAllactions��ָ���*/
			Client::getInstance()->sendStopAction();
			clientPlayer->stopAllActions();
			lastCollidablePos = pos;
		}
		
	}

void GameControllerOnline::createHero()
{
	hero1 = new Hero();
	hero2 = new Hero();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (PlayMode == 2)
	{
		clientPlayer = hero1;
		serverPlayer = hero2;
	}
	else
	{
		clientPlayer = hero2;
		serverPlayer = hero1;
	}

	clientPlayer->heroType = HeroRole;
	serverPlayer->heroType = EnemyHero;

	switch (HeroRole)       //  
	{
	case ChangE:
	{
		clientPlayer->image = Sprite::create(hero_ChangE);
		clientPlayer->addChild(clientPlayer->image);
		break;
	}
	case SunWukong:
	{
		clientPlayer->image = Sprite::create(hero_SunWukong);
		clientPlayer->addChild(clientPlayer->image);
		break;
	}
	case HuaMulan:
	{
		clientPlayer->image = Sprite::create(hero_HuaMulan);
		clientPlayer->addChild(clientPlayer->image);
		break;
	}
	default:break;
	}
	switch (EnemyHero)
	{
	case ChangE:
	{

		serverPlayer->image = Sprite::create(hero_ChangE);
		serverPlayer->addChild(serverPlayer->image);
		break;
	}
	case SunWukong:
	{

		serverPlayer->image = Sprite::create(hero_SunWukong);
		serverPlayer->addChild(serverPlayer->image);
		break;
	}
	case HuaMulan:
	{
		serverPlayer->image = Sprite::create(hero_HuaMulan);
		serverPlayer->addChild(serverPlayer->image);

	}
	default:break;
	}

}

void  GameControllerOnline::updateView(float dt)  //ˢ�º���
{
	this->setViewpointCenter(clientPlayer->getPosition());
	collidableCheck();
}

void GameControllerOnline::AI_Hero_Attack(float dt) {
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(0));
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(1));
		serverPlayer->autoAttack(serverPlayer->thisSoldierVector->at(2));
		//serverPlayer->autoAttack(serverPlayer->enemyDefendTower);
		serverPlayer->autoAttack(serverPlayer->enemyTower);
		serverPlayer->autoAttack(clientPlayer);

}


void GameControllerOnline::spriteRectCheck(float dt) {
	playTime++;
	clientPlayer->retain();
	serverPlayer->retain();
	
	if (serverPlayer->enemyTower->bloodNum <= 0 ) {
		this->unscheduleAllSelectors();
		GameResult[0] = playTime;
		GameResult[1] = clientPlayer->getExp();
		GameResult[2] = clientPlayer->killCount;
		GameResult[3] = clientPlayer->getMoney();
		playTime = 0;
		auto sc = GameResultFailure::createScene();
		Director::getInstance()->replaceScene(sc);
	}
	else {
		if (clientPlayer->enemyTower->bloodNum <= 0) {
			this->unscheduleAllSelectors();
			GameResult[0] = playTime;
			GameResult[1] = clientPlayer->getExp();
			GameResult[2] = clientPlayer->killCount;
			GameResult[3] = clientPlayer->getMoney();
			playTime = 0;
			auto sc = GameResultSuccess::createScene();
			Director::getInstance()->replaceScene(sc);
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
		clientSoldierVector[i]->setNewAttackRect();
		if (clientSoldierVector[i]->bloodNum > 0) {
			bool judge = clientSoldierVector[i]->checkHeroInRect();
			bool towerJudge = clientSoldierVector[i]->enemyTower->attack_rect->containsPoint(clientSoldierVector[i]->getPosition());
			bool defendtowerJudge = clientSoldierVector[i]->enemyDefendTower->attack_rect->containsPoint(clientSoldierVector[i]->getPosition());
			Tower* tempEnemyTower, *tempEnemyDefendTower;
			if (i <= 2) {
				tempEnemyTower = TowerVector.at(0);
				tempEnemyDefendTower = TowerVector.at(2);
			}
			else {
				tempEnemyTower = TowerVector.at(1);
				tempEnemyDefendTower = TowerVector.at(3);

			}

			if (clientSoldierVector[i]->isAttacking == false && clientSoldierVector[i]->isWalking == false) {
				int tempDir = getNowPointDir(clientSoldierVector[i], tempEnemyTower->getPosition()); 
				int attackDir = getAttackDir(tempDir);
				clientSoldierVector[i]->startWalkTowardsTower(attackDir);
				clientSoldierVector[i]->isWalking = true;
				log("enemy is walking");
				continue;
			}
			if (clientSoldierVector[i]->isAttacking == false && clientSoldierVector[i]->isWalking == true) {
				if (towerJudge &&clientSoldierVector[i]->enemyTower->bloodNum > 0) {		//��û�����ſ��Խ��빥��״̬
					clientSoldierVector[i]->isWalking = false;
					clientSoldierVector[i]->isAttacking = true;
					clientSoldierVector[i]->stopAllActions();
					clientSoldierVector[i]->scheduleAttack(1);
					log("enemy is attacking");
					continue;
				}
				if (defendtowerJudge &&clientSoldierVector[i]->enemyDefendTower->bloodNum > 0) {		//��û�����ſ��Խ��빥��״̬
					clientSoldierVector[i]->isWalking = false;
					clientSoldierVector[i]->isAttacking = true;
					clientSoldierVector[i]->stopAllActions();
					clientSoldierVector[i]->scheduleAttack(1);
					log("enemy is attacking");
					continue;
				}
				if (judge && clientSoldierVector[i]->enemyHero->getBloodNum() > 0) {		//Ӣ��û�����ſ��Խ��빥��״̬
					clientSoldierVector[i]->isWalking = false;
					clientSoldierVector[i]->isAttacking = true;
					clientSoldierVector[i]->stopAllActions();
					clientSoldierVector[i]->scheduleAttack(0);//0����
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
						int tempDir = getNowPointDir(clientSoldierVector[i], tempEnemyTower->getPosition());
						int attackDir = getAttackDir(tempDir);
						clientSoldierVector[i]->startWalkTowardsTower(attackDir);
						log("enemy stop attacking");
						continue;
					}
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
	Sprite* testReviveArea = (Sprite*)getChildByTag(1);
	auto inRect = new Rect(testReviveArea->getPositionX() - 100, testReviveArea->getPositionY() - 100, 200, 200);
	if (inRect->containsPoint(hero1->getPosition())) {
		hero1->addBlood(15);
	}
	testReviveArea = (Sprite*)getChildByTag(2);
	inRect = new Rect(testReviveArea->getPositionX() - 100, testReviveArea->getPositionY() - 100, 200, 200);
	if (inRect->containsPoint(hero2->getPosition())) {
		hero2->addBlood(15);
	}
}

void GameControllerOnline::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}


void GameControllerOnline::setViewpointCenter(Vec2 position)
{
	//log("setViewpointCenter");

	//log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//���Է�ֹ����ͼ��߳�����Ļ֮�⡣
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//���Է�ֹ����ͼ�ұ߳�����Ļ֮�⡣
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//ʹ���鴦����Ļ���ģ��ƶ���ͼĿ��λ��
	Vec2 pointB = Vec2(x, y);
	//log("Ŀ��λ�� (%f ,%f) ", pointB.x, pointB.y);

	//��ͼ�ƶ�ƫ����
	Vec2 offset = pointA - pointB;
	//log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);

}

Vec2 GameControllerOnline::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}


int GameControllerOnline::getNowPointDir(Node* player,Vec2 newpoint)
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
int GameControllerOnline::getAttackDir(int tempDir) { //ת��8������
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
void GameControllerOnline::setPlayerPosition(Vec2 position) {
	//hero1->stopAllActions();


	//�����ص�����ת��Ϊ��Ƭ����
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//�����Ƭ��GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);//ֻ����ײ��ʱ
	if (tileGid > 0) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//������ײ
		clientPlayer->stopAllActions();
		return;
	}
	//�ƶ�����
	clientPlayer->setPosition(position);
	//������ͼ
	this->setViewpointCenter(clientPlayer->getPosition());
	//hero1->stopAllActions();

	
}


bool GameControllerOnline::onTouchBegan(Touch* touch, Event* event)
{

	log("onTouchBegan");
	return true;
}

void GameControllerOnline::onTouchMoved(Touch *touch, Event *event)
{

	log("onTouchMoved");
}
bool GameControllerOnline::checkHit(int standDir, int monsterDir) { //������﷽��͹��﷽���Ƿ����
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
void GameControllerOnline::onTouchEnded(Touch *touch, Event *event)
{
	if (clientPlayer->getBloodNum() > 0) {

		if (clientPlayer->isHeroWalking == true)
			return;
		clientPlayer->isHeroWalking = true;
		clientPlayer->stopAllActions();
		clientPlayer->image->stopAllActions();

		//log("onTouchEnded");
		//�����OpenGL����
		Vec2 touchLocation = touch->getLocation();
		//ת��Ϊ��ǰ���ģ������ϵ
		touchLocation = this->convertToNodeSpace(touchLocation);

		Vec2 playerPos = clientPlayer->getPosition();
		Vec2 diff = touchLocation - playerPos;
		int newDir = getNowPointDir(clientPlayer, touchLocation);
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
			//SpriteFrame *spriteFrame = SpriteFrame::
			animation->addSpriteFrameWithFile(frameName->getCString());
		}
		animation->setDelayPerUnit(0.15f);
		animation->setRestoreOriginalFrame(false);
		Animate* action = Animate::create(animation);
		clientPlayer->image->runAction(RepeatForever::create(action));
		//log(_tileMap->getTileSize().height);
		Vec2 tileCoord = this->tileCoordFromPosition(touchLocation);
		//�����Ƭ��GID
		int tileGid = _collidable->getTileGIDAt(tileCoord);//ֻ����ײ��ʱ
		//log("new Gid %d", tileGid);
		if (tileGid > 0) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");//������ײ
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
		clientPlayer->runAction(MoveTo::create(dis*(speed - (float)(clientPlayer->bonusSpeed / 100.0)) / 100.0, touchLocation));
		clientPlayer->isHeroWalking = false;
		//clientPlayer->skillSprite->setPosition(touchLocation);
		//hero1->stopAllActions();
		//this->setViewpointCenter(hero1->getPosition()); //�ŵ�updateGame��ʵ��˳������
		//������·��Ϣ
		Client::getInstance()->sendClickPos(touchLocation.x, touchLocation.y);
	}
}

void GameControllerOnline::updateEnemy(float dt)
{
	std::vector<command> commands = Client::getInstance()->getCommands();
	for (auto &single_command : commands)
	{
		switch (single_command.command_type)
		{
		case 2:
		{
			this->serverPlayerAttack();
			break;
		}
		case 3:
		{
			serverPlayer->autoRun(Vec2(single_command.click_x, single_command.click_y));
			break;
		}
		case 4:
		{
			//�Է��Ͽ�����
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			clientPlayer->enemyTower->bloodNum = 0;
			auto linkLabel = LabelTTF::create(MyUtility::gbk_2_utf8("�Է�������"), "fonts/simkai.ttf", 35);
			linkLabel->setPosition(Vec2(origin.x + visibleSize.width*0.72, origin.y + visibleSize.height*1.45));
			linkLabel->setColor(Color3B::RED);
			this->addChild(linkLabel);
			break;
		}
		case 5:
		{
			serverPlayer->stopAllActions();
			break;
		}
		default:break;
		}
	}
}

