#include"Scene/SelectHeroScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;
hero_role HeroRole; //定义一个全局变量  并且初始化

Scene*  SelectHeroScene::createScene()
{
	return  SelectHeroScene::create();
}

bool  SelectHeroScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);
	auto rootNode = CSLoader::createNode("SelectHeroScene.csb");
	auto ChangEbutton = static_cast<ui::Button*>(rootNode->getChildByName("CreateChange"));
	ChangEbutton->addClickEventListener(CC_CALLBACK_1(SelectHeroScene::ChangeCallBack, this));
	auto HuaMuLanbutton = static_cast<ui::Button*>(rootNode->getChildByName("CreateHuamulan"));
	HuaMuLanbutton->addClickEventListener(CC_CALLBACK_1(SelectHeroScene::HuamulanCallBack, this));
	auto SunWuKongbutton = static_cast<ui::Button*>(rootNode->getChildByName("CreateSunwukong"));
	SunWuKongbutton->addClickEventListener(CC_CALLBACK_1(SelectHeroScene::SunCallBack, this));
	addChild(rootNode);
	return true;

}


void  SelectHeroScene::ChangeCallBack(Ref *pSender)
{
	HeroRole =ChangE;   //给全局变量赋值
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void  SelectHeroScene::HuamulanCallBack(Ref *pSender)
{
	HeroRole = HuaMulan;   //给全局变量赋值
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void  SelectHeroScene::SunCallBack(Ref *pSender)
{
	HeroRole = SunWukong;   //给全局变量赋值
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}