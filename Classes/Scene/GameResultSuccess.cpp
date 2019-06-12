#include "Scene/GameResultSuccess.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"Scene/StartScene.h"

//#include"Scene/GameScene.h"
USING_NS_CC;
using namespace CocosDenshion;

extern int GameResult[4];
int enterTime = 0;
Scene* GameResultSuccess::createScene()
{
	return GameResultSuccess::create();
}
bool GameResultSuccess::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("SuccessResultScene.csb");
	auto button = static_cast<ui::Button*>(rootNode->getChildByName("BackButton"));
	//button->addClickEventListener(CC_CALLBACK_1(GameResultSuccess::BackToMain, this));

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
	MoneyText->setText(MoneyDisplay +"+"+std::to_string(bonusMoney));
	addChild(rootNode);
	this->schedule(schedule_selector(GameResultSuccess::BackToMain), 1.0f);
	return true;

}
void GameResultSuccess::BackToMain(float dt) {
	enterTime++;
	if (enterTime >= 10) {
		this->unscheduleAllSelectors();

		auto sc = StartScene::createScene();
		Director::getInstance()->replaceScene(sc);
	}
}

void GameResultSuccess::onExit()
{
	Scene::onExit();
	log("MainMenu onExit");
}

void GameResultSuccess::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("MainMenu onExitTransitionDidStart");
}

void GameResultSuccess::cleanup()
{
	Scene::cleanup();
	log("MainMenu cleanup");
	//ֹͣ
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/2.mp3");
}