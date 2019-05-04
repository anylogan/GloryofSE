//#pragma once
//#include"cocos2d.h"
//#include"Core/Sprite/Hero.h"
//#include"Core/Sprite/Buff.h"
//#include"Core/Sprite/CannonFodder .h"
//
//#include<assert.h>
//USING_NS_CC;
//typedef enum
//{
//	Hero = 0,  //英雄
//	Buff=1,    //野怪
//	CannonFodder=2 //炮灰
//	
//}sprite_type;   //精灵类型
//
//class CreateSprite :public Sprite
//{
//private:
//	int blood;   //血量
//
//public:
//	//static cocos2d::Sprite* createScene();
//	CreateSprite*CreateSpriteTpye(sprite_type s_type)   //
//	{
//		switch (s_type)
//		{
//			case Hero:
//				{
//				auto sprite=Hero::create();
//				break;
//				}
//			case Buff:
//				{
//				auto sprite =Buff::create();
//				break;
//
//				}
//			case CannonFodder:
//				{
//				auto sprite = CannonFodder::create();
//				break;
//
//				}
//		}
//
//
//
//	}
//
//};
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//class daji :public Hero
//{
//public:
//	static cocos2d::Sprite* createScene();
//	virtual bool init();   //  英雄的总的控制
//	virtual bool createHero();  //创建英雄的函数，每个英雄在创建的时候必须重写
//
//
//	CREATE_FUNC(Hero);
//
//};
//
//
//
//Sprite* daji::createScene()
//{
//	return daji::create();
//}