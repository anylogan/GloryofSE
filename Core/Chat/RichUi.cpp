#include "Core/Chat/RichUi.h"
#include "ui/UIHelper.h"

NS_CC_BEGIN

namespace cui {


	bool RichElement::init(int tag, const Color3B &color, GLubyte opacity)
	{
		_tag = tag;
		_color = color;
		_opacity = opacity;
		return true;
	}


	RichElementText* RichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
	{
		RichElementText* element = new (std::nothrow) RichElementText();
		if (element && element->init(tag, color, opacity, text, fontName, fontSize))
		{
			element->autorelease();
			return element;
		}
		CC_SAFE_DELETE(element);
		return nullptr;
	}

	bool RichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
	{
		if (RichElement::init(tag, color, opacity))
		{
			_text = text;
			_fontName = fontName;
			_fontSize = fontSize;
			return true;
		}
		return false;
	}

	void RichElementText::setTouchCallBack(std::function<void(std::string)> touch, std::string pramas)
	{
		_touchCallback = touch;
		_pramas = pramas;
	}

	void RichElementText::setLinkUrl(std::string linkurl)
	{
		_linkurl = linkurl;
		setTouchCallBack(std::bind(&RichElementText::linkCallback, this, std::placeholders::_1), linkurl);
	}

	void RichElementText::linkCallback(std::string str)
	{
		log("call open url %s", str.c_str());
	}

	RichElementImage* RichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
	{
		RichElementImage* element = new (std::nothrow) RichElementImage();
		if (element && element->init(tag, color, opacity, filePath))
		{
			element->autorelease();
			return element;
		}
		CC_SAFE_DELETE(element);
		return nullptr;
	}

	bool RichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
	{
		if (RichElement::init(tag, color, opacity))
		{
			_filePath = filePath;
			return true;
		}
		return false;
	}

	RichElementCustomNode* RichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
	{
		RichElementCustomNode* element = new (std::nothrow) RichElementCustomNode();
		if (element && element->init(tag, color, opacity, customNode))
		{
			element->autorelease();
			return element;
		}
		CC_SAFE_DELETE(element);
		return nullptr;
	}

	bool RichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
	{
		if (RichElement::init(tag, color, opacity))
		{
			_customNode = customNode;
			_customNode->retain();
			return true;
		}
		return false;
	}

	RichElementNewLine* RichElementNewLine::create(int tag, const Color3B& color, GLubyte opacity)
	{
		RichElementNewLine* element = new (std::nothrow) RichElementNewLine();
		if (element && element->init(tag, color, opacity))
		{
			element->autorelease();
			return element;
		}
		CC_SAFE_DELETE(element);
		return nullptr;
	}

	RichText::RichText() :
		_formatTextDirty(true),
		_leftSpaceWidth(0.0f),
		_verticalSpace(0.0f),
		_touchPriority(-1)
	{
		_touchDelegate.clear();
	}

	RichText::~RichText()
	{
		_richElements.clear();
		//
		std::map<Node*, std::function<void(std::string)> >::const_iterator it = _touchDelegate.begin();
		while (it != _touchDelegate.end())
		{
			Node* node = it->first;
			if (node->getUserData() != nullptr)
			{
				delete (std::string*)(node->getUserData());
				node->setUserData(nullptr);
			}
			++it;
		}
		_touchDelegate.clear();
	}

	/***************可以重写改造换行******************/
	RichText* RichText::create()
	{
		RichText* widget = new (std::nothrow) RichText();
		if (widget && widget->init())
		{
			widget->autorelease();
			return widget;
		}
		CC_SAFE_DELETE(widget);
		return nullptr;
	}

	bool RichText::init()
	{
		if (Widget::init())
		{
			return true;
		}
		return false;
	}

