#pragma once
#include "cocos2d.h"
#include"Core/Controller/GameControllerOnline.h"
#include"Scene/SelectHeroScene.h"
#include"Core/Controller/StoreScene.h"
#include"Core/Controller/EquipScene.h"
#include"ui/CocosGUI.h"
#include"Scene/GlobalDefine.h"
#include"proj.win32/MyUtility.h"
//全局变量
#include<vector>
extern std::vector<int> equipmentBoughtList;//标记当前拥有装备的状态
extern std::vector<int> equipmentEquippedList;//标记当前装备装备的状态


class GameSceneOnline : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void storeItemCallback(Ref *pSender);// 创建商城
	void equipmentItemCallback(Ref *pSender);//创建装备查看
	void  displaymoney(float dt);   //显示金币
	void  displayexp(float dt);     //显示经验
	void  displayskillicon();
	CREATE_FUNC(GameSceneOnline);
};