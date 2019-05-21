#pragma once
//http://www.87g.com/zixun/16123.html    һ������   ������ҫӢ��ͼ

//��SelectHero�����л���ѡ��Ӣ�۵Ľ��棬   �û����ĳ��Ӣ�ۣ�ͨ��һ���ص�����������һ��hero_role������
//Ȼ���������������ж�   ���ݲ�ͬ�������Ӣ��
#include"cocos2d.h"
#include<vector>
#include"Core/Sprite/Progress.h"

#define hero_moonGoddess_attack "hero/change/attck/1047-6a75dcb1-0%d00%d.png"
using namespace std;
USING_NS_CC;
class Tower;
class EnemySoldier;

typedef enum {
	shooter = 0,    //����
	Master = 1,     //��ʦ
	auxiliary = 2,   //����
	Assassin=3,       //�̿�
	tank=4			 //̹��
}hero_type;
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

//typedef enum {
//	bestteammate = 0,    //  ��Ѷ���
//	slaughter = 1,     //   Ѫ���ȷ�
//	lifewinner = 2,   //    ����Ӯ��
//       //��������������
//}achievement_type;
//typedef enum {
//	moonGoddess = 0,    //槼�
//	houyi = 1,     //����
//	yase = 2,   //��ɪ
//
//}hero_role;
class Hero:public Sprite
{
	
private:
	Progress* blood;   //Ѫ��
	int bloodNum;
	//vector<achievement_type> Achievement;  //����õĳɾ�
	hero_type type;                //Ӣ���������ֽ�ɫ  
	int money;				//����
	float speed;			//�����ƶ��ٶ�
	int commonAttack;	   //��ͨ����ֵ
	int exp;
public:
	Vec2 initPos;			//��Ƭ��ͼ��ʼ��λ��
	Tower* enemyTower;
	int bounsSpeed=0;
	int bounsAttack=0;
	int bounsDefend=0;
	int bounsBlood = 0;
	Vector<EnemySoldier*> *thisSoldierVector; //������ǿͻ����û���soldier
	void addReward(int moneyNum,int expNum) {
		money += moneyNum;
		exp += expNum;
	}
	virtual bool init();   //  �����ʼ��
	//bool attackTrick(const char *format,int num);   //  ����
	virtual bool checkIsAttack();  //����Ƿ��ܵ�����   
	void autoAttack(Node * thisSoldier);
	void autoRun(Vec2 pos);
	int getAttackDir(int tempDir);
	bool isHeroWalking;
	int currentPos;
	float getHeroSpeed();	     //�����ٶ�
	int getCommonAttack() { return commonAttack; }       //������ͨ����ֵ
	int getBloodNum() { return bloodNum; }	//����Ѫ��
	void minusBlood(int num);
	int getNowPointDir(Node * player, Vec2 newpoint);
	//��Ѫ&�����ж�
	void attackEnemyAnimation(int dir);
	void updateHeroSpeed(float newspeed);
	void setMoney(int num) { money = num; }
	int getMoney() { return money; }
	void initHeroAttr(int _money, float _speed, int _blood, int _commonAttack, int _exp, Tower* _tower);
	//CREATE_FUNC(Hero);   //�����벻��д������Ȼ�޷�createӢ��
};

