#pragma once
#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__
#include "cocos2d.h"
#include"ui/UIRadioButton.h"
class Hero;
extern Hero* clientPlayer;


class StoreScene :public cocos2d::Layer
{
public:
	static StoreScene* createScene();
	virtual bool init();
	void storeReturnCallback(Ref* pSender);//返回按钮回调函数
	void buyCallback(Ref* pSender);//购买按钮回调函数
	CREATE_FUNC(StoreScene);
};


#endif