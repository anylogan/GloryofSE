#include "Scene/BattleHistory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"Scene/StartScene.h"

//#include"Scene/GameScene.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* BattleHistory::createScene()
{
	return BattleHistory::create();
}
bool BattleHistory::init()
{
	if (!Scene::init())
	{
		return false;
	}
	int success=0, failure=0, exp=0;
		success = UserDefault::getInstance()->getIntegerForKey("success");
		failure= UserDefault::getInstance()->getIntegerForKey("failure");
		exp= UserDefault::getInstance()->getIntegerForKey("exp");
	auto rootNode = CSLoader::createNode("BattleHistory.csb");
	//button->addClickEventListener(CC_CALLBACK_1(BattleHistory::BackToMain, this));

	auto successText = dynamic_cast<ui::Text*>(rootNode->getChildByName("success"));
	auto failureText = dynamic_cast<ui::Text*>(rootNode->getChildByName("failure"));
	auto expText = dynamic_cast<ui::Text*>(rootNode->getChildByName("exp"));
	auto levelText = dynamic_cast<ui::Text*>(rootNode->getChildByName("level "));
	auto backButton = dynamic_cast<ui::Button*>(rootNode->getChildByName("BackButton_0"));
	backButton->addClickEventListener(CC_CALLBACK_1(BattleHistory::BackToMain, this));

	successText->setText(std::to_string(success));
	failureText->setText(std::to_string(failure));
	expText->setText(std::to_string(exp));
	if (exp <= 200)
		levelText->setText("LV1");
	else if(exp<=500)
		levelText->setText("LV2");
	else levelText->setText("MAXLEVEL");
	addChild(rootNode);
	return true;

}
void BattleHistory::BackToMain(cocos2d::Ref*pSender) {
	Director::getInstance()->popScene();
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
}
