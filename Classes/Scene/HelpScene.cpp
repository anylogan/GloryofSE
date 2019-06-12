#include"Scene/HelpScene.h"
USING_NS_CC;

Scene* HelpScene::createScene()
{
	return HelpScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	Sprite *bg = Sprite::create("helpground1.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
	

	Vector<Text*>T;  //存放Text gui控件

	Text *text1 = Text::create(MyUtility ::gbk_2_utf8("神明乘坐方舟穿越无边的宇宙,降临王者大陆。"), "font/Marker Felt.ttf", 40);
	Text *text2 = Text::create(MyUtility::gbk_2_utf8("他们用宇宙最强大的力量——方舟核心，创造了那些为人熟知的英雄。"), "font/Marker Felt.ttf", 40);
	Text *text3 = Text::create(MyUtility::gbk_2_utf8("依靠方舟核心，十二座奇迹拔地而起，昭示着那个时代的荣光。"), "font/Marker Felt.ttf", 40);
	
	Text *text4 = Text::create(MyUtility::gbk_2_utf8("然而无上的力量滋生欲望，欲望带来战争。"),"font/Marker Felt.ttf", 40);
	Text *text5 = Text::create(MyUtility::gbk_2_utf8("暗夜笼罩大陆，奇迹的光芒被掩映。"), "font/Marker Felt.ttf", 40);
	Text *text6 = Text::create(MyUtility::gbk_2_utf8("为了防止战争再次降临，神明将方舟核心封印在长安大门之后。"), "font/Marker Felt.ttf", 40);
	Text *text7 = Text::create(MyUtility::gbk_2_utf8("留下隐秘的暗示——解封方舟核心的线索，蕴藏在十二奇迹之中。"), "font/Marker Felt.ttf", 40);
	
	Text *text8 = Text::create(MyUtility::gbk_2_utf8("堕世之神窥伺着方舟核心——这一能够让他重获新生的绝世力量。"), "font/Marker Felt.ttf", 40);
	Text *text9 = Text::create(MyUtility::gbk_2_utf8("为了守护王者大陆的和平，英雄们踏上解封方舟核心的道路。"), "font/Marker Felt.ttf", 40);
	Text *text10 = Text::create(MyUtility::gbk_2_utf8("生存或者毁灭，前路风云变幻，但抵挡不了他们的脚步。"), "font/Marker Felt.ttf", 40);
	Text *text11 = Text::create(MyUtility::gbk_2_utf8("出征吧，英雄们！"), "font/Marker Felt.ttf",70);
	//放到容器中
	T.pushBack(text1);
	T.pushBack(text2);
	T.pushBack(text3);
	T.pushBack(text4);
	T.pushBack(text5);
	T.pushBack(text6);
	T.pushBack(text7);
	T.pushBack(text8);
	T.pushBack(text9);
	T.pushBack(text10);


	//设置文本颜色
	for(int i=0;i<(T.size()-1);i++)
	{ 
		T.at(i)->setColor(Color3B(5,39,175));  //设置颜色
		T.at(i)->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.8 - i * 0.05))));
		this->addChild(T.at(i));
	}
	text11->setColor(Color3B(128, 0, 128));  //设置颜色
	text11->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height *0.2));
	this->addChild(text11);

	//text1->setColor(Color3B(192,192,192));
	//text2->setColor(Color3B(192, 192, 192));
	//text3->setColor(Color3B(192, 192, 192));
	//
	//text1->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.8));
	//text2->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.77));
	//text3->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.74));
	//this->addChild(text1);
	//this->addChild(text2);
	//this->addChild(text3);


	//Back菜单
	MenuItemImage*backMenuItem = MenuItemImage::create("backbutton.png", "backbutton2.png", CC_CALLBACK_1(HelpScene::menuItemGoBackCallback, this));
	backMenuItem->setPosition(origin.x + visibleSize.width * 0.9, origin.y + visibleSize.height * 0.1);
	//将菜单项放到菜单对象中
	Menu *mn = Menu::create(backMenuItem, NULL);

	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	return true;
}


void HelpScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


void HelpScene::menuItemGoBackCallback(cocos2d::Ref*pSender)
{
	Director::getInstance()->popScene();
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}