#pragma once
#include "cocos2d.h"
#include"Core/Controller/GameController.h"
#include"Scene/SelectHeroScene.h"
class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);
};