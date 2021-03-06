#pragma once
#include "cocos2d.h"
#include"Core/Controller/GameControllerOnline.h"
#include"Scene/SelectHeroScene.h"
#include"Core/Controller/StoreScene.h"
#include"Core/Controller/EquipScene.h"
#include"ui/CocosGUI.h"
#include"Scene/GlobalDefine.h"
#include"proj.win32/MyUtility.h"
#include "cocostudio/CocoStudio.h"
#include"Core/Chat/ChatLayer.h"
//全局变量
#include<vector>
extern std::vector<int> equipmentBoughtList;//标记当前拥有装备的状态
extern std::vector<int> equipmentEquippedList;//标记当前装备装备的状态


class GameSceneOnline : public cocos2d::Scene
{
public:
	~GameSceneOnline();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void storeItemCallback(Ref *pSender);// 创建商城
	void equipmentItemCallback(Ref *pSender);//创建装备查看
	void chatItemCallback(Ref *pSender);  //聊天框的打开关闭
	bool chatOpen;
	ChatLayer* _chatLayer;
	void  displaymoney(float dt);   //显示金币
	void  displayexp(float dt);     //显示经验
	void  displayskillicon();
	void surrenderItemCallback(Ref * pSender);
	CREATE_FUNC(GameSceneOnline);

};