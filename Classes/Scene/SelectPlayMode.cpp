#include"Scene/SelectPlayMode.h"
#include "cocostudio/CocoStudio.h"
#include "Core/Controller/GameScene.h"
#include "Core/Controller/GameSceneOnline.h"
#include "Scene/BattleHistory.h"
#include"Scene/Rule.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;
extern bool isMusicEffect;
extern bool isSoundEffect;
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



	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (isMusicEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);
	}

	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}

	Sprite *bg = Sprite::create("selectmodebg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);


	//单机模式
	MenuItemImage*item1 = MenuItemImage::create("online.png", "online.png", CC_CALLBACK_1(SelectPlayMode::OnlineModeCallBack, this));
	item1->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.45);

	//联机模式
	MenuItemImage*item2 = MenuItemImage::create("single.png", "single.png", CC_CALLBACK_1(SelectPlayMode::SingleModeCallBack, this));
	item2->setPosition(origin.x + visibleSize.width * 0.75, origin.y + visibleSize.height * 0.45);

	MenuItemImage*item3 = MenuItemImage::create("rule.png", "rule.png", CC_CALLBACK_1(SelectPlayMode::RuleCallBack, this));
	item3->setPosition(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95);

	MenuItemImage*item4 = MenuItemImage::create("battlehistory.png", "battlehistory.png", CC_CALLBACK_1(SelectPlayMode::BattleHistory, this));
	item4->setPosition(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.85);
	//将菜单项放到菜单对象中
	Menu *mn = Menu::create(item1, item2, item3,item4, NULL);

	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	return true;

}


void  SelectPlayMode::SingleModeCallBack(Ref *pSender)
{
	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	auto scene = SelectHeroScene::createScene();
	scene->setTag(010);
	Director::getInstance()->pushScene(scene);
}
void  SelectPlayMode::OnlineModeCallBack(Ref *pSender)
{
	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	auto scene = SelectHeroScene::createScene();
	scene->setTag(020);
	Client::getInstance()->connectWithServer();
	Director::getInstance()->pushScene(scene);
}
void  SelectPlayMode::RuleCallBack(Ref *pSender)
{
	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	//auto scene = GameSceneOnline::createScene();
	auto scene = Rule::createScene();
	Director::getInstance()->pushScene(scene);
}
void  SelectPlayMode::BattleHistory(Ref *pSender)
{
	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}
	//auto scene = GameSceneOnline::createScene();
	auto scene = BattleHistory::createScene();
	Director::getInstance()->pushScene(scene);
}
void SelectPlayMode::onExit()
{
	Scene::onExit();
	log("MainMenu onExit");
}

void SelectPlayMode::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("MainMenu onExitTransitionDidStart");
}

void SelectPlayMode::cleanup()
{
	Scene::cleanup();
	log("MainMenu cleanup");
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/2.mp3");
}