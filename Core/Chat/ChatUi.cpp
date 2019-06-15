#include "Core/Chat/ChatUi.h"
#include"proj.win32/MyUtility.h"
#include "ui/UIText.h"


ChatUI::ChatUI()
{
}

ChatUI::~ChatUI()
{
}

ChatUI* ChatUI::createScene()
{
	return ChatUI::create();
}


bool ChatUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initRichEdit();
	return true;
}


void ChatUI::initRichEdit()
{

}

cui::RichText* ChatUI::getChatMsg(string  roleName, string  chatMsg)
{
	string siz = ":";
	int msglen = chatMsg.size() + siz.size() +  roleName.size();
	int s = msglen / 25;
	if (msglen % 25 > 0)
	{
		s += 1;
	}
	cui::RichText* _richChat = cui::RichText::create();
	_richChat->ignoreContentAdaptWithSize(false);
	if (s == 1)
	{
		_richChat->setContentSize(Size(200, 18 * s));
	}
	else {
		_richChat->setContentSize(Size(200, 15 * s + 3));
	}

	//RichElementText* resrole = new RichElementText();

	RichElementText* resrole = RichElementText::create(1, Color3B::GREEN, 255, MyUtility::gbk_2_utf8(roleName), "fonts/simkai.ttf", 15 );
	resrole->setUnderLineSize(1);
	resrole->setUnderLineColor(Color4B::GREEN);
	auto fuhao = RichElementText::create(1, Color3B::BLACK, 255, MyUtility::gbk_2_utf8(":"), "fonts/simkai.ttf", 15);
	auto re = RichElementText::create(1, Color3B(0, 255, 255), 255, MyUtility::gbk_2_utf8(chatMsg), "fonts/simkai.ttf", 15);
	_richChat->pushBackElement(resrole);
	_richChat->pushBackElement(fuhao);
	_richChat->pushBackElement(re);
	//RichElementNewLine* line = RichElementNewLine::create(1, Color3B::WHITE, 255);
	//_richChat->pushBackElement(line);
	return _richChat;
}