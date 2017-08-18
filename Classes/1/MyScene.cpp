//
//  MyScene.cpp
//  MyGame
//
//  Created by mac on 2017/8/4.
//
//

#include "MyScene.hpp"
#include "MyLayer.h"
bool MyScene::init()
{
    Scene::init();
    MyLayer *layer = MyLayer::create();
    this->addChild(layer);
    return true;
    
}