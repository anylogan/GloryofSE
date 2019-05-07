#include"Scene/GameScene.h"
#define hero_daji "hero/daji.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"
#define map1_buff_num 8
//extern hero_role HeroRole;
GameScene* GameScene::createScene()
{
	return (GameScene*)GameScene::create();
}

//程序交互
bool GameScene::init()
{
	//创建地图
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);


	createHero();   //创建英雄
	hero1->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
	this->addChild(hero1);

	createBuff();  //创建Buff

				   //创建CannonFodder     简单起见  实现隔一段时间创建一队炮灰让他们沿着固定路径前进  

	createCannonFodder();  //创建炮灰

	return true;

}
void GameScene::createHero()//hero_role HeroRole)  //创建英雄
{
	switch (HeroRole)
	{
	case 0://daji:
	{
		hero1 = (Hero*)Hero::create(hero_daji);
		break;
	}
	case 1://yase:
	{
		hero1 = (Hero*)Hero::create(hero_yase);
		break;
	}
	case 2://houyi:
	{
		hero1 = (Hero*)Hero::create(hero_houyi);
		break;
	}
	default:break;
	}
}

void GameScene::createBuff()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < map1_buff_num; i++)
	{
		Buff *buff = new Buff();// ("npc/buff1.png");
		buff->initWithFile("npc/buff1.png");
		buff->setPosition(Vec2(origin.x + visibleSize.width * (0.1*i), origin.y + visibleSize.height * 0.2));// 设置野怪的位置  让它在初始位置生成
		this->addChild(buff);    //加到层中
		BuffVector.pushBack(buff);   //加到容器中
	}
}

void GameScene::createCannonFodder() //创建炮灰
{




}

void GameScene::onEnter()  //  主要用来注册事件监听器
{
	//
	Layer::onEnter();
	//注册事件监听器  监听键盘  hero可以释放技能
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)    //放大招 
		{
			attackBigTrick();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)    //放中招 
		{
			attackMediumTrick();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)    //放小招 
		{
			attackSmallTrick();
		}

	};

	listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	this->schedule(schedule_selector(GameScene::updateGame), 0.2f);
	/*this->schedule(schedule_selector(GameScene::updateGame), 0.2f);*/
}

void GameScene::updateGame(float dt)  //刷新函数
{



}
bool GameScene::attackBigTrick()   //攻击方法  放大招
{
	if (hero1&& hero1->isVisible()) {
		Skill* skill = Skill::createWithSpriteFrameName("skills/skill.png");
		skill->setVelocity(Vec2(0, GameSceneSkillVelocity));
		this->addChild(skill, 0, GameSceneNodeBatchTagSkill);
		skill->releaseSkillFromHero(hero1);
	}
	return true;
}
bool GameScene::attackMediumTrick()   //  放中招
{
	return true;
}
bool GameScene::attackSmallTrick()   //  放小招
{
	return true;
}
void GameScene::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

//bool GameScene::onTouchBegan(Touch *touch, Event*unused_event)
//{
//	log("OnTouchBegan");
//	return true;
//
//}
//void GameScene::onTouchEnded(Touch *touch, Event*unused_event)
//{
//	log("OnTouchMoved");
//
//}
//void GameScene::onTouchMoved(Touch *touch, Event*unused_event)
//{
//	log("onTouchEnded");
//	//获得OpenGL坐标
//	Vec2 touchLocation = touch->getLocation();
//	//log("touchLocation (%f ,%f) ", touchLocation.x, touchLocation.y);
//
//	Vec2 HeroPos = hero1->getPosition();
//	Vec2 diff = touchLocation - HeroPos;
//
//	if (abs(diff.x) > abs(diff.y)) {
//		if (diff.x > 0) {
//			HeroPos.x += _tileMap->getTileSize().width;
//			hero1->runAction(FlipX::create(false));
//		}
//		else {
//			HeroPos.x -= _tileMap->getTileSize().width;
//			hero1->runAction(FlipX::create(true));
//		}
//	}
//	else {
//		if (diff.y > 0) {
//			HeroPos.y += _tileMap->getTileSize().height;
//		}
//		else {
//			HeroPos.y -= _tileMap->getTileSize().height;
//		}
//	}
//	//log("HeroPos (%f ,%f) ", HeroPos.x, HeroPos.y);
//	hero1->setPosition(HeroPos);
//
//
//
//}
//