	void RichText::onEnter()
	{
		Widget::onEnter();
		EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(RichText::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(RichText::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _touchPriority);
	}

	void RichText::onExit()
	{
		Widget::onExit();
		_eventDispatcher->removeAllEventListeners();
	}

	void RichText::initRenderer()
	{

	}

	void RichText::insertElement(RichElement *element, int index)
	{
		_richElements.insert(index, element);
		_formatTextDirty = true;
	}

	void RichText::pushBackElement(RichElement *element)
	{
		_richElements.pushBack(element);
		_formatTextDirty = true;
	}

	void RichText::removeElement(int index)
	{
		_richElements.erase(index);
		_formatTextDirty = true;
	}

	void RichText::removeElement(RichElement *element)
	{
		_richElements.eraseObject(element);
		_formatTextDirty = true;
	}

	void RichText::formatText()
	{
		if (_formatTextDirty)
		{
			this->removeAllProtectedChildren();
			_elementRenders.clear();
			if (_ignoreSize)
			{
				addNewLine();
				for (ssize_t i = 0; i < _richElements.size(); i++)
				{
					RichElement* element = _richElements.at(i);
					Node* elementRenderer = nullptr;
					switch (element->_type)
					{
					case RichElement::Type::TEXT:
					{
						Label* elementLabel = nullptr;
						RichElementText* elmtText = static_cast<RichElementText*>(element);
						if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
						{
							elementLabel = Label::createWithTTF(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
						}
						else
						{
							elementLabel = Label::createWithSystemFont(elmtText->_text.c_str(), elmtText->_fontName, elmtText->_fontSize);
						}
						if (elmtText->getOutLine() > 0)
						{
							elementLabel->enableOutline(elmtText->getOutLineColor(), elmtText->getOutLine());
						}
						if (elmtText->getShadow())
						{
							elementLabel->enableShadow();
						}
						if (elmtText->getUnderLineSize() > 0)
						{
							LayerColor* l = nullptr;
							if (elmtText->getUnderLineColor().a == 0)
							{
								l = LayerColor::create(Color4B(elmtText->_color), elementLabel->getContentSize().width, elmtText->getUnderLineSize());
							}
							else
							{
								l = LayerColor::create(elmtText->getUnderLineColor(), elementLabel->getContentSize().width, elmtText->getUnderLineSize());
							}
							elementLabel->setUserObject(l);
						}
						if (elmtText->getTouchCallBack())
						{
							std::string* tag = new std::string("" + elmtText->getPramas());
							elementLabel->setUserData(tag);
							_touchDelegate[elementLabel] = elmtText->getTouchCallBack();
						}
						elementRenderer = elementLabel;

						break;
					}
					case RichElement::Type::IMAGE:
					{
						RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
						elementRenderer = Sprite::create(elmtImage->_filePath.c_str());
						break;
					}
					case RichElement::Type::CUSTOM:
					{
						RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
						elementRenderer = elmtCustom->_customNode;
						break;
					}
					case RichElement::Type::NEWLINE:
					{
						addNewLine();
						break;
					}
					default:
						break;
					}
					elementRenderer->setColor(element->_color);
					elementRenderer->setOpacity(element->_opacity);
					pushToContainer(elementRenderer);
				}
			}
			else
			{
				addNewLine();
				for (ssize_t i = 0; i < _richElements.size(); i++)
				{

					RichElement* element = static_cast<RichElement*>(_richElements.at(i));
					switch (element->_type)
					{
					case RichElement::Type::TEXT:
					{
						RichElementText* elmtText = static_cast<RichElementText*>(element);
						handleTextRenderer(*elmtText);
						break;
					}
					case RichElement::Type::IMAGE:
					{
						RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
						handleImageRenderer(elmtImage->_filePath.c_str(), elmtImage->_color, elmtImage->_opacity);
						break;
					}
					case RichElement::Type::CUSTOM:
					{
						RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
						handleCustomRenderer(elmtCustom->_customNode);
						break;
					}
					case RichElement::Type::NEWLINE:
					{
						addNewLine();
						break;
					}
					default:
						break;
					}
				}
			}
			formarRenderers();
			_formatTextDirty = false;
		}
	}

	void RichText::visit(Renderer * renderer, const Mat4 & parentTransform, uint32_t parentFlags)
	{
		if (_enabled)
		{
			formatText();
			Widget::visit(renderer, parentTransform, parentFlags);
		}
	}


	void RichText::handleTextRenderer(const RichElementText& textInfo)
	{
		auto fileExist = FileUtils::getInstance()->isFileExist(textInfo._fontName);
		Label* textRenderer = nullptr;
		if (fileExist)
		{
			textRenderer = Label::createWithTTF(textInfo._text, textInfo._fontName, textInfo._fontSize);
		}
		else
		{
			textRenderer = Label::createWithSystemFont(textInfo._text, textInfo._fontName, textInfo._fontSize);
		}


		float textRendererWidth = textRenderer->getContentSize().width;
		_leftSpaceWidth -= textRendererWidth;
		if (_leftSpaceWidth < 0.0f)
		{
			float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
			std::string curText = textInfo._text;
			size_t stringLength = StringUtils::getCharacterCountInUTF8String(textInfo._text);
			int leftLength = stringLength * (1.0f - overstepPercent);

			// The adjustment of the new line position
			auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;
			auto leftStr = ui::Helper::getSubStringOfUTF8String(curText, 0, leftLength);
			textRenderer->setString(leftStr);
			auto leftWidth = textRenderer->getContentSize().width;
			if (originalLeftSpaceWidth < leftWidth) {
				// Have protruding
				for (;;) {
					leftLength--;
					leftStr = ui::Helper::getSubStringOfUTF8String(curText, 0, leftLength);
					textRenderer->setString(leftStr);
					leftWidth = textRenderer->getContentSize().width;
					if (leftWidth <= originalLeftSpaceWidth) {
						break;
					}
					else if (leftLength <= 0) {
						break;
					}
				}
			}
			else if (leftWidth < originalLeftSpaceWidth) {
				// A wide margin
				for (;;) {
					leftLength++;
					leftStr = ui::Helper::getSubStringOfUTF8String(curText, 0, leftLength);
					textRenderer->setString(leftStr);
					leftWidth = textRenderer->getContentSize().width;
					if (originalLeftSpaceWidth < leftWidth) {
						leftLength--;
						break;
					}
					else if (stringLength <= leftLength) {
						break;
					}
				}
			}

			//The minimum cut length is 1, otherwise will cause the infinite loop.
			if (0 == leftLength) leftLength = 1;
			std::string leftWords = ui::Helper::getSubStringOfUTF8String(curText, 0, leftLength);
			std::string cutWords = ui::Helper::getSubStringOfUTF8String(curText, leftLength, stringLength - leftLength);
			if (leftLength > 0)
			{
				Label* leftRenderer = nullptr;
				if (fileExist)
				{
					leftRenderer = Label::createWithTTF(ui::Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), textInfo._fontName, textInfo._fontSize);
				}
				else
				{
					leftRenderer = Label::createWithSystemFont(ui::Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), textInfo._fontName, textInfo._fontSize);
				}
				if (leftRenderer)
				{
					leftRenderer->setColor(textInfo._color);
					leftRenderer->setOpacity(textInfo._opacity);
					if (textInfo.getOutLine() > 0)
					{
						leftRenderer->enableOutline(textInfo.getOutLineColor(), textInfo.getOutLine());
					}
					if (textInfo.getShadow())
					{
						leftRenderer->enableShadow();
					}
					if (textInfo.getUnderLineSize() > 0)
					{
						LayerColor* l = nullptr;
						if (textInfo.getUnderLineColor().a == 0)
						{
							l = LayerColor::create(Color4B(textInfo._color), leftRenderer->getContentSize().width, textInfo.getUnderLineSize());
						}
						else
						{
							l = LayerColor::create(textInfo.getUnderLineColor(), leftRenderer->getContentSize().width, textInfo.getUnderLineSize());
						}
						leftRenderer->setUserObject(l);
					}
					if (textInfo.getTouchCallBack())
					{
						std::string* tag = new std::string(textInfo.getPramas());
						leftRenderer->setUserData(tag);
						_touchDelegate[leftRenderer] = textInfo.getTouchCallBack();
					}

					pushToContainer(leftRenderer);
				}
			}

			addNewLine();
			RichElementText cutRich = textInfo;
			cutRich._text = cutWords;
			handleTextRenderer(cutRich);
		}
		else
		{
			textRenderer->setColor(textInfo._color);
			textRenderer->setOpacity(textInfo._opacity);

			if (textInfo.getOutLine() > 0)
			{
				textRenderer->enableOutline(textInfo.getOutLineColor(), textInfo.getOutLine());
			}
			if (textInfo.getShadow())
			{
				textRenderer->enableShadow();
			}
			if (textInfo.getUnderLineSize() > 0)
			{
				LayerColor* l = nullptr;
				if (textInfo.getUnderLineColor().a == 0)
				{
					l = LayerColor::create(Color4B(textInfo._color), textRenderer->getContentSize().width, textInfo.getUnderLineSize());
				}
				else
				{
					l = LayerColor::create(textInfo.getUnderLineColor(), textRenderer->getContentSize().width, textInfo.getUnderLineSize());
				}
				textRenderer->setUserObject(l);
			}
			if (textInfo.getTouchCallBack())
			{
				std::string* tag = new std::string(textInfo.getPramas());
				textRenderer->setUserData(tag);
				_touchDelegate[textRenderer] = textInfo.getTouchCallBack();
			}

			pushToContainer(textRenderer);
		}
	}

