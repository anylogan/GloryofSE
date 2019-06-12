#pragma once
#include"cocos2d.h"
#include"Core/Sprite/Hero.h"
#include"Core/Sprite/Progress.h"

USING_NS_CC;
class fieldMonster : public Sprite
{
public:
	Progress * blood;   //Ѫ��
	int bloodNum;  //Ѫ��
	Sprite* image;
	//void attack();
	Vec2 initPos;
	int deadRewardmoney;	//���������������
	int deadRewardExp;		//�����������������
	int attackMinusNum;		//ÿ�δ��˵�
	virtual bool init();   //  Ұ���ܵĿ���
	Rect* attack_rect;
	void initBloodBar();
	void initMonsterAttr(int attackAbility, int _bloodNum, int _rewardMoney, int _rewardExp);//�������ʼ����������
	bool checkHeroInRect(Hero* hero1,Hero* hero2);
	void attackHero(float dt);
	void minusBlood(int num,Hero* hero);
	Hero* heroInRect;
	bool isAttacking;
	void scheduleAttack();
	void unscheduleAttack();
};