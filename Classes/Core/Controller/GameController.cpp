#include"Core/Controller/GameController.h"
#define hero_daji "hero/daji.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"
extern hero_role HeroRole;
Scene* GameController::createScene()
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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	map = GameScene::createScene();   //创建层对象  里面有地图
	this->addChild(map);

	createHero();   //创建英雄
	map->addChild(hero1);
	hero1->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height * 0.2));


	return true;



}
void GameController::createHero()//hero_role HeroRole)  //创建英雄
{
	switch (HeroRole)
	{
	case 0://daji:
	{
		hero1 = Hero::create(hero_daji);
		break;
	}
	case 1://yase:
	{
		hero1 = Hero::create(hero_yase);
		break;
	}
	case 2://houyi:
	{
		hero1 = Hero::create(hero_houyi);
		break;
	}
	default:break;
	}
}