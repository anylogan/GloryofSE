#include"Scene/Rule.h"
USING_NS_CC;

Rule* Rule::createScene()
{
	return Rule::create();
}

// Print useful error message instead of segfaulting when files are not there.

// on "init" you need to initialize your instance
bool Rule::init()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	Sprite *bg = Sprite::create("RuleBackground.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//Back菜单
	MenuItemImage*backMenuItem = MenuItemImage::create("quit01.png", "quit02.png", CC_CALLBACK_1(Rule::menuItemGoBackCallback, this));
	backMenuItem->setPosition(origin.x + visibleSize.width * 0.9, origin.y + visibleSize.height * 0.1);
	//将菜单项放到菜单对象中
	Menu *mn = Menu::create(backMenuItem, NULL);

	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	return true;
}


void Rule::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


void Rule::menuItemGoBackCallback(cocos2d::Ref*pSender)
{
	Director::getInstance()->popScene();
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}
void Rule::onExit()
{
	Scene::onExit();
	log("MainMenu onExit");
}

void Rule::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("MainMenu onExitTransitionDidStart");
}

void Rule::cleanup()
{
	Scene::cleanup();
	log("MainMenu cleanup");
	//停止
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/2.mp3");
}