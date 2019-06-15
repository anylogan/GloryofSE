#pragma once
#ifndef _CHAT_LAYER_
#define _CHAT_LAYER_

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"proj.win32/MyUtility.h"
#include "cocostudio/CocoStudio.h"
#include"Core/Chat/ChatUi.h"


class ChatLayer: public cocos2d::Layer
{
public:
	int GBKToUTF8(std::string & gbkStr, const char * toCode, const char * formCode);
	static ChatLayer* createScene();
	virtual bool init();

	
	CREATE_FUNC(ChatLayer);

	//聊天框有关内容
	Node* _ui_node;
	ChatUI* _chat;
	ui::TextField* _textfield;
	ui::ListView* _listview;
	int index;
	cui::RichText* _text;
	void sendChatMsg(Ref * pSender, ui::Widget::TouchEventType type);
	void updateMessage(float dt);
};

#endif