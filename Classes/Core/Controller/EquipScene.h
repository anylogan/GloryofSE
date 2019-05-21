#pragma once
#ifndef __EQUIP_SCENE_H__
#define __EQUIP_SCENE_H__


#include "cocos2d.h"
#include"ui/UIRadioButton.h"



class EquipScene :public cocos2d::Layer
{
public:
	static EquipScene* createScene();
	virtual bool init();
	void equipReturnCallback(Ref* pSender);//返回按钮回调函数
	void equipCallback(Ref* pSender);//未装备按钮回调函数
	void equipCallbackEquipped(Ref* pSender);//已装备购买按钮回调函数
	void equipCallback_s(Ref* pSender);//虚设回调函数
	CREATE_FUNC(EquipScene);
};


#endif
