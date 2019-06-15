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
	Sprite *bg = Sprite::create("SelectHeroBackground.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);


	Vector<Text*>T;  //存放Text gui控件

	Text *text1 = Text::create(MyUtility::gbk_2_utf8("本游戏是一款MOBA类游戏"), "font/Marker Felt.ttf", 40);
	Text *text2 = Text::create(MyUtility::gbk_2_utf8("玩家通过鼠标点击移动英雄位置"), "font/Marker Felt.ttf", 40);
	Text *text3 = Text::create(MyUtility::gbk_2_utf8("W键释放技能小招"), "font/Marker Felt.ttf", 40);

	Text *text4 = Text::create(MyUtility::gbk_2_utf8("A键释放技能大招"), "font/Marker Felt.ttf", 40);
	Text *text5 = Text::create(MyUtility::gbk_2_utf8("玩家通过击杀敌方玩家和野怪获得金钱和经验"), "font/Marker Felt.ttf", 40);
	Text *text6 = Text::create(MyUtility::gbk_2_utf8("通过购买装备提升英雄能力"), "font/Marker Felt.ttf", 40);
	Text *text7 = Text::create(MyUtility::gbk_2_utf8("当一方摧毁另一方大本营防御塔时游戏结束，该方获得胜利，另一方失败"), "font/Marker Felt.ttf", 40);

	//放到容器中
	T.pushBack(text1);
	T.pushBack(text2);
	T.pushBack(text3);
	T.pushBack(text4);
	T.pushBack(text5);
	T.pushBack(text6);
	T.pushBack(text7);


	//设置文本颜色
	for (int i = 0; i < (T.size() - 1); i++)
	{
		T.at(i)->setColor(Color3B(5, 39, 175));  //设置颜色
		T.at(i)->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.8 - i * 0.05))));
		this->addChild(T.at(i));
	}


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