#pragma once
#include"Scene/GameMap.h"
#define hero_daji "hero/daji.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"
bool GameMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	Sprite *heroDaji = Hero::create(hero_daji);
	//Sprite *heroDaji = Sprite::create(hero_daji);
	heroDaji->setPosition(Vec2(origin.x + visibleSize.width * 0.2, origin.y+visibleSize.height * 0.2));
	addChild(heroDaji);




	/*Hero hero_daji(hero);
	Sprite *sp = hero_daji;*/
	//addChild(sp);
	/*TMXObjectGroup *group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();*/


	//_player = Sprite::create("daji1.png");
	//_player->setPosition(Vec2(100,100));
	//addChild(_player, 2, 200);
	return true;

}


void GameMap::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}