#include"Core/Controller/EquipScene.h"
#include"Core/Controller/GameScene.h"


USING_NS_CC;
#include<vector>
#include<utility>

//各按钮位置
std::vector<std::pair<int, int> > equipButtonPosition = { std::pair<int, int>(325,570),std::pair<int, int>(560,570),std::pair<int, int>(805,570),\
std::pair<int, int>(1060, 570), std::pair<int, int>(325, 425), std::pair<int, int>(570, 425), std::pair<int, int>(805, 425),\
std::pair<int, int>(1060, 425), std::pair<int, int>(325, 270), std::pair<int, int>(570, 270), std::pair<int, int>(810, 270),\
std::pair<int, int>(1060, 270), std::pair<int, int>(330, 120), std::pair<int, int>(575, 120), std::pair<int, int>(818, 120),\
std::pair<int, int>(1062, 120) };

//为各个按钮加tag
enum EquipemntTag_c {
	weapon_1 = 0, weapon_2, weapon_3, weapon_4, armor_1, armor_2, armor_3, armor_4, accessory_1, accessory_2, accessory_3, \
	accessory_4, shoes_1, shoes_2, shoes_3, shoes_4
};
std::vector<int> equipmentTag_c = { weapon_1,weapon_2,weapon_3,weapon_4,armor_1,armor_2,armor_3,armor_4,accessory_1,accessory_2,accessory_3,\
accessory_4,shoes_1,shoes_2,shoes_3,shoes_4 };

//装备按钮的设置
std::vector<MenuItemToggle*> menuVector(16);

EquipScene* EquipScene::createScene()
{
	return EquipScene::create();
}

bool EquipScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//装备界面
	Sprite *equipbg = Sprite::create("equipground.png");
	equipbg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(equipbg);

	//循环设置装备按钮
	for (int i = 0; i < 16; ++i)
	{
		if (equipmentBoughtList[i] == 0)
		{
			auto state1 = MenuItemImage::create("storebutton/unbuy.png", "storebutton/unbuy.png");
			auto state2 = MenuItemImage::create("storebutton/unbuy.png", "storebutton/unbuy.png");
			menuVector[i] = MenuItemToggle::createWithCallback(CC_CALLBACK_1(EquipScene::equipCallback_s, this), state1, state2, NULL);
		}
		else
			if (equipmentBoughtList[i] == 1)
			{
				auto state1 = MenuItemImage::create("storebutton/equip.png", "storebutton/equip.png");
				auto state2 = MenuItemImage::create("storebutton/equipped.png", "storebutton/equipped.png");
				if (equipmentEquippedList[i] == 0)
				{
					menuVector[i] = MenuItemToggle::createWithCallback(CC_CALLBACK_1(EquipScene::equipCallback, this), state1, state2, NULL);
				}
				else
					if (equipmentEquippedList[i] == 1)
					{
						menuVector[i] = MenuItemToggle::createWithCallback(CC_CALLBACK_1(EquipScene::equipCallbackEquipped, this), state2, state1, NULL);
					}
			}
		menuVector[i]->setTag(equipmentTag_c[i]);
		menuVector[i]->setPosition(Vec2(equipButtonPosition[i].first, equipButtonPosition[i].second));
	}

	

	//返回按钮
	MenuItemImage *equipReturn = MenuItemImage::create("storereturn.png", "storereturn.png", CC_CALLBACK_1(EquipScene::equipReturnCallback, this));
	equipReturn->setPosition(Vec2(640, 55));

	Menu *mu = Menu::create(menuVector[0], menuVector[1], menuVector[2], menuVector[3], menuVector[4], menuVector[5], menuVector[6],\
	menuVector[7], menuVector[8], menuVector[9], menuVector[10], menuVector[11], menuVector[12], menuVector[13], menuVector[14],\
	menuVector[15], equipReturn, NULL);
	mu->setPosition(Vec2::ZERO);
	equipbg->addChild(mu);
	return true;
}

