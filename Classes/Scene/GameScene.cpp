#include"Scene/GameScene.h"

Scene* GameScene::createScene()
{
	return GameScene::create();
}


//³ÌÐò½»»¥
bool GameScene::init()
{
	auto map = GameMap::create();
	addChild(map);
	return true;

}
