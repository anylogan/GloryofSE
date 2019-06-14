#pragma once
#ifndef __RICHUI_H__
#define __RICHUI_H__

#include "ui/UIWidget.h"
#include "cocos2d.h"
USING_NS_CC;

NS_CC_BEGIN
/**
* @addtogroup cui
* @modify source code by iuoon@zhejiang.china
*/

namespace cui {

	/**
	*@brief Rich text element base class.
	* It defines the basic common properties for all rich text element.
	*/
	class  RichElement : public Ref
	{
	public:
		/**
		*@brief Rich element type.
		*/
		enum class Type
		{
			TEXT,
			IMAGE,
			CUSTOM,
			NEWLINE
		};

		/**
		* @brief Default constructor.
		* @js ctor
		* @lua new
		*/
		RichElement() {};

		/**
		* @brief Default destructor.
		* @js NA
		* @lua NA
		*/
		virtual ~RichElement() {};


		/**
		* @brief Initialize a rich element with different arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in @see `Color3B`.
		* @param opacity A opacity value in `GLubyte`.
		* @return True if initialize success, false otherwise.
		*/
		bool init(int tag, const Color3B& color, GLubyte opacity);
	protected:
		Type _type;
		int _tag;
		CC_SYNTHESIZE(std::string, _pramas, Pramas);
		Color3B _color;
		GLubyte _opacity;
		friend class RichText;
	};

	/**
	*@brief Rich element for displaying text.
	*/
	class  RichElementText : public RichElement
	{
	public:

		/**
		*@brief Default constructor.
		* @js ctor
		* @lua new
		*/
		RichElementText() {
			_type = Type::TEXT;
			_outLine = -1;
			_outLineColor = Color4B::BLACK;
			_shadow = false;
			_linkurl = "";
			_underLinecolor = Color4B(0, 0, 0, 0);
			_underLinesize = -1;
			_touchCallback = nullptr;
		};


		/**
		*@brief Default destructor.
		* @js NA
		* @lua NA
		*/
		virtual ~RichElementText() {};

		/**
		* @brief Initialize a RichElementText with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @param text Content string.
		* @param fontName Content font name.
		* @param fontSize Content font size.
		* @return True if initialize scucess, false otherwise.
		*/
		bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);


