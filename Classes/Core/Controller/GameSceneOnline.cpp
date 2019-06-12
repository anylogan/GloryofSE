#include"Core/Controller/GameSceneOnline.h"
#include"Core/Net/Client.h"
#include<vector>
//全局变量初始化
extern std::vector<int> equipmentBoughtList;//标记当前拥有装备的状态
extern std::vector<int> equipmentEquippedList;//标记当前装备装备的状态

Scene* GameSceneOnline::createScene()

{
	return GameSceneOnline::create();
}

bool GameSceneOnline::init()
{
	equipmentBoughtList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//标记当前拥有装备的状态
	equipmentEquippedList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//标记当前装备装备的状态
	auto controller = GameControllerOnline::createScene();//创建控制层
	addChild(controller);
	//创建商城及装备查看界面
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemImage *storeItem = MenuItemImage::create("shopbutton.png", "shopbutton.png", CC_CALLBACK_1(GameSceneOnline::storeItemCallback, this));
	storeItem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.92);
	MenuItemImage *equipmentItem = MenuItemImage::create("equipmentbutton.png", "equipmentbutton.png", CC_CALLBACK_1(GameSceneOnline::equipmentItemCallback, this));
	equipmentItem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.85);
	Menu *mu = Menu::create(storeItem, equipmentItem, NULL);
	mu->setPosition(Vec2::ZERO);
	addChild(mu);
	return true;
}

//商城和背包界面回调函数
void GameSceneOnline::storeItemCallback(Ref *pSender)
{
	auto storescene = StoreScene::createScene();//创建控制层
	addChild(storescene);
}
void GameSceneOnline::equipmentItemCallback(Ref *pSender)
{
	auto equipscene = EquipScene::createScene();//创建控制层
	addChild(equipscene);
}
