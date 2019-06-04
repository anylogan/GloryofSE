#pragma once
//http://www.87g.com/zixun/16123.html    һ������   ������ҫӢ��ͼ

//��SelectHero�����л���ѡ��Ӣ�۵Ľ��棬   �û����ĳ��Ӣ�ۣ�ͨ��һ���ص�����������һ��hero_role������
//Ȼ���������������ж�   ���ݲ�ͬ�������Ӣ��
#include"cocos2d.h"
#include<vector>
#include"Core/Sprite/Progress.h"
#include"Scene/GlobalDefine.h"


using namespace std;
USING_NS_CC;
class Tower;
class EnemySoldier;

enum {
	up = 6,
	down = 4,
	lefts = 5,//
	rigth = 7,//
	rigth_up = 3,//
	rigth_down = 0,//
	left_down = 1,//
	left_up = 2//
};

class Hero:public Sprite
{
	
private:
	Progress* blood;   //Ѫ��
	int bloodNum;
	//vector<achievement_type> Achievement;  //����õĳɾ�
	int money;				//����
	float speed;			//�����ƶ��ٶ�
	int commonAttack;	   //��ͨ����ֵ
	int exp;
	int fullBlood;

public:
	Vec2 initPos;			//��Ƭ��ͼ��ʼ��λ��
	int killCount;       //ɱ�м���
	Tower* enemyTower;
	int bonusSpeed;
	Sprite* image;
	int bonusAttack;
	int bonusDefend;
	int bonusBlood;
	Tower* enemyDefendTower;
	Sprite* skillSprite;
	//EnemySoldier* thisSoldierVector[3];
	std::vector<EnemySoldier*> *thisSoldierVector; //������ǿͻ����û���soldier
	void addReward(int moneyNum,int expNum) {
		money += moneyNum;
		exp += expNum;
		killCount += 1;
	}
	virtual bool init();   //  �����ʼ��
	//bool attackTrick(const char *format,int num);   //  ����
	virtual bool checkIsAttack();  //����Ƿ��ܵ�����   
	void autoAttack(Node * thisSoldier);
	void autoRun(Vec2 pos);
	int getAttackDir(int tempDir);
	bool isHeroWalking;
	Rect *inRect;
	int currentPos;
	float getHeroSpeed();	     //�����ٶ�
	int getCommonAttack() { return commonAttack; }       //������ͨ����ֵ
	int getBloodNum() { return bloodNum; }	//����Ѫ��
	void minusBlood(int num);
	int getNowPointDir(Node * player, Vec2 newpoint);
	//��Ѫ&�����ж�
	void attackEnemyAnimation(int dir);
	void skillAnimation();
	void updateHeroSpeed(float newspeed);
	void setMoney(int num) { money = num; }
	int getMoney() { return money; }
	int getExp() { return exp; }
	void initHeroAttr(int _money, float _speed, int _blood, int _commonAttack, int _exp, Tower* _tower);
	void equipbonusBlood(int num);
	//CREATE_FUNC(Hero);   //�����벻��д������Ȼ�޷�createӢ��
};

