#include"Core/Controller/StoreScene.h"
#include"Core/Controller/GameScene.h"


USING_NS_CC;
#include<vector>
#include<utility>

int playMoney=0;
//各购买按钮位置
std::vector<std::pair<int, int> > storeButtonPosition = { std::pair<int, int>(325,570),std::pair<int, int>(560,570),std::pair<int, int>(805,570),\
std::pair<int, int>(1060, 570), std::pair<int, int>(325, 425), std::pair<int, int>(570, 425), std::pair<int, int>(805, 425),\
std::pair<int, int>(1060, 425), std::pair<int, int>(325, 270), std::pair<int, int>(570, 270), std::pair<int, int>(810, 270),\
std::pair<int, int>(1060, 270), std::pair<int, int>(330, 120), std::pair<int, int>(575, 120), std::pair<int, int>(818, 120),\
std::pair<int, int>(1062, 120) };

//为各个装备加tag
enum EquipemntTag {weapon_1=0,weapon_2,weapon_3,weapon_4,armor_1,armor_2,armor_3,armor_4,accessory_1,accessory_2,accessory_3,\
accessory_4,shoes_1,shoes_2,shoes_3,shoes_4};
std::vector<int> equipmentTag = { weapon_1,weapon_2,weapon_3,weapon_4,armor_1,armor_2,armor_3,armor_4,accessory_1,accessory_2,accessory_3,\
accessory_4,shoes_1,shoes_2,shoes_3,shoes_4 };

StoreScene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//商店界面
	Sprite *storebg = Sprite::create("storeground.png");
	storebg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(storebg,1,155);
	playMoney = clientPlayer->getMoney();
	//金钱的显示
	auto moneyLabel = LabelTTF::create("Money:  0", "Arial", 58);
	moneyLabel->setPosition(Vec2(630, 705));
	moneyLabel->setColor(Color3B(139,69,19));
	moneyLabel->setString(String::createWithFormat("Money:  %d", playMoney)->getCString());
	storebg->addChild(moneyLabel, 1, 156);

	//循环设置购买按钮
	for (int i = 0; i < 16; ++i)
	{
		//若已购买，显示已购买，否则先计算价格，按价格显示能否购买
			if (equipmentBoughtList[i] == 0)
			{
				int tg = i % 4;
				int leftMoney = 0;
				switch (tg)
				{
				case 0:
					leftMoney = playMoney - 100;
					break;
				case 1:
					leftMoney = playMoney - 250;
					break;
				case 2:
					leftMoney = playMoney - 400;
					break;
				case 3:
					leftMoney = playMoney - 600;
					break;
				}
				if (leftMoney >= 0)
				{
					ui::RadioButton* button = nullptr;
					switch (tg)
					{
					case 0:
						button = ui::RadioButton::create("storebutton/100buy.png", "storebutton/bought.png");
						break;
					case 1:
						button = ui::RadioButton::create("storebutton/250buy.png", "storebutton/bought.png");
						break;
					case 2:
						button = ui::RadioButton::create("storebutton/400buy.png", "storebutton/bought.png");
						break;
					case 3:
						button = ui::RadioButton::create("storebutton/600buy.png", "storebutton/bought.png");
						break;
					}
					button->setTag(equipmentTag[i]);
					button->setPosition(Vec2(storeButtonPosition[i].first, storeButtonPosition[i].second));
					button->addTouchEventListener(CC_CALLBACK_1(StoreScene::buyCallback, this));
					storebg->addChild(button);
				}
				else
				{
					Sprite *button = Sprite::create("storebutton/lackmoney.png");
					button->setPosition(Vec2(storeButtonPosition[i].first, storeButtonPosition[i].second));
					storebg->addChild(button);
				}
			}
			else
				if(equipmentBoughtList[i] == 1)
				{

					Sprite *button = Sprite::create("storebutton/bought.png");
					button->setPosition(Vec2(storeButtonPosition[i].first, storeButtonPosition[i].second));
					storebg->addChild(button);
				}
	}
	

	//返回按钮
	MenuItemImage *storeReturn = MenuItemImage::create("storereturn.png", "storereturn.png", CC_CALLBACK_1(StoreScene::storeReturnCallback, this));
	storeReturn->setPosition(Vec2(640,55));
	
	Menu *mu = Menu::create(storeReturn,NULL);
	mu->setPosition(Vec2::ZERO);
	storebg->addChild(mu);
	return true;
}

//返回按钮回调函数
void StoreScene::storeReturnCallback(Ref* pSender)
{
	this->removeFromParent();
	this->release();
}
//购买按钮回调函数
void StoreScene::buyCallback(Ref* pSender)
{
	ui::RadioButton* button = (ui::RadioButton*)pSender;
	int tag = button->getTag();
	//先计算价格，看能否购买
	int leftMoney = 0;
	switch (tag%4)
	{
	case 0:
		leftMoney = playMoney - 100;
		break;
	case 1:
		leftMoney = playMoney - 250;
		break;
	case 2:
		leftMoney = playMoney - 400;
		break;
	case 3:
		leftMoney = playMoney - 600;
		break;
	}
	//由于button按钮点击会响应多次， equipmentBoughtList[tag] ==0判断的作用是使按钮的显示效果只有一次
	if (leftMoney >= 0&& equipmentBoughtList[tag] ==0)
	{
		clientPlayer->setMoney(leftMoney);
		equipmentBoughtList[tag] = 1;
		//更新金钱显示
		LabelTTF *label = (LabelTTF*)(this->getChildByTag(155)->getChildByTag(156));
		label->setString(String::createWithFormat("Money:  %d", playMoney)->getCString());
	}
	else
		if(equipmentBoughtList[tag] == 0)
	{
		Sprite *button = Sprite::create("storebutton/lackmoney.png");
		button->setPosition(Vec2(storeButtonPosition[tag].first, storeButtonPosition[tag].second));
		this->getChildByTag(155)->addChild(button);
	}
}