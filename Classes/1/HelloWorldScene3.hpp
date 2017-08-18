//
//  HelloWorld3.hpp
//  MyGame
//
//  Created by mac on 2017/8/3.
//
//

#ifndef HelloWorld3_hpp
#define HelloWorld3_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class HelloWorld3 : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    CREATE_FUNC(HelloWorld3);
    //    static HelloWorld3* create()
    //    {
    //        HelloWorld3 *pRet = new HelloWorld3();
    //        if (pRet && pRet->init()) {
    //            pRet->autorelease();
    //        } else {
    //            delete pRet;
    //            pRet = NULL;
    //        }
    //        return pRet;
    //        
    //    }
};
#endif /* HelloWorld3_hpp */
