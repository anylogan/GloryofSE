#include"Core/Controller/GameSceneOnline.h"
#include"Core/Net/Client.h"
#include<vector>
using namespace cocos2d::ui;

//ȫ�ֱ�����ʼ��
extern std::vector<int> equipmentBoughtList;//��ǵ�ǰӵ��װ����״̬
extern std::vector<int> equipmentEquippedList;//��ǵ�ǰװ��װ����״̬

Scene* GameSceneOnline::createScene()

{
	return GameSceneOnline::create();
}

bool GameSceneOnline::init()
{
	equipmentBoughtList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//��ǵ�ǰӵ��װ����״̬
	equipmentEquippedList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//��ǵ�ǰװ��װ����״̬
	auto controller = GameControllerOnline::createScene();//�������Ʋ�
	addChild(controller);
	//�����̳Ǽ�װ���鿴����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemImage *storeItem = MenuItemImage::create("shopbutton.png", "shopbutton.png", CC_CALLBACK_1(GameSceneOnline::storeItemCallback, this));
	storeItem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.92);
	MenuItemImage *equipmentItem = MenuItemImage::create("equipmentbutton.png", "equipmentbutton.png", CC_CALLBACK_1(GameSceneOnline::equipmentItemCallback, this));
	equipmentItem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.85);
	MenuItemImage *moneyitem = MenuItemImage::create("money.png", "money.png");
	moneyitem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.75);

	MenuItemImage *expitem = MenuItemImage::create("exp.png", "exp.png");
	expitem->setPosition(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height * 0.65);

	Menu *mu = Menu::create(storeItem, equipmentItem, moneyitem, expitem, NULL);
	mu->setPosition(Vec2::ZERO);
	addChild(mu);
	displayskillicon();
	this->schedule(schedule_selector(GameSceneOnline::displaymoney), 1.0f);
	this->schedule(schedule_selector(GameSceneOnline::displayexp), 1.0f);
	return true;
}

//�̳Ǻͱ�������ص�����
void GameSceneOnline::storeItemCallback(Ref *pSender)
{
	auto storescene = StoreScene::createScene();//�������Ʋ�
	addChild(storescene);
}
void GameSceneOnline::equipmentItemCallback(Ref *pSender)
{
	auto equipscene = EquipScene::createScene();//�������Ʋ�
	addChild(equipscene);
}
void GameSceneOnline::displaymoney(float dt)
{
	this->removeChildByTag(13, true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto money = std::to_string(clientPlayer->getMoney());
	Text *text1 = Text::create(money, "font/Marker Felt.ttf", 40);
	text1->setColor(Color3B(128, 0, 128));  //������ɫ
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height *0.7));

	this->addChild(text1, 6, 13);
}
void GameSceneOnline::displayexp(float dt)
{
	this->removeChildByTag(35, true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto exp = std::to_string(clientPlayer->getExp());
	Text *text1 = Text::create(exp, "font/Marker Felt.ttf", 40);
	text1->setColor(Color3B(128, 0, 128));  //������ɫ
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.03, origin.y + visibleSize.height *0.6));

	this->addChild(text1, 7, 35);
}

void GameSceneOnline::displayskillicon()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Text *text1 = Text::create(MyUtility::gbk_2_utf8("W:�ͷ���ͨ����"), "font/Marker Felt.ttf", 20);
	text1->setColor(Color3B(32, 178, 170));  //������ɫ
	text1->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height *0.55));
	this->addChild(text1);

}