#include"Core/Controller/GameSceneOnline.h"
#include"Core/Net/Client.h"

#include<vector>
using namespace cocos2d::ui;

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
	storeItem->setPosition(origin.x + visibleSize.width * 0.98, origin.y + visibleSize.height * 0.11);
	MenuItemImage *equipmentItem = MenuItemImage::create("equipmentbutton.png", "equipmentbutton.png", CC_CALLBACK_1(GameSceneOnline::equipmentItemCallback, this));
	equipmentItem->setPosition(origin.x + visibleSize.width *0.97, origin.y + visibleSize.height * 0.03);
	MenuItemImage *moneyitem = MenuItemImage::create("money.png", "money.png");
	moneyitem->setPosition(origin.x + visibleSize.width * 0.98, origin.y + visibleSize.height * 0.23);

	MenuItemImage *expitem = MenuItemImage::create("exp.png", "exp.png");
	expitem->setPosition(origin.x + visibleSize.width * 0.98, origin.y + visibleSize.height * 0.35);
	MenuItemImage *surrenderItem = MenuItemImage::create("surrender.png", "surrender.png", CC_CALLBACK_1(GameSceneOnline::surrenderItemCallback, this));
	surrenderItem->setPosition(origin.x + visibleSize.width * 0.98, origin.y + visibleSize.height * 0.45);

	displayskillicon();
	this->schedule(schedule_selector(GameSceneOnline::displaymoney), 1.0f);
	this->schedule(schedule_selector(GameSceneOnline::displayexp), 1.0f);

	//创建聊天框
	MenuItemImage *chatItem = MenuItemImage::create("chatbutton.png", "chatbutton.png", CC_CALLBACK_1(GameSceneOnline::chatItemCallback, this));
	chatItem->setPosition(origin.x + visibleSize.width * 0.97, origin.y + visibleSize.height * 0.5);
	_chatLayer = ChatLayer::createScene();
	addChild(_chatLayer);
	chatOpen = true;
	
	Menu *mu = Menu::create(storeItem, equipmentItem, moneyitem, expitem, surrenderItem,chatItem, NULL);
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
void GameSceneOnline::displaymoney(float dt)
{
	this->removeChildByTag(13, true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto money = std::to_string(clientPlayer->getMoney());
	Text *text1 = Text::create(money, "fonts/Marker Felt.ttf", 40);
	text1->setColor(Color3B(128, 0, 128));  //设置颜色
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.98, origin.y + visibleSize.height *0.19));

	this->addChild(text1, 6, 13);
}

void GameSceneOnline::chatItemCallback(Ref *pSender)
{
	if (chatOpen == true)
	{
		_chatLayer->setVisible(false);
		chatOpen = false;
	}
	else
	{
		_chatLayer->setVisible(true);
		chatOpen = true;
	}
}

void GameSceneOnline::displayexp(float dt)
{
	this->removeChildByTag(35, true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto exp = std::to_string(clientPlayer->getExp());
	Text *text1 = Text::create(exp, "fonts/Marker Felt.ttf", 40);
	text1->setColor(Color3B(128, 0, 128));  //设置颜色
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.98, origin.y + visibleSize.height *0.3));

	this->addChild(text1, 7, 35);
}

void GameSceneOnline::displayskillicon()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Text *text1 = Text::create(MyUtility::gbk_2_utf8("W:释放普通技能"), "font/Marker Felt.ttf", 20);
	text1->setColor(Color3B(32, 178, 170));  //设置颜色
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height *0.55));
	this->addChild(text1);

}
void GameSceneOnline::surrenderItemCallback(Ref *pSender){//投降
	clientPlayer->friendTower->bloodNum = 0;
	/*这里向对方发送退出信息*/
	Client::getInstance()->sendExit();
}
GameSceneOnline::~GameSceneOnline()
{
	Client::getInstance()->sendExit();
	Client::getInstance()->clear();
}