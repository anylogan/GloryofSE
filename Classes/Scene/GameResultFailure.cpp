#include "Scene/GameResultFailure.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"Scene/StartScene.h"

//#include"Scene/GameScene.h"
USING_NS_CC;
using namespace CocosDenshion;
int enterTime2 = 0;
extern int GameResult[4];

Scene* GameResultFailure::createScene()
{
	return GameResultFailure::create();
}
bool GameResultFailure::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("FailureResultScene.csb");
	//button->addClickEventListener(CC_CALLBACK_1(GameResultFailure::BackToMain, this));

	auto timeText = dynamic_cast<ui::Text*>(rootNode->getChildByName("TimeTextView"));
	auto ExpText = dynamic_cast<ui::Text*>(rootNode->getChildByName("ExpTextView"));
	auto KillCountText = dynamic_cast<ui::Text*>(rootNode->getChildByName("KillCountTextView"));
	auto MoneyText = dynamic_cast<ui::Text*>(rootNode->getChildByName("MoneyTextView"));

	std::string timeDisplay = std::to_string(GameResult[0]);
	timeText->setText(timeDisplay);
	std::string ExpDisplay = std::to_string(GameResult[1]);
	ExpText->setText(ExpDisplay);
	std::string killDisplay = std::to_string(GameResult[2]);
	KillCountText->setText(killDisplay);
	std::string MoneyDisplay = std::to_string(GameResult[3]);
	int bonusMoney = 200 - GameResult[0];
	if (bonusMoney < 0)
		bonusMoney = 0;
	MoneyText->setText(MoneyDisplay + "+"+ std::to_string(bonusMoney));
	int success, failure, exp;


		success = UserDefault::getInstance()->getIntegerForKey("success");
		failure = UserDefault::getInstance()->getIntegerForKey("failure");
		exp = UserDefault::getInstance()->getIntegerForKey("exp");
		UserDefault::getInstance()->setIntegerForKey("success",success);
		UserDefault::getInstance()->setIntegerForKey("failure", failure+1);
		UserDefault::getInstance()->setIntegerForKey("exp", exp+GameResult[1]);
		UserDefault::getInstance()->flush();

	
	addChild(rootNode);
	this->schedule(schedule_selector(GameResultFailure::BackToMain), 1.0f);
	return true;

}
void GameResultFailure::BackToMain(float dt) {
	enterTime2++;
	if (enterTime2 >= 10) {
		this->unscheduleAllSelectors();
		auto sc = StartScene::createScene();
		Director::getInstance()->replaceScene(sc);
	}
}
