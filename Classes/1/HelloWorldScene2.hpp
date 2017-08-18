//
//  HelloWorldScene2.hpp
//  MyGame
//
//  Created by mac on 2017/8/3.
//
//

#ifndef HelloWorldScene2_hpp
#define HelloWorldScene2_hpp

#include <stdio.h>
#include "cocos2d.h"

class HelloWorld2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld2);
};
#endif /* HelloWorldScene2_hpp */
