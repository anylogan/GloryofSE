#include"Core/Controller/GameScene.h"
Scene* GameScene::createScene()

{

	auto controller =GameController::createScene();//创建控制层
	auto scene = Scene::create();//创造场景
	//controller->map = gamemap;  //将游戏控制类中的GameScene指针指向gamescene   注意两个类不能互相指
	scene->addChild(controller);
	return scene;
}
