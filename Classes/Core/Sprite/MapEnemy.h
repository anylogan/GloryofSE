#pragma once
#include"cocos2d.h"
USING_NS_CC;

class MapElement :public Sprite
{
private:
	ProgressTimer * blood;   //Ѫ��
	int bloodNum;  //Ѫ��
	Vec2 initPos;
	int deadRewardmoney;	//���������������
	int deadRewardExp;		//�����������������
	int attackMinusNum;		//ÿ�δ��˵ĵ�Ѫ��
	Rect* attack_rect;
	char* attackURL;
	char* runURL;
public:
	//void attackHero(float dt);
	void minusBlood(int num, Node* attacker);
	bool isAttacking;
	void scheduleAttack();
	void unscheduleAttack();
	MapElement(int _deadRewardmoney, int _deadRewardExp, int _bloodNum, int _attackMinusNum, char* _attackURL, char* _runURl);
};