#include"Core/Controller/GameScene.h"
//#include"Core/Net/Client.h"
#include<vector>
using namespace cocos2d::ui;
//全局变量初始化
std::vector<int> equipmentBoughtList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//标记当前拥有装备的状态
std::vector<int> equipmentEquippedList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//标记当前装备装备的状态
																			 //Client *Client::instance = nullptr;
extern hero_role HeroRole;
Scene* GameScene::createScene()

{
	return GameScene::create();
}

bool GameScene::init()
{
	auto controller = GameController::createScene();//创建控制层
	addChild(controller);
	//创建商城及装备查看界面
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemImage *storeItem = MenuItemImage::create("shopbutton.png", "shopbutton.png", CC_CALLBACK_1(GameScene::storeItemCallback, this));
	storeItem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.92);
	MenuItemImage *equipmentItem = MenuItemImage::create("equipmentbutton.png", "equipmentbutton.png", CC_CALLBACK_1(GameScene::equipmentItemCallback, this));
	equipmentItem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.85);
	MenuItemImage *moneyitem = MenuItemImage::create("money.png", "money.png");
	moneyitem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.75);

	MenuItemImage *expitem = MenuItemImage::create("exp.png", "exp.png");
	expitem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.65);


	Menu *mu = Menu::create(storeItem, equipmentItem, moneyitem, expitem, NULL);
	mu->setPosition(Vec2::ZERO);
	addChild(mu);

	displayskillicon();
	this->schedule(schedule_selector(GameScene::displaymoney), 1.0f);
	this->schedule(schedule_selector(GameScene::displayexp), 1.0f);
	return true;
}

//商城和背包界面回调函数
void GameScene::storeItemCallback(Ref *pSender)
{
	auto storescene = StoreScene::createScene();//创建控制层
	addChild(storescene);
}
void GameScene::equipmentItemCallback(Ref *pSender)
{
	auto equipscene = EquipScene::createScene();//创建控制层
	addChild(equipscene);
}
void GameScene::displaymoney(float dt)
{
	this->removeChildByTag(13, true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto money = std::to_string(clientPlayer->getMoney());
	Text *text1 = Text::create(money, "fonts/Marker Felt.ttf", 40);
	text1->setColor(Color3B(128, 0, 128));  //设置颜色
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height *0.7));

	this->addChild(text1, 6, 13);
}
void GameScene::displayexp(float dt)
{
	this->removeChildByTag(35, true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto exp = std::to_string(clientPlayer->getExp());
	Text *text1 = Text::create(exp, "fonts/Marker Felt.ttf", 40);
	text1->setColor(Color3B(128, 0, 128));  //设置颜色
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height *0.6));

	this->addChild(text1, 7, 35);
}

void GameScene::displayskillicon()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Text *text1 = Text::create(MyUtility::gbk_2_utf8("W:释放普通技能"), "", 20);
	text1->setColor(Color3B(32, 178, 170));  //设置颜色
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height *0.55));
	MenuItemImage *skillitem;
	if (HeroRole == ChangE)
	{
		skillitem = MenuItemImage::create(hero_ChangE_attack, hero_ChangE_attack);
	}
	else if (HeroRole == HuaMulan)
	{
		skillitem = MenuItemImage::create(hero_HuaMulan_attack, hero_HuaMulan_attack);
	}
	else
	{
		skillitem = MenuItemImage::create(hero_SunWukong_attack, hero_SunWukong_attack);
	}
	skillitem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.5);


	Text *text2 = Text::create(MyUtility::gbk_2_utf8("A:释放大招"), "", 20);
	text2->setColor(Color3B(32, 178, 170));  //设置颜色
	text2->setPosition(Vec2(origin.x + visibleSize.width * 0.036, origin.y + visibleSize.height *0.4));
	MenuItemImage *skillitem2;
	if (HeroRole == ChangE)
	{
		skillitem2 = MenuItemImage::create("skills/role_skill/ziqidonglai/ziqidonglai0.png", "skills/role_skill/ziqidonglai/ziqidonglai0.png");
	}
	else if (HeroRole == HuaMulan)
	{
		skillitem2 = MenuItemImage::create("skills/kongjumo/skill_kongjimo_00003.png", "skills/kongjumo/skill_kongjimo_00003.png");
	}
	else
	{
		skillitem2 = MenuItemImage::create("skills/xixue/skill_xixue_00003.png", "skills/xixue/skill_xixue_00003.png");
	}
	skillitem2->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.25);
	this->addChild(text1);
	this->addChild(text2);
	this->addChild(skillitem);
	this->addChild(skillitem2);
}