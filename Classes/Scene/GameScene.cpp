#include"Scene/GameScene.h"
Layer* GameScene::createScene()
{
	return GameScene::create();
}

//程序交互
bool GameScene::init()
{
	//创建地图
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	 _tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);
	return true;

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

