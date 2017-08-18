#include "LayerMenu.h"#include "LayerStart.h"#include "MarioLayerGame.h"bool LayerMenu::init(){	CCLayer::init();    auto listener = EventListenerTouchOneByOne::create();        // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没    listener->setSwallowTouches(true);        // 触摸开始时,用调用函数的方式    listener->onTouchBegan = CC_CALLBACK_2(LayerMenu::onTouchBegan, this); // 触摸开始    //    listener->onTouchMoved = CC_CALLBACK_2(TouchExa::onTouchMoved, this); // 触摸移动    listener->onTouchEnded = CC_CALLBACK_2(LayerMenu::onTouchEnded, this); // 触摸结束    //    listener->onTouchCancelled = CC_CALLBACK_2(TouchExa::onTouchCancelled, this); // 触摸中断        // 用事件分发器给对象添加监听器,this表示本场景    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);        // ±≥æ∞Õº∆¨    CCSprite* bg = CCSprite::create("bg.png");    addChild(bg);    bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));        // πˆ∂Ø—°‘Ò    CCNode* node = CCNode::create();    for (int i = 0; i < 8; ++i)    {        CCSprite* sprite = CCSprite::create(Common::format(i + 1, "select", ".jpg"));        node->addChild(sprite);        sprite->setPosition(ccp(winSize.width / 2 + i*winSize.width, winSize.height / 2));        sprite->setTag(1000 + i);    }        ScrollView* view = ScrollView::create(winSize, node);    addChild(view);    view->setContentSize(CCSizeMake(8 * winSize.width, winSize.height));    view->setDirection(ScrollView::Direction::HORIZONTAL);//    view->setDirection(kScrollViewDirectionHorizontal);//	view->setDirection(kCCScrollViewDirectionHorizontal);	_view = view;	// Ω¯»Î”Œœ∑µƒ¥¶¿Ì	setTouchEnabled(true);	setTouchMode(kCCTouchesOneByOne);		// ∑µªÿ∞¥≈•	CCMenuItemImage* item = CCMenuItemImage::create("backA.png", "backB.png", this, menu_selector(LayerMenu::Back));	CCMenu* menu = CCMenu::createWithItem(item);	addChild(menu);	item->setPosition(ccp(winSize.width / 2 - item->getContentSize().width / 2,		item->getContentSize().height / 2 - winSize.height / 2));	return true;}void LayerMenu::Back(CCObject*){	CCDirector::sharedDirector()->replaceScene(Common::scene(LayerStart::create()));}bool LayerMenu::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){	return true;}void LayerMenu::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent){	if (isClick(pTouch))	{		CCNode* node = _view->getContainer();		CCPoint ptInNode = node->convertTouchToNodeSpace(pTouch);		for (int i = 0; i < 8; ++i)		{			CCSprite* sprite = (CCSprite*)node->getChildByTag(1000 + i);			if (sprite->boundingBox().containsPoint(ptInNode))			{				// Ω¯»Î”Œœ∑≥°æ∞				CCDirector::sharedDirector()->replaceScene(Common::scene(LayerGame::create(i)));				break;			}		}	}}bool LayerMenu::isClick(CCTouch* pTouch){	CCPoint ptStartLocation = pTouch->getStartLocation();	CCPoint ptLoacation = pTouch->getLocation();	return ptLoacation.getDistanceSq(ptStartLocation) < 25;}