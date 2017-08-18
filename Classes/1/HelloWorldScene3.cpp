//
//  HelloWorld3.cpp
//  MyGame
//
//  Created by mac on 2017/8/3.
//
//

#include "HelloWorldScene3.hpp"
#include "CommonUI.h"

Scene* HelloWorld3::createScene()
{
    Scene *scene = Scene::create();
    
    HelloWorld3 *layer = HelloWorld3::create();
    
    scene->addChild(layer);
    return scene;
}

bool HelloWorld3::init()
{
    Layer::init();
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *psprite = Sprite::create("HelloWorld.png");
    psprite->setPosition( Screen_Width / 2, Screen_Height / 2);
//    psprite->setPosition(Vec2(Screen_Width / 2 + ORIGINX, Screen_Height /2 + ORIGINY));
//    psprite->setPosition(Vec2(Screen_Width / 2, Screen_Height / 2));
    
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    auto sprite = Sprite::create("HelloWorld.png");
//    
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(sprite,0);
    addChild(psprite, 0);
    return true;
    
}

void HelloWorld3::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORL == CC_PLATFORM_IOS)
    exit(0);
#endif
}