#include"Core/Controller/GameController.h"
#define hero_daji "hero/daji.png"
#define hero_houyi "hero/houyi.jpg"
#define hero_yase "hero/yase.jpg"

#define daji_big_skill "skills\role_skill\ziqidonglai%d.png"
#define daji_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define daji_small_skill "skills\role_skill\ziqidonglai%d.png"

#define yase_big_skill "skills\role_skill\ziqidonglai%d.png"
#define yase_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define yase_small_skill "skills\role_skill\ziqidonglai%d.png"


#define houyi_big_skill "skills\role_skill\ziqidonglai%d.png"
#define houyi_medium_skill "skills\role_skill\ziqidonglai%d.png"
#define houyi_small_skill "skills\role_skill\ziqidonglai%d.png"

#define daji_big_skill_num 13
#define daji_medium_skill_num 13
#define daji_small_skill_num 13


#define houyi_big_skill_num 13
#define houyi_medium_skill_num 13
#define houyi_small_skill_num 13


#define yase_big_skill_num 13
#define yase_medium_skill_num 13
#define yase_small_skill_num 13


#define map1_buff_num 8
USING_NS_CC;
extern hero_role HeroRole;
GameController* GameController::createScene()
{
	return (GameController*)GameController::create();
}
void GameController::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

bool GameController::init()
{
	//创建地图
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_tileMap = TMXTiledMap::create("map/map.tmx");
	addChild(_tileMap, 0, 100);

	//设置英雄的位置
	createHero();


	createBuff();  //创建Buff

				   //创建CannonFodder     简单起见  实现隔一段时间创建一队炮灰让他们沿着固定路径前进  

	createCannonFodder();  //创建炮灰


	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->schedule(schedule_selector(GameController::updateGame), 0.2f);
	return true;
	
}

void GameController::onEnter()  //  主要用来注册键盘和鼠标事件监听器
{

	Layer::onEnter();

	//注册事件监听器  根据鼠标走的位置移动英雄
	auto moveHeroListener = EventListenerMouse::create();
	moveHeroListener->onMouseDown = [this](Event *e)
	{
		EventMouse* em = (EventMouse*)e;
		mouse_down = em->getLocation();
		mouse_down = Director::getInstance()->convertToGL(mouse_down);
		ismousedown = true;
		//mouse_down = location+repair;
	};
	moveHeroListener->onMouseUp = [this](Event *e)
	{
		EventMouse* em = (EventMouse*)e;

		if (ismousedown)
		{
			auto heroPostion = hero1->getPosition();
			heroPostion = Director::getInstance()->convertToGL(heroPostion);
			auto move = mouse_down - heroPostion;
			//需要加一个瞬时动作让精灵朝向运动方向
			Action*moveaction = hero1->runAction(MoveBy::create(10,move));
			moveaction->setTag(1);
		}
		ismousedown = false;

	};

	////注册事件监听器  监听键盘  hero可以释放技能
	auto releaseSkillListener = EventListenerKeyboard::create();
	releaseSkillListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)    //放大招 
		{
			hero1->attackTrick(bigSkillFormat, bigSkillNum);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)    //放中招 
		{
			hero1->attackTrick(mediumSkillFormat, mediumSkillNum);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)    //放小招 
		{
			hero1->attackTrick(smallSkillFormat,smallSkillNum);
		}

	};
	releaseSkillListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(moveHeroListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(releaseSkillListener, this);

}

void GameController::createHero()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	switch (HeroRole)       //创建英雄
	{
	case daji:
	{
		hero1 = (Hero*)Hero::create(hero_daji);
		bigSkillFormat = daji_big_skill;
		mediumSkillFormat = daji_medium_skill;
		smallSkillFormat = daji_small_skill;

		bigSkillNum = daji_big_skill_num;
		mediumSkillNum= daji_medium_skill_num;   
		smallSkillNum= daji_small_skill_num;   
		break;
	}
	case yase:
	{
		hero1 = (Hero*)Hero::create(hero_yase);
		bigSkillFormat = yase_big_skill;
		mediumSkillFormat = yase_medium_skill;
		smallSkillFormat = yase_small_skill;

		bigSkillNum = yase_big_skill_num;
		mediumSkillNum = yase_medium_skill_num;
		smallSkillNum = yase_small_skill_num;
		break;
	}
	case houyi:
	{
		hero1 = (Hero*)Hero::create(hero_houyi);
		bigSkillFormat = houyi_big_skill;
		mediumSkillFormat = houyi_medium_skill;
		smallSkillFormat = houyi_small_skill;

		bigSkillNum = houyi_big_skill_num;
		mediumSkillNum = houyi_medium_skill_num;
		smallSkillNum = houyi_small_skill_num;
		break;
	}
	default:break;
	}
	hero1->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
	this->addChild(hero1);
}

void GameController::createBuff()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < map1_buff_num; i++)
	{
		Buff *buff = new Buff();// ("npc/buff1.png");
		buff->initWithFile("npc/buff1.png");
		buff->setPosition(Vec2(origin.x + visibleSize.width * (0.1*i), origin.y + visibleSize.height * 0.2));// 设置野怪的位置  让它在初始位置生成
		this->addChild(buff);    //加到层中
		BuffVector.pushBack(buff);   //加到容器中
	}
}

void GameController::createCannonFodder() //创建炮灰
{




}

void GameController::createTower()    //创建塔
{

}


void  GameController::updateGame(float dt)  //刷新函数
{
	CannonFodderMoving();  //让炮灰走几步   
	if (isHeroDeath())
	{
		//进入阵亡界面
	}
	if (isGameOver())
	{
		//进入战绩界面
	}
	if (isCannonFodderDeath())
	{
		//把炮灰从容器中移除
	}


}

void GameController::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}





void GameController::CannonFodderMoving()
{

}
void GameController::backHome()  //回城
{




}

bool GameController::isHeroDeath()          //判断英雄是否死亡
{
	if (hero1->bloodnum < 0)
		return true;
	else
		return false;
}
bool GameController::isGameOver()       //判断游戏是否结束
{
	//判断大本营的塔是否被推
	//建出来再说
	return true;
}
bool GameController::isCannonFodderDeath()//判断炮灰是否死亡
{
	return true;
}
bool GameController::isBuffDeath()//判断Buff是否死亡
{
	return true;
}
bool GameController::isHeroResurrection()//英雄复活函数
{
	return true;
}
bool GameController::isTowerPushed()   //判断塔是否被推
{
	return true;
}



