#pragma once
#ifndef _CHAT_UI_H_
#define _CHAT_UI_H_

#include "cocos2d.h"
#include <string>
#include "Core/Chat/RichUi.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::cui;

class ChatUI :public cocos2d::Layer
{
public:
	ChatUI();
	~ChatUI();

	static ChatUI* createScene();

	virtual bool init();

	CREATE_FUNC(ChatUI);

	void initRichEdit();

	cui::RichText* getChatMsg( string roleName, string chatMsg);

private:
	cui::RichText* _richBugle;//À®°È

};



#endif
