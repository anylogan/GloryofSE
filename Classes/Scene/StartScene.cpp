#include"StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//#include"Scene/GameScene.h"
USING_NS_CC;
using namespace CocosDenshion;
extern bool isMusicEffect;
extern bool isSoundEffect;
Scene* StartScene::createScene()
{
	return StartScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	if (isMusicEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/1.mp3", true);
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto rootNode = CSLoader::createNode("MainScene.csb");
	auto StartGamebutton = static_cast<ui::Button*>(rootNode->getChildByName("StartGame"));
	StartGamebutton->addClickEventListener(CC_CALLBACK_1(StartScene::menuItemLoginCallback, this));
	auto Settingbutton = static_cast<ui::Button*>(rootNode->getChildByName("Setting"));
	Settingbutton->addClickEventListener(CC_CALLBACK_1(StartScene::menuItemSettingCallback, this));
	auto QuitGamebutton = static_cast<ui::Button*>(rootNode->getChildByName("QuitGame"));
	QuitGamebutton->addClickEventListener(CC_CALLBACK_1(StartScene::menuCloseCallback, this));
	//设置帮助菜单
	MenuItemImage*helpMenuItem = MenuItemImage::create("help.jpg", "help.jpg", CC_CALLBACK_1(StartScene::menuItemHelpCallback, this));
	helpMenuItem->setPosition(origin.x + visibleSize.width * 0.015, origin.y + visibleSize.height *0.97);
	//将菜单项放到菜单对象中
	Menu *mn = Menu::create(helpMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(rootNode);
	this->addChild(mn);
	return true;
}


void StartScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void StartScene::menuItemLoginCallback(Ref *pSender)
{
	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	}

	auto sc = LoginScene::createScene();
	Director::getInstance()->pushScene(sc);
}
//void StartScene::menuItemStartCallback(Ref *pSender)
//{
//	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
//	auto sc = GameScene::createScene();
//	Director::getInstance()->pushScene(sc);
//}

void StartScene::menuItemSettingCallback(cocos2d::Ref*pSender)
{
	auto sc = SettingScene::createScene();
	Director::getInstance()->pushScene(sc);
}

void StartScene::menuItemHelpCallback(cocos2d::Ref*pSender)
{
	auto sc = HelpScene::createScene();
	Director::getInstance()->pushScene(sc);
}
void StartScene::onEnter()
{
	Scene::onEnter();
	log("MainMenu onEnter");
}

void StartScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	log("MainMenu onEnterTransitionDidFinish");
	//播放
	//if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
	//	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);
	//}
}

void StartScene::onExit()
{
	Scene::onExit();
	log("MainMenu onExit");
}

void StartScene::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("MainMenu onExitTransitionDidStart");
}

void StartScene::cleanup()
{
	Scene::cleanup();
	log("MainMenu cleanup");
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/2.mp3");
}