	void RichText::handleImageRenderer(const std::string& fileParh, const Color3B &color, GLubyte opacity)
	{
		Sprite* imageRenderer = Sprite::create(fileParh);
		handleCustomRenderer(imageRenderer);
	}

	void RichText::handleCustomRenderer(cocos2d::Node *renderer)
	{
		Size imgSize = renderer->getContentSize();
		_leftSpaceWidth -= imgSize.width;
		if (_leftSpaceWidth < 0.0f)
		{
			addNewLine();
			pushToContainer(renderer);
			_leftSpaceWidth -= imgSize.width;
		}
		else
		{
			pushToContainer(renderer);
		}
	}

	void RichText::addNewLine()
	{
		_leftSpaceWidth = _customSize.width;
		_elementRenders.push_back(new Vector<Node*>());
	}

	bool RichText::onTouchBegan(Touch * touch, Event * unusedEvent)
	{
		std::map<Node*, std::function<void(std::string)> >::const_iterator it = _touchDelegate.begin();
		while (it != _touchDelegate.end())
		{
			Node* node = it->first;
			if (node->getBoundingBox().containsPoint(node->getParent()->convertTouchToNodeSpace(touch)))
			{
				return true;
			}
			++it;
		}
		return false;
	}

	void RichText::onTouchEnded(Touch * touch, Event * unusedEvent)
	{
		std::map<Node*, std::function<void(std::string)> >::const_iterator it = _touchDelegate.begin();
		while (it != _touchDelegate.end())
		{
			Node* node = it->first;
			if (node->getBoundingBox().containsPoint(node->getParent()->convertTouchToNodeSpace(touch)))
			{
				if (node->getUserData() != nullptr)
				{
					(it->second)(*((std::string*)node->getUserData()));
				}

				return;
			}
			++it;
		}
	}

