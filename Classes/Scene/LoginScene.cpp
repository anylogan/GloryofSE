#include"Scene/LoginScene.h"
#include"ui/UIButton.h"
#include"cocos-ext.h"
using namespace CocosDenshion;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
Scene* LoginScene::createScene()
{
	return LoginScene::create();
}
bool LoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/music_logo.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ӱ���
	Sprite *bg = Sprite::create("loginground.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bg,0);


	usernameInput = EditBox::create(Size(300, 50), Scale9Sprite::create("inputbox.png"));
	usernameInput->setPlaceHolder("ID:");
	usernameInput->setColor(Color3B::BLUE);
	usernameInput->setMaxLength(7);
	usernameInput->setPosition(Vec2(origin.x+visibleSize.width*0.5, origin.y+visibleSize.height*0.3));
	usernameInput->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(usernameInput, 1);

	IPAddressInput = EditBox::create(Size(300, 50), Scale9Sprite::create("inputbox.png"));
	IPAddressInput->setPlaceHolder("IP:");
	IPAddressInput->setColor(Color3B::BLUE);
	IPAddressInput->setMaxLength(15);
	IPAddressInput->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height*0.2));
	IPAddressInput->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(IPAddressInput, 1);

	addLoginButton();
}
void LoginScene::addLoginButton()
{
	auto visiblesize = Director::getInstance()->getVisibleSize();

	auto loginButton = ui::Button::create("button_normal.png", "button_selected.png");
	loginButton->setTitleText("Login");
	loginButton->setTitleFontName("font/Marker Felt.ttf");
	loginButton->setTitleFontSize(40);
	loginButton->setPosition(Vec2(visiblesize.width / 2, visiblesize.height *0.1));

	//����¼�������
	loginButton->addTouchEventListener(CC_CALLBACK_1(LoginScene::menuItemStartCallback, this));

	this->addChild(loginButton);
}
//(CC_CALLBACK_1(StartScene::menuItemStartCallback, this));
void LoginScene::menuItemStartCallback(Ref *pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto sc = SelectPlayMode::createScene();
	Director::getInstance()->pushScene(sc);
}