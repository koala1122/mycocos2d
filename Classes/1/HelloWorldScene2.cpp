//
//  HelloWorldScene2.cpp
//  MyGame
//
//  Created by mac on 2017/8/3.
//
//

#include "HelloWorldScene2.hpp"

USING_NS_CC;
Scene* HelloWorld2::createScene()
{
    return HelloWorld2::create();
}

bool HelloWorld2::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld2::menuCloseCallback, this));
    closeItem->setPosition(Vec2(
                                origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                origin.y + closeItem->getContentSize().height / 2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = Label::createWithTTF("HELLO WORLD", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height / 2));
    
    this->addChild(label);
    
    auto sprite = Sprite::create("HelloWorld.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite,0);
    
    return true;
}

void HelloWorld2::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORL == CC_PLATFORM_IOS)
    exit(0);
#endif
}