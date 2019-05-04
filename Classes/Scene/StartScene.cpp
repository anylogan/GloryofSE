#include"StartScene.h"
//#include"Scene/GameScene.h"
USING_NS_CC;
using namespace CocosDenshion;
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
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Lose1.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	Sprite *bg = Sprite::create("bg.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//添加菜单
	/*MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);*/

	
	//设置开始和设置菜单
	MenuItemImage*startMenuItem = MenuItemImage::create("startbutton.png", "startbutton2.png", CC_CALLBACK_1(StartScene::menuItemLoginCallback, this));
	MenuItemImage*settingMenuItem = MenuItemImage::create("setbutton.png", "setbutton2.png", CC_CALLBACK_1(StartScene::menuItemSettingCallback, this));
	
	//设置帮助菜单
	MenuItemImage*helpMenuItem = MenuItemImage::create("help.jpg", "help.jpg", CC_CALLBACK_1(StartScene::menuItemHelpCallback, this));
	startMenuItem->setPosition(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.2);//(Director::getInstance()->convertToGL(Vec2(570, 230)));
	//startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(960, 780)));
	settingMenuItem->setPosition(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.1);//(Director::getInstance()->convertToGL(Vec2(570, 320)));
	helpMenuItem->setPosition(origin.x + visibleSize.width * 0.015, origin.y + visibleSize.height *0.97);
	
	//将菜单项放到菜单对象中
	Menu *mn = Menu::create(startMenuItem,settingMenuItem,helpMenuItem,NULL);
	mn->setPosition(Vec2::ZERO);
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
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
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
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}
void StartScene::menuItemHelpCallback(cocos2d::Ref*pSender)
{
	auto sc = HelpScene::createScene();
	Director::getInstance()->pushScene(sc);
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");

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
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/Lose.mp3");
}