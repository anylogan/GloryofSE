#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include"Core/Sprite/Hero.h"

USING_NS_CC;
class GameMap : public cocos2d::Layer
{
private:
	TMXTiledMap * _tileMap;
	Sprite *_player;
public:

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	//virtual bool OnTouchBegan(Touch*touch, Event*event);
	//virtual void OnTouchMoved(Touch*touch, Event*event);
	//virtual void OnTouchEnded(Touch*touch, Event*event);
	CREATE_FUNC(GameMap);
};

#endif // __HELLOWORLD_SCENE_H__