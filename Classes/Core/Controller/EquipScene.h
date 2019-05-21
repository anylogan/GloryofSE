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
	void equipReturnCallback(Ref* pSender);//���ذ�ť�ص�����
	void equipCallback(Ref* pSender);//δװ����ť�ص�����
	void equipCallbackEquipped(Ref* pSender);//��װ������ť�ص�����
	void equipCallback_s(Ref* pSender);//����ص�����
	CREATE_FUNC(EquipScene);
};


#endif
