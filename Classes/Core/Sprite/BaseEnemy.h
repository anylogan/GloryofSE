#pragma once
//������  �Ȳ�ʵ���ڻҶ�ս����  ֻ���ڻ����Ź̶���·���߿������˺�  ���Ҹ�Ӣ���ͽ�Ҿ���
#include"cocos2d.h"
#include"Core/Sprite/Progress.h"
#include"Core/Sprite/Hero.h"

USING_NS_CC;
class BaseEnemy : public Sprite
{
private:
	Progress * bloodBar;
	int bloodNum;  //Ѫ��
	Vec2 initPos;
	Vec2 attackTowerPos;
	int deadRewardmoney;	//���������������
	int deadRewardExp;		//�����������������
	int attackMinusNum;		//ÿ�δ��˵ĵ�Ѫ��

};