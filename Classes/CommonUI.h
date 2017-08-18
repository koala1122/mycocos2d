
//
//  CommonUI.h
//  MyGame
//
//  Created by mac on 2017/8/3.
//
//

#ifndef CommonUI_h
#define CommonUI_h

#define Screen_Width Director::getInstance()->getWinSize().width
#define Screen_Height Director::getInstance()->getWinSize().height

//#define ORIGINX Director::getInstance()->getWinSize().x
//#define ORIGINY Director::getInstance()->getVisibleOrigin().y

//#define Screen_Width Director::getInstance()->getVisibleSize().width
//#define Screen_Height Director::getInstance()->getVisibleSize().height
#define ORIGINX Director::getInstance()->getVisibleOrigin().x
#define ORIGINY Director::getInstance()->getVisibleOrigin().y
#endif /* CommonUI_h */