	void RichText::formarRenderers()
	{
		if (_ignoreSize)
		{
			float newContentSizeWidth = 0.0f;
			float newContentSizeHeight = 0.0f;

			Vector<Node*>* row = (_elementRenders[0]);
			float nextPosX = 0.0f;
			for (ssize_t j = 0; j < row->size(); j++)
			{
				Node* l = row->at(j);
				l->setAnchorPoint(Vec2::ZERO);
				l->setPosition(nextPosX, 0.0f);
				this->addProtectedChild(l, 1);
				/****这里将下划线显示*************/
				Node* under = dynamic_cast<Node*>(l->getUserObject());
				if (under)
				{
					under->setPosition(Point(nextPosX, -1));
					this->addProtectedChild(under, 1);
					l->setUserObject(nullptr);
				}
				/**********************************/
				Size iSize = l->getContentSize();
				newContentSizeWidth += iSize.width;
				newContentSizeHeight = MAX(newContentSizeHeight, iSize.height);
				nextPosX += iSize.width;
			}
			this->setContentSize(Size(newContentSizeWidth, newContentSizeHeight));
		}
		else
		{
			float newContentSizeHeight = 0.0f;
			float *maxHeights = new float[_elementRenders.size()];

			for (size_t i = 0; i < _elementRenders.size(); i++)
			{
				Vector<Node*>* row = (_elementRenders[i]);
				float maxHeight = 0.0f;
				for (ssize_t j = 0; j < row->size(); j++)
				{
					Node* l = row->at(j);
					maxHeight = MAX(l->getContentSize().height, maxHeight);
				}
				maxHeights[i] = maxHeight;
				newContentSizeHeight += maxHeights[i];
			}

			float nextPosY = _customSize.height;
			for (size_t i = 0; i < _elementRenders.size(); i++)
			{
				Vector<Node*>* row = (_elementRenders[i]);
				float nextPosX = 0.0f;
				nextPosY -= (maxHeights[i] + _verticalSpace);

				for (ssize_t j = 0; j < row->size(); j++)
				{
					Node* l = row->at(j);
					l->setAnchorPoint(Vec2::ZERO);
					l->setPosition(nextPosX, nextPosY);
					this->addProtectedChild(l, 1);
					/****这里将下划线显示*************/
					Node* under = dynamic_cast<Node*>(l->getUserObject());
					if (under)
					{
						under->setPosition(Point(nextPosX, nextPosY - 1));
						this->addProtectedChild(under, 1);
						l->setUserObject(nullptr);
					}
					/**********************************/
					nextPosX += l->getContentSize().width;
				}
			}
			delete[] maxHeights;
		}

		size_t length = _elementRenders.size();
		for (size_t i = 0; i < length; i++)
		{
			Vector<Node*>* l = _elementRenders[i];
			l->clear();
			delete l;
		}
		_elementRenders.clear();

		if (_ignoreSize)
		{
			Size s = getVirtualRendererSize();
			this->setContentSize(s);
		}
		else
		{
			this->setContentSize(_customSize);
		}
		updateContentSizeWithTextureSize(_contentSize);
	}

	void RichText::adaptRenderers()
	{
		this->formatText();
	}

	void RichText::pushToContainer(cocos2d::Node *renderer)
	{
		if (_elementRenders.size() <= 0)
		{
			return;
		}
		_elementRenders[_elementRenders.size() - 1]->pushBack(renderer);
	}

	void RichText::setVerticalSpace(float space)
	{
		_verticalSpace = space;
	}

	void RichText::ignoreContentAdaptWithSize(bool ignore)
	{
		if (_ignoreSize != ignore)
		{
			_formatTextDirty = true;
			Widget::ignoreContentAdaptWithSize(ignore);
		}
	}

	std::string RichText::getDescription() const
	{
		return "RichText";
	}



}

NS_CC_END