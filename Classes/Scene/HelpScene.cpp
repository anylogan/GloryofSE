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

	//��ӱ���
	Sprite *bg = Sprite::create("helpground1.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);
	

	Vector<Text*>T;  //���Text gui�ؼ�

	Text *text1 = Text::create(MyUtility ::gbk_2_utf8("�����������۴�Խ�ޱߵ�����,�������ߴ�½��"), "font/Marker Felt.ttf", 40);
	Text *text2 = Text::create(MyUtility::gbk_2_utf8("������������ǿ��������������ۺ��ģ���������ЩΪ����֪��Ӣ�ۡ�"), "font/Marker Felt.ttf", 40);
	Text *text3 = Text::create(MyUtility::gbk_2_utf8("�������ۺ��ģ�ʮ�����漣�εض�����ʾ���Ǹ�ʱ�����ٹ⡣"), "font/Marker Felt.ttf", 40);
	
	Text *text4 = Text::create(MyUtility::gbk_2_utf8("Ȼ�����ϵ�����������������������ս����"),"font/Marker Felt.ttf", 40);
	Text *text5 = Text::create(MyUtility::gbk_2_utf8("��ҹ���ִ�½���漣�Ĺ�â����ӳ��"), "font/Marker Felt.ttf", 40);
	Text *text6 = Text::create(MyUtility::gbk_2_utf8("Ϊ�˷�ֹս���ٴν��٣����������ۺ��ķ�ӡ�ڳ�������֮��"), "font/Marker Felt.ttf", 40);
	Text *text7 = Text::create(MyUtility::gbk_2_utf8("�������صİ�ʾ������ⷽ�ۺ��ĵ��������̲���ʮ���漣֮�С�"), "font/Marker Felt.ttf", 40);
	
	Text *text8 = Text::create(MyUtility::gbk_2_utf8("����֮������ŷ��ۺ��ġ�����һ�ܹ������ػ������ľ���������"), "font/Marker Felt.ttf", 40);
	Text *text9 = Text::create(MyUtility::gbk_2_utf8("Ϊ���ػ����ߴ�½�ĺ�ƽ��Ӣ����̤�Ͻ�ⷽ�ۺ��ĵĵ�·��"), "font/Marker Felt.ttf", 40);
	Text *text10 = Text::create(MyUtility::gbk_2_utf8("������߻���ǰ·���Ʊ�ã����ֵ��������ǵĽŲ���"), "font/Marker Felt.ttf", 40);
	Text *text11 = Text::create(MyUtility::gbk_2_utf8("�����ɣ�Ӣ���ǣ�"), "font/Marker Felt.ttf",70);
	//�ŵ�������
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


	//�����ı���ɫ
	for(int i=0;i<(T.size()-1);i++)
	{ 
		T.at(i)->setColor(Color3B(5,39,175));  //������ɫ
		T.at(i)->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.8 - i * 0.05))));
		this->addChild(T.at(i));
	}
	text11->setColor(Color3B(128, 0, 128));  //������ɫ
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


	//Back�˵�
	MenuItemImage*backMenuItem = MenuItemImage::create("backbutton.png", "backbutton2.png", CC_CALLBACK_1(HelpScene::menuItemGoBackCallback, this));
	backMenuItem->setPosition(origin.x + visibleSize.width * 0.9, origin.y + visibleSize.height * 0.1);
	//���˵���ŵ��˵�������
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