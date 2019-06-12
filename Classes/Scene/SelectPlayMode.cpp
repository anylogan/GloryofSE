#include"Scene/SelectPlayMode.h"
#include "cocostudio/CocoStudio.h"
#include"Scene/SelectHeroScene.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;

Client* Client::instance = nullptr;

Scene*  SelectPlayMode::createScene()
{
	return  SelectPlayMode::create();
}

bool  SelectPlayMode::init()
{
	if (!Scene::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);
	auto rootNode = CSLoader::createNode("SelectPlayMethod.csb");
	auto ChangEbutton = static_cast<ui::Button*>(rootNode->getChildByName("Single"));
	ChangEbutton->addClickEventListener(CC_CALLBACK_1(SelectPlayMode::SingleModeCallBack, this));
	auto HuaMuLanbutton = static_cast<ui::Button*>(rootNode->getChildByName("Online"));
	HuaMuLanbutton->addClickEventListener(CC_CALLBACK_1(SelectPlayMode::OnlineModeCallBack, this));
	
	addChild(rootNode);
	return true;

}


void  SelectPlayMode::SingleModeCallBack(Ref *pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto scene = SelectHeroScene::createScene();
	scene->setTag(010);
	Director::getInstance()->replaceScene(scene);
}
void  SelectPlayMode::OnlineModeCallBack(Ref *pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto scene = SelectHeroScene::createScene();
	scene->setTag(020);
	Client::getInstance()->connectWithServer();
	Director::getInstance()->replaceScene(scene);
}
