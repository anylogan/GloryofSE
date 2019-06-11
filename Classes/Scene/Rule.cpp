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

	//��ӱ���
	Sprite *bg = Sprite::create("SelectHeroBackground.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg);


	Vector<Text*>T;  //���Text gui�ؼ�

	Text *text1 = Text::create(MyUtility::gbk_2_utf8("����Ϸ��һ��MOBA����Ϸ"), "font/Marker Felt.ttf", 40);
	Text *text2 = Text::create(MyUtility::gbk_2_utf8("���ͨ��������ƶ�Ӣ��λ��"), "font/Marker Felt.ttf", 40);
	Text *text3 = Text::create(MyUtility::gbk_2_utf8("W���ͷż���С��"), "font/Marker Felt.ttf", 40);

	Text *text4 = Text::create(MyUtility::gbk_2_utf8("A���ͷż��ܴ���"), "font/Marker Felt.ttf", 40);
	Text *text5 = Text::create(MyUtility::gbk_2_utf8("���ͨ����ɱ�з���Һ�Ұ�ֻ�ý�Ǯ�;���"), "font/Marker Felt.ttf", 40);
	Text *text6 = Text::create(MyUtility::gbk_2_utf8("ͨ������װ������Ӣ������"), "font/Marker Felt.ttf", 40);
	Text *text7 = Text::create(MyUtility::gbk_2_utf8("��һ���ݻ���һ����Ӫ������ʱ��Ϸ�������÷����ʤ������һ��ʧ��"), "font/Marker Felt.ttf", 40);

	//�ŵ�������
	T.pushBack(text1);
	T.pushBack(text2);
	T.pushBack(text3);
	T.pushBack(text4);
	T.pushBack(text5);
	T.pushBack(text6);
	T.pushBack(text7);


	//�����ı���ɫ
	for (int i = 0; i < (T.size() - 1); i++)
	{
		T.at(i)->setColor(Color3B(5, 39, 175));  //������ɫ
		T.at(i)->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + (visibleSize.height * (0.8 - i * 0.05))));
		this->addChild(T.at(i));
	}


	//Back�˵�
	MenuItemImage*backMenuItem = MenuItemImage::create("quit01.png", "quit02.png", CC_CALLBACK_1(Rule::menuItemGoBackCallback, this));
	backMenuItem->setPosition(origin.x + visibleSize.width * 0.9, origin.y + visibleSize.height * 0.1);
	//���˵���ŵ��˵�������
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
	//ֹͣ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/2.mp3");
}