		/**
		* @brief Create a RichElementText with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @param text Content string.
		* @param fontName Content font name.
		* @param fontSize Content font size.
		* @return RichElementText instance.
		*/
		static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);

		void setTouchCallBack(std::function<void(std::string)> touch, std::string tag);
		void setLinkUrl(std::string linkurl);

	protected:
		std::string _text;
		std::string _fontName;
		float _fontSize;
		friend class RichText;
		/**************************************/
	protected:
		//		CC_SYNTHESIZE(Color4B, _textColor, TextColor); //设置字体颜色
		CC_SYNTHESIZE(int, _outLine, OutLine);  //描边大小
		CC_SYNTHESIZE(Color4B, _outLineColor, OutLineColor);//描边颜色
		CC_SYNTHESIZE(bool, _shadow, Shadow); //启用阴影
		CC_SYNTHESIZE_READONLY(std::string, _linkurl, LinkUrl);//设置链接（或点击事件当参数传输）
		CC_SYNTHESIZE(Color4B, _underLinecolor, UnderLineColor);//下划线颜色
		CC_SYNTHESIZE(int, _underLinesize, UnderLineSize); //下划线大小
		CC_SYNTHESIZE_READONLY(std::function<void(std::string)>, _touchCallback, TouchCallBack);//点击回调函数

	private:
		void linkCallback(std::string str);

	};

	/**
	*@brief Rich element for displaying images.
	*/
	class  RichElementImage : public RichElement
	{
	public:

		/**
		* @brief Default constructor.
		* @js ctor
		* @lua new
		*
		*/
		RichElementImage() { _type = Type::IMAGE; };


		/**
		* @brief Default destructor.
		* @js NA
		* @lua NA
		*/
		virtual ~RichElementImage() {};


		/**
		* @brief Initialize a RichElementImage with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @param filePath A image file name.
		* @return True if initialize success, false otherwise.
		*/
		bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);


		/**
		* @brief Create a RichElementImage with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @param filePath A image file name.
		* @return A RichElementImage instance.
		*/
		static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
	protected:
		std::string _filePath;
		Rect _textureRect;
		int _textureType;
		friend class RichText;
	};

	/**
	*@brief Rich element for displaying custom node type.
	*/
	class  RichElementCustomNode : public RichElement
	{
	public:

		/**
		* @brief Default constructor.
		* @js ctor
		* @lua new
		*/
		RichElementCustomNode() { _type = Type::CUSTOM; };


		/**
		* @brief Default destructor.
		* @js NA
		* @lua NA
		*/
		virtual ~RichElementCustomNode() { CC_SAFE_RELEASE(_customNode); };


		/**
		* @brief Initialize a RichElementCustomNode with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @param customNode A custom node pointer.
		* @return True if initialize success, false otherwise.
		*/
		bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);

		/**
		* @brief Create a RichElementCustomNode with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @param customNode A custom node pointer.
		* @return A RichElementCustomNode instance.
		*/
		static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
	protected:
		Node* _customNode;
		friend class RichText;
	};

	/**
	*@brief Rich element for new line.
	*/
	class  RichElementNewLine : public RichElement
	{
	public:

		/**
		* @brief Default constructor.
		* @js ctor
		* @lua new
		*
		*/
		RichElementNewLine() { _type = Type::NEWLINE; };

		/**
		* @brief Default destructor.
		* @js NA
		* @lua NA
		*/
		virtual ~RichElementNewLine() {};

		/**
		* @brief Create a RichElementNewLine with various arguments.
		*
		* @param tag A integer tag value.
		* @param color A color in Color3B.
		* @param opacity A opacity in GLubyte.
		* @return A RichElementNewLine instance.
		*/
		static RichElementNewLine* create(int tag, const Color3B& color, GLubyte opacity);
	protected:
		friend class RichText;
	};

	/**
	*@brief A container for displaying various RichElements.
	* We could use it to display texts with images easily.
	*/
	class  RichText : public ui::Widget
	{
	public:

		/**
		* @brief Default constructor.
		* @js ctor
		* @lua new
		*/
		RichText();

		/**
		* @brief Default destructor.
		* @js NA
		* @lua NA
		*/
		virtual ~RichText();

		/**
		* @brief Create a empty RichText.
		*
		* @return RichText instance.
		*/
		static RichText* create();

		/**
		* @brief Insert a RichElement at a given index.
		*
		* @param element A RichElement type.
		* @param index A given index.
		*/
		void insertElement(RichElement* element, int index);

		/**
		* @brief Add a RichElement at the end of RichText.
		*
		* @param element A RichElement instance.
		*/
		void pushBackElement(RichElement* element);

		/**
		* @brief Remove a RichElement at a given index.
		*
		* @param index A integer index value.
		*/
		void removeElement(int index);

		/**
		* @brief Remove specific RichElement.
		*
		* @param element A RichElement type.
		*/
		void removeElement(RichElement* element);

		/**
		* @brief Set vertical space between each RichElement.
		*
		* @param space Point in float.
		*/
		void setVerticalSpace(float space);

		/**
		* @brief Rearrange all RichElement in the RichText.
		* It's usually called internally.
		*/
		void formatText();

		virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

		//override functions.
		virtual void ignoreContentAdaptWithSize(bool ignore) override;
		virtual std::string getDescription() const override;

	CC_CONSTRUCTOR_ACCESS:
		virtual bool init() override;
		virtual void onEnter() override;
		virtual void onExit() override;

	protected:
		virtual void adaptRenderers() override;

		virtual void initRenderer() override;
		void pushToContainer(Node* renderer);
		void handleTextRenderer(const RichElementText& textInfo);
		//	void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color, GLubyte opacity);
		void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity);
		void handleCustomRenderer(Node* renderer);
		void formarRenderers();
		void addNewLine();

		bool onTouchBegan(Touch *touch, Event *unusedEvent);
		void onTouchEnded(Touch *touch, Event *unusedEvent);

		CC_SYNTHESIZE(int, _touchPriority, TouchPriority);
	protected:
		bool _formatTextDirty;
		Vector<RichElement*> _richElements;
		std::vector<Vector<Node*>*> _elementRenders;
		std::map<Node*, std::function<void(std::string)> > _touchDelegate;//定义node对应的事件
		float _leftSpaceWidth;
		float _verticalSpace;

	};

}

NS_CC_END

#endif /* defined(__RICHUI_H__) */