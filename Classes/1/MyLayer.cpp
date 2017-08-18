#include "MyLayer.h"
#include "CommonUI.h"
USING_NS_CC;
//MyLayer *MyLayer::create()
//{
//	MyLayer * pRet = new MyLayer();
//	if (pRet && pRet->init())
//	{
//		pRet->autorelease();
//	}
//	else
//	{
//		delete pRet;
//		pRet = NULL;
//	}
//	return pRet;
//}
bool MyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

//	Size winSize = Director::getInstance()->getWinSize();
//	Sprite * spr = Sprite::create("CloseSelected.png");
//	spr->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
//	addChild(spr);
    
    touchPoint = Point::ZERO;
    objDraw = DrawNode::create();
    this->addChild(objDraw);
    
    Size winSize = Director::getInstance()->getWinSize();
    spr = Sprite::create("anchor3.png");
//    spr->setAnchorPoint(Vec2(1,1));
//
    spr->setIgnoreAnchorPointForPosition(true);
    spr->setPosition(winSize.width / 2,winSize.height / 2);
//    spr->setPosition(Vec2(winSize.width / 2,winSize.height / 2));
//    spr->setScale(5);
    addChild(spr);
    
//    schedule(<#SEL_SCHEDULE selector#>, <#float interval#>, <#unsigned int repeat#>, <#float delay#>)
//    schedule(schedule_selector(MyLayer::mySchedule), 1);
	return true;

}
Scene *MyLayer::scene()
{
	Scene * scene = Scene::create();
	MyLayer * layer = MyLayer::create();
    log("x = %f, y = %f", layer->getPositionX(), layer->getPositionY());
//    layer->setIgnoreAnchorPointForPosition(false);
    
	scene->addChild(layer);
	return scene;
}

void MyLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) 
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    ccDrawColor4B(255, 0, 0, 255);
//    
//    ccDrawLine(Vec2(0, winSize.height / 2), Vec2(winSize.width, winSize.height / 2));
//    ccDrawLine(Vec2(winSize.width / 2, 0), Vec2(winSize.width/2,winSize.height));

    objDraw->clear();
//    objDraw->drawSegment(Vec2(0, winSize.height / 2), Vec2(winSize.width, winSize.height / 2), 1, Color4F(0, 1, 0, 1));
//    objDraw->drawSegment(Vec2(winSize.width / 2, 0), Vec2(winSize.width/2,winSize.height), 1, Color4F(0, 1, 0, 1));
    objDraw->drawSegment(Vec2(0, Screen_Height / 2), Vec2(Screen_Width, Screen_Height / 2), 1, Color4F(0, 1, 0, 1));
    objDraw->drawSegment(Vec2(Screen_Width / 2, 0), Vec2(Screen_Width / 2, Screen_Height), 1, Color4F(0, 1, 0, 1));
    Layer::draw(renderer, transform, flags);
    }

void MyLayer::mySchedule(float dt)
{
    static float ro = 0;
    ro += 30;
    spr -> setRotation(ro);
}

