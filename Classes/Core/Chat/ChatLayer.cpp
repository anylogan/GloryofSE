#include"Core/Chat/ChatLayer.h"
#include"proj.win32/MyUtility.h"
#include"Core/Net/Client.h"
#include  "cocos2d\external\win32-specific\icon\include\iconv.h"

USING_NS_CC;
int ChatLayer::GBKToUTF8(std::string &gbkStr, const char* toCode, const char* formCode) {
	iconv_t iconvH;
	iconvH = iconv_open(formCode, toCode);
	if (iconvH == 0) {
		return -1;
	}
	const char* strChar = gbkStr.c_str();
	const char** pin = &strChar;
	size_t strLength = gbkStr.length();
	char *outbuf = (char*)malloc(strLength * 4);
	char *pBuff = outbuf;
	memset(outbuf, 0, strLength * 4);
	size_t outLength = strLength * 4;
	if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength)) {
		iconv_close(iconvH);
		return -1;
	}
	gbkStr = pBuff;
	iconv_close(iconvH);
	return 0;
}
ChatLayer* ChatLayer::createScene()
{
	return ChatLayer::create();
}

void ChatLayer::sendChatMsg(Ref * pSender, ui::Widget::TouchEventType type)
{

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		_textfield = static_cast<ui::TextField*>(_ui_node->getChildByName("TextField_1"));
		std::string message = _textfield->getStringValue();
		GBKToUTF8(message, "gb2312", "utf-8");
		if (message.compare("") != 0)
		{
			std::string message1 = "��";
			GBKToUTF8(message1, "gb2312", "utf-8");
				_text = _chat->getChatMsg(message1, message);
				_listview->pushBackCustomItem(_text);
				_listview->sortAllChildren();
			    _listview->jumpToBottom();//�������ʾ�ڵײ�
				index += 1;
				Client::getInstance()->sendMessage(message);
		}

		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}
bool ChatLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//�����
	index = 1;
	_ui_node = CSLoader::createNode("chatroom/ChatLayer.csb");
	this->addChild(_ui_node, 200, 100);

	_listview = static_cast<ui::ListView*>(_ui_node->getChildByName("ListView_1"));
	_listview->setBright(true);

	auto enterbt = static_cast<ui::Button*>(_ui_node->getChildByName("Button_1"));
	enterbt->addTouchEventListener(CC_CALLBACK_2(ChatLayer::sendChatMsg, this));

	_chat = ChatUI::createScene();
	std::string message1 = "ϵͳ";
	GBKToUTF8(message1, "gb2312", "utf-8");
	std::string message2 = "��ӭ��½���뾡�����ܣ�";
	GBKToUTF8(message2, "gb2312", "utf-8");
	_text = _chat->getChatMsg(message1, message2);
	_listview->insertCustomItem(_text, 0);
	this->schedule(schedule_selector(ChatLayer::updateMessage), 0.5f);
	return true;
}

void ChatLayer::updateMessage(float dt)
{
	std::string get_msg = Client::getInstance()->getMessage();
	if (get_msg != "")
	{
		std::string message1 = "����";
		GBKToUTF8(message1, "gb2312", "utf-8");
			_text = _chat->getChatMsg(message1, get_msg);
			_listview->pushBackCustomItem(_text);
			_listview->sortAllChildren();
			_listview->jumpToBottom();//�������ʾ�ڵײ�
			index += 1;
			
	}
}


