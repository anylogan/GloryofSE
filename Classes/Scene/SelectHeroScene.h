#pragma once
//������ѡ��Ӣ�۵�ʱ�򱳾�����������ҫ��Ӣ��ר��������
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Core/Controller/GameScene.h"
#include"Core/Controller/GameController.h"
#include"Scene/GlobalDefine.h"
USING_NS_CC;


//hero_role HeroRole=moonGoddess; //����һ��ȫ�ֱ���  ���ҳ�ʼ��
//extern hero_role HeroRole; 

class SelectHeroScene :public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void ChangeCallBack(Ref *pSender);
	void HuamulanCallBack(Ref *pSender);
	void SunCallBack(Ref *pSender);

    // implement the "static create()" method manually

	CREATE_FUNC(SelectHeroScene);


};