#pragma once

#include"cocos2d.h"

#include"Scene/SelectHeroScene.h"
//��������ͷ�ļ�
#include"Scene/ButtonLayer.h"

//����������ͷ�ļ�
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/EnemySoldier.h"
#include"Core/Sprite/CannonFodder .h"
#include"Core/Sprite/Tower.h"
#include"Core/Sprite/fieldMonster.h"
#include"Core/Sprite/EnemySoldier.h"

USING_NS_CC;
//ȫ�ֱ���
extern int playMoney;

class GameController : public Layer   //��Ϸ������
{
	
public:
//����
	//������
	ButtonLayer*button;
	//
	//����
	TMXTiledMap * _tileMap;
	TMXLayer * _collidable;
	Hero * hero1, *hero2;
	Vector<EnemySoldier*> clientSoldierVector;    //���EnemySoldier���������
	fieldMonster* monster1;
    fieldMonster* monster2;
	Vector<Tower*>TowerVector;				//�����ָ�������
	bool ismousedown;
	char *bigSkillFormat;    //����·��
	char *mediumSkillFormat;  //����·��
	char *smallSkillFormat;   //С��·��
	int bigSkillNum;    //���ж�������Ƭ��
	int mediumSkillNum;    //���ж�������Ƭ��
	int smallSkillNum;    //���ж�������Ƭ��
//����
	ValueMap player1_initPos;
	void setViewpointCenter(Vec2 position);
	Vec2 tileCoordFromPosition(Vec2 pos);
	 int getNowPointDir(Node* player, Vec2 newpoint);
	 int getAttackDir(int tempDir);
	void setPlayerPosition(Vec2 position);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	bool checkHit(int standDir, int monsterDir);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    static GameController* createScene(); //��������
	virtual bool init(); //��ʼ�����Ʋ�
	void mapElementsInit();
	int successPlayerID; //�ж�ʤ����ʱ������
	Vec2 lastCollidablePos;
	void onEnter();
	void clientPlayerAttack();
	void spriteRectCheck(float dt);
	//   ��дonEnter ����
	void onExit();   //��дonExit ����
	
	void collidableCheck();
	void createHero();
	void updateView(float dt);
	//hero_role HeroRole);  //����Ӣ��
	bool isHeroDeath();           //�ж�Ӣ���Ƿ�����
	void menuCloseCallback(cocos2d::Ref* pSender);
	GameController() {
		lastCollidablePos = Vec2(0, 0);
	}
	CREATE_FUNC(GameController);    

};