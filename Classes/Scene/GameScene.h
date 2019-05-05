#pragma once
//在游戏中加载地图
//创建地图

#include"cocos2d.h"

USING_NS_CC;

//游戏场景类
//在游戏场景中加载游戏地图

class GameScene :public cocos2d::Layer
{
public:	

//属性
	TMXTiledMap * _tileMap;
//方法
	static cocos2d::Layer* createScene();
	virtual bool init();
	
	//以下为移动精灵函数
	//bool onTouchBegan(Touch *touch, Event*unused_event);
	//void onTouchEnded(Touch *touch, Event*unused_event);
	//void onTouchMoved(Touch *touch, Event*unused_event);

	CREATE_FUNC(GameScene);
};
