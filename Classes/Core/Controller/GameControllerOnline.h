//#pragma once
//
//#include"cocos2d.h"
//#include <vector>
//#include"Scene/SelectHeroScene.h"
////��������ͷ�ļ�
//#include"Scene/ButtonLayer.h"
////����������ͷ�ļ�
//#include"Core/Sprite/Hero.h"
//#include"Core/Sprite/EnemySoldier.h"
//#include"Core/Sprite/Tower.h"
//#include"Core/Sprite/fieldMonster.h"
//
//USING_NS_CC;
////ȫ�ֱ���
////extern int playMoney;
//class GameControllerOnline : public Layer   //��Ϸ������
//{
//
//public:
//	//����
//	//������
//	ButtonLayer * button;
//	//
//	//����
//	TMXTiledMap * _tileMap;
//	TMXLayer * _collidable;
//	Hero * hero1, *hero2;
//	std::vector<EnemySoldier*> clientSoldierVector;    //���EnemySoldier���������
//	fieldMonster* monster1;
//	fieldMonster* monster2;
//	std::vector<Tower*>TowerVector;				//�����ָ�������
//						  //����
//	ValueMap player1_initPos;
//	void setViewpointCenter(Vec2 position);
//	Vec2 tileCoordFromPosition(Vec2 pos);
//	int getNowPointDir(Node* player, Vec2 newpoint);
//	int getAttackDir(int tempDir);
//	void setPlayerPosition(Vec2 position);
//	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
//	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
//	bool checkHit(int standDir, int monsterDir);
//	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//	static GameControllerOnline* createScene(); //��������
//	virtual bool init(); //��ʼ�����Ʋ�
//	void mapElementsInit();
//	int successPlayerID; //�ж�ʤ����ʱ������
//	Vec2 lastCollidablePos;
//	void onEnter();
//	void clientPlayerAttack();
//	void serverPlayerAttack();
//	void AI_Hero_Attack(float dt);
//	void spriteRectCheck(float dt);
//	//   ��дonEnter ����
//	void onExit();   //��дonExit ����
//	void collidableCheck();
//	void createHero();
//	void updateView(float dt);
//	void AI_Hero_Run(float dt);
//	//hero_role HeroRole);  //����Ӣ��
//	bool isHeroDeath();           //�ж�Ӣ���Ƿ�����
//	void menuCloseCallback(cocos2d::Ref* pSender);
//	CREATE_FUNC(GameControllerOnline);
//
//};