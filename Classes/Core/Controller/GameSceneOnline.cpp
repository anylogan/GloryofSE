#include"Core/Controller/GameSceneOnline.h"
#include"Core/Net/Client.h"
#include<vector>
//ȫ�ֱ�����ʼ��
std::vector<int> equipmentBoughtList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//��ǵ�ǰӵ��װ����״̬
std::vector<int> equipmentEquippedList = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//��ǵ�ǰװ��װ����״̬
Client *Client::instance = nullptr;

Scene* GameSceneOnline::createScene()

{
	return GameSceneOnline::create();
}

bool GameSceneOnline::init()
{
	auto controller = GameController::createScene();//�������Ʋ�
	addChild(controller);
	//�����̳Ǽ�װ���鿴����
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
