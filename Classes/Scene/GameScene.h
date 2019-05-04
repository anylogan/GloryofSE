//在游戏中加载地图
#include"cocos2d.h"
#include"Scene/GameMap.h"
USING_NS_CC;
//游戏场景类
//在游戏场景中加载游戏地图
class GameScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};
