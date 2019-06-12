#pragma once
#include "cocos2d.h"
#include"Core/Controller/GameController.h"
#include"Scene/SelectHeroScene.h"
#include"Core/Controller/StoreScene.h"
#include"Core/Controller/EquipScene.h"

//ȫ�ֱ���
#include<vector>
extern std::vector<int> equipmentBoughtList;//��ǵ�ǰӵ��װ����״̬
extern std::vector<int> equipmentEquippedList;//��ǵ�ǰװ��װ����״̬


class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void storeItemCallback(Ref *pSender);// �����̳�
	void equipmentItemCallback(Ref *pSender);//����װ���鿴
	CREATE_FUNC(GameScene);
};