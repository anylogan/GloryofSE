#pragma once

#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Scene/StartScene.h"
//#include"Scene/GameScene.h"
#include"Scene/SelectHeroScene.h"
USING_NS_CC;

class LoginScene :public cocos2d::Scene
{
private:
	cocos2d::ui::EditBox *usernameInput, *IPAddressInput;
	void addLoginButton();
public:
	LoginScene()
	{}
	~LoginScene() {}
	static cocos2d::Scene* createScene();
	void menuItemStartCallback(Ref *pSender);
	CREATE_FUNC(LoginScene);
	bool init();

};