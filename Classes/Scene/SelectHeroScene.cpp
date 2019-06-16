#include"Scene/SelectHeroScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;
hero_role HeroRole; //定义三个全局变量  并且初始化
hero_role EnemyHero;
int PlayMode; //左上or右下
extern bool isMusicEffect;
extern bool isSoundEffect;
Scene*  SelectHeroScene::createScene()
{
	return  SelectHeroScene::create();
}

bool  SelectHeroScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	if (isMusicEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/2.mp3", true);
	}

	if (isSoundEffect == false)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	int exp;

	
		exp = UserDefault::getInstance()->getIntegerForKey("exp");
	

	auto rootNode = CSLoader::createNode("SelectHeroScene.csb");
	auto ChangEbutton = static_cast<ui::Button*>(rootNode->getChildByName("CreateChange"));
	ChangEbutton->addClickEventListener(CC_CALLBACK_1(SelectHeroScene::ChangeCallBack, this));
	auto HuaMuLanbutton = static_cast<ui::Button*>(rootNode->getChildByName("CreateHuamulan"));
	HuaMuLanbutton->addClickEventListener(CC_CALLBACK_1(SelectHeroScene::HuamulanCallBack, this));
	auto SunWuKongbutton = static_cast<ui::Button*>(rootNode->getChildByName("CreateSunwukong"));
	SunWuKongbutton->addClickEventListener(CC_CALLBACK_1(SelectHeroScene::SunCallBack, this));
	if (exp <= 200) {
		HuaMuLanbutton->setEnabled(false);
		SunWuKongbutton->setEnabled(false);
	}else if(exp<=500)
		SunWuKongbutton->setEnabled(false);

	addChild(rootNode);
	
	return true;

}


void  SelectHeroScene::ChangeCallBack(Ref *pSender)
{
	int mode_tag = this->getTag();
	if (mode_tag == 020)
	{
		bool check_connect = Client::getInstance()->checkConnect();
		if (check_connect)
		{
			HeroRole = ChangE;   //给全局变量赋值
			Client::getInstance()->sendOwnHero(0);
			command hero_command = (Client::getInstance()->receiveHero());
			switch (hero_command.hero_type)
			{
			case 0:
			{
				EnemyHero = ChangE;
				break;
			}
			case 1:
			{
				EnemyHero = HuaMulan;
				break;
			}
			case 2:
			{
				EnemyHero = SunWukong;
				break;
			}
			default:
				break;
			}
			PlayMode = hero_command.player_type;
			if (isSoundEffect == false)
			{
				SimpleAudioEngine::getInstance()->stopAllEffects();
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			}
			auto scene = GameSceneOnline::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}
	else
	{
		HeroRole = ChangE;   //给全局变量赋值
		if (isSoundEffect == false)
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}
		else
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}
void  SelectHeroScene::HuamulanCallBack(Ref *pSender)
{
	int mode_tag = this->getTag();
	if (mode_tag == 020)
	{
		bool check_connect = Client::getInstance()->checkConnect();
		if (check_connect)
		{
			HeroRole = HuaMulan;   //给全局变量赋值
			Client::getInstance()->sendOwnHero(1);
			command hero_command=(Client::getInstance()->receiveHero());
			switch (hero_command.hero_type)
			{
			case 0:
			{
				EnemyHero = ChangE;
				break;
			}
			case 1:
			{
				EnemyHero = HuaMulan;
				break;
			}
			case 2:
			{
				EnemyHero = SunWukong;
				break;
			}
			default:
				break;
			}
			PlayMode = hero_command.player_type;
			if (isSoundEffect == false)
			{
				SimpleAudioEngine::getInstance()->stopAllEffects();
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			}
			auto scene = GameSceneOnline::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}
	else
	{
		HeroRole = HuaMulan;   //给全局变量赋值
		if (isSoundEffect == false)
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}
		else
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}
void  SelectHeroScene::SunCallBack(Ref *pSender)
{
	int mode_tag = this->getTag();
	if (mode_tag == 020)
	{
		bool check_connect = Client::getInstance()->checkConnect();
		if (check_connect)
		{
			HeroRole = SunWukong;   //给全局变量赋值
			Client::getInstance()->sendOwnHero(2);
			command hero_command = (Client::getInstance()->receiveHero());
			switch (hero_command.hero_type)
			{
			case 0:
			{
				EnemyHero = ChangE;
				break;
			}
			case 1:
			{
				EnemyHero = HuaMulan;
				break;
			}
			case 2:
			{
				EnemyHero = SunWukong;
				break;
			}
			default:
				break;
			}
			PlayMode = hero_command.player_type;
			if (isSoundEffect == false)
			{
				SimpleAudioEngine::getInstance()->stopAllEffects();
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
			}
			auto scene = GameSceneOnline::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}
	else
	{
		HeroRole = SunWukong;   //给全局变量赋值
		if (isSoundEffect == false)
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}
		else
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
		}
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}