#include"Scene/SettingScene.h"
USING_NS_CC;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	Sprite *bg = Sprite::create("settingground.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
	//
	//设置音效和背景音控件
	Text *sound = Text::create("sound", "font/Marker Felt.ttf", 40);
	//设置文本颜色
	sound->setColor(Color3B(191, 42, 42));
	sound->setPosition(Vec2(origin.x + visibleSize.width * 0.65, origin.y + visibleSize.height * 0.63));
	this->addChild(sound);

	Text *music = Text::create("music", "font/Marker Felt.ttf",40);
	//设置文本颜色
	music->setColor(Color3B(191, 42, 42));
	music->setPosition(Vec2(origin.x + visibleSize.width * 0.65, origin.y + visibleSize.height * 0.56));
	this->addChild(music);

	/*MenuItemFont*soundMenuItem = MenuItemFont::create("sound", CC_CALLBACK_1(StartScene::menuItemStartCallback, this));
	MenuItemFont*musicMenuItem = MenuItemFont::create("music", CC_CALLBACK_1(StartScene::menuItemSettingCallback, this));*/

	//
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuSoundToggleCallback, this),
		MenuItemImage::create("onbutton.png", "onbutton.png"),
		MenuItemImage::create("offbutton.png", "offbutton.png"),
		NULL);

	soundToggleMenuItem->setPosition(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.56);//(Director::getInstance()->convertToGL(Vec2(710,279 )));

																											   //音乐
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::menuMusicToggleCallback, this),
		MenuItemImage::create("onbutton.png", "onbutton.png"),
		MenuItemImage::create("offbutton.png", "offbutton.png"),
		NULL);
	musicToggleMenuItem->setPosition(origin.x + visibleSize.width * 0.7, origin.y + visibleSize.height * 0.63);
	
	//OK菜单
	MenuItemImage*okMenuItem = MenuItemImage::create("okbutton.png", "okbutton2.png", CC_CALLBACK_1(SettingScene::menuItemOKCallback, this));
	okMenuItem->setPosition(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.1);
	//将菜单项放到菜单对象中
	Menu *mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem,okMenuItem,NULL);
	
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	return true;
}


void SettingScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void SettingScene::menuSoundToggleCallback(Ref *pSender)
{
	MenuItem *item = (MenuItem*)pSender;
	log("Touch 音效 Menu Item %p", item);
}
void SettingScene::menuMusicToggleCallback(Ref *pSender)
{
	MenuItem *item = (MenuItem*)pSender;
	log("Touch 背景音 Menu Item %p", item);
}
void SettingScene::menuItemOKCallback(cocos2d::Ref*pSender)
{
	Director::getInstance()->popScene();
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}


//void SettingScene::menuSoundCallback(cocos2d::Ref*pSender)
//{
//}
//void SettingScene::menuMusicCallback(cocos2d::Ref*pSender)
//{
//
//}