//返回按钮回调函数
void EquipScene::equipReturnCallback(Ref* pSender)
{
	this->removeFromParent();
}
//未装备回调函数
void EquipScene::equipCallback(Ref* pSender)
{
	MenuItemToggle* equipButton = (MenuItemToggle*)pSender;
	int tag = equipButton->getTag();
	int index = equipButton->getSelectedIndex();
	if (index == 1)
	{
		//取消已有装备
		if (tag >= weapon_1 && tag <= weapon_4)
		{
			for (int i = weapon_1; i <= weapon_4; ++i)
			{
				if (equipmentEquippedList[i] == 1)
				{
					menuVector[i]->activate();
					break;
				}
			}
		}
		if (tag >= armor_1 && tag <= armor_4)
		{
			for (int i = armor_1; i <= armor_4; ++i)
			{
				if (equipmentEquippedList[i] == 1)
				{
					menuVector[i]->activate();
					break;
				}
			}
		}
		if (tag >= accessory_1 && tag <= accessory_4)
		{
			for (int i = accessory_1; i <= accessory_4; ++i)
			{
				if (equipmentEquippedList[i] == 1)
				{
					menuVector[i]->activate();
					break;
				}
			}
		}
		if (tag >= shoes_1 && tag <= shoes_4)
		{
			for (int i = shoes_1; i <= shoes_4; ++i)
			{
				if (equipmentEquippedList[i] == 1)
				{
					menuVector[i]->activate();
					break;
				}
			}
		}
		//增加标记
		equipmentEquippedList[tag] = 1;
		//增加属性
		switch (tag)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
		case 11:

			break;
		case 12:

			break;
		case 13:

			break;
		case 14:

			break;
		case 15:

			break;
		}
	}
	else
		if (index == 0)
		{
			//撤销标记
			equipmentEquippedList[tag] = 0;
			//只撤销添加了的属性
			switch (tag)
			{
			case 0:

				break;
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			case 5:

				break;
			case 6:

				break;
			case 7:

				break;
			case 8:

				break;
			case 9:

				break;
			case 10:

				break;
			case 11:

				break;
			case 12:

				break;
			case 13:

				break;
			case 14:

				break;
			case 15:

				break;
			}
		}
}
//已装备回调函数
void EquipScene::equipCallbackEquipped(Ref* pSender)
{
	MenuItemToggle* equipButton = (MenuItemToggle*)pSender;
	int tag = equipButton->getTag();
	if (equipButton->getSelectedIndex() == 1)
	{
		//撤销标记
		equipmentEquippedList[tag] = 0;
		//只撤销添加了的属性
		switch (tag)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
		case 11:

			break;
		case 12:

			break;
		case 13:

			break;
		case 14:

			break;
		case 15:

			break;
		}
	}
	else
		if (equipButton->getSelectedIndex() == 0)
		{
			//取消已有装备
			if (tag >= weapon_1 && tag <= weapon_4)
			{
				for (int i = weapon_1; i <= weapon_4; ++i)
				{
					if (equipmentEquippedList[i] == 1)
					{
						menuVector[i]->activate();
						break;
					}
				}
			}
			if (tag >= armor_1 && tag <= armor_4)
			{
				for (int i = armor_1; i <= armor_4; ++i)
				{
					if (equipmentEquippedList[i] == 1)
					{
						menuVector[i]->activate();
						break;
					}
				}
			}
			if (tag >= accessory_1 && tag <= accessory_4)
			{
				for (int i = accessory_1; i <= accessory_4; ++i)
				{
					if (equipmentEquippedList[i] == 1)
					{
						menuVector[i]->activate();
						break;
					}
				}
			}
			if (tag >= shoes_1 && tag <= shoes_4)
			{
				for (int i = shoes_1; i <= shoes_4; ++i)
				{
					if (equipmentEquippedList[i] == 1)
					{
						menuVector[i]->activate();
						break;
					}
				}
			}
			//增加标记
			equipmentEquippedList[tag] = 1;
			//增加属性
			switch (tag)
			{
			case 0:

				break;
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			case 5:

				break;
			case 6:

				break;
			case 7:

				break;
			case 8:

				break;
			case 9:

				break;
			case 10:

				break;
			case 11:

				break;
			case 12:

				break;
			case 13:

				break;
			case 14:

				break;
			case 15:

				break;
			}
		}
}
//虚设回调函数
void EquipScene::equipCallback_s(Ref* pSender)
{
}
