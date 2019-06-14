#include"Core/Chat/ChatLayer.h"
#include"proj.win32/MyUtility.h"
#include"Core/Net/Client.h"
USING_NS_CC;

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
		if (_textfield->getString().compare("") != 0)
		{
			
				std::string message = _textfield->getString();
				_text = _chat->getChatMsg("me", message);
				_listview->pushBackCustomItem(_text);
				_listview->sortAllChildren();
			    _listview->jumpToBottom();//将最后显示在底部
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
	//聊天框
	index = 1;
	_ui_node = CSLoader::createNode("chatroom/ChatLayer.csb");
	this->addChild(_ui_node, 200, 100);

	_listview = static_cast<ui::ListView*>(_ui_node->getChildByName("ListView_1"));
	_listview->setBright(true);

	auto enterbt = static_cast<ui::Button*>(_ui_node->getChildByName("Button_1"));
	enterbt->addTouchEventListener(CC_CALLBACK_2(ChatLayer::sendChatMsg, this));

	_chat = ChatUI::createScene();
	_text = _chat->getChatMsg("system", MyUtility::gbk_2_utf8("welcome and enjoy!"));

	_listview->insertCustomItem(_text, 0);
	_listview->setInnerContainerSize(cocos2d::Size(200, 200));
	
	this->schedule(schedule_selector(ChatLayer::updateMessage), 0.5f);
	return true;
}

void ChatLayer::updateMessage(float dt)
{
	std::string get_msg = Client::getInstance()->getMessage();
	if (get_msg != "")
	{
		
			_text = _chat->getChatMsg("opponent", get_msg);
			_listview->pushBackCustomItem(_text);
			_listview->sortAllChildren();
			_listview->jumpToBottom();//将最后显示在底部
			index += 1;
			
	}
}


