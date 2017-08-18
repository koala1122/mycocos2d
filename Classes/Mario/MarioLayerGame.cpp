#include "MarioLayerGame.h"
#include "LayerMenu.h"
#include "MenuCtrl.h"
#include "LayerStart.h"
#include "Item.h"
int LayerGame::_idx;

LayerGame* LayerGame::create(int idx)
{
	LayerGame*ret = new LayerGame;
	ret->init(idx);
	ret->autorelease();
	return ret;
}

void LayerGame::loadResource()
{
	// picture, music
	static const char* picfiles[] = {
		"about_normal.png",
		"about_select.png",
		"AB_normal.png",
		"AB_select.png",
		"allow_walkLeft.png",
		"allow_walkRight.png",
		"arrow.png",
		"arrowActionL.png",
		"arrowActionR.png",
		"arrowBroken.png",
		"arrowBullet.png",
		"arrow_die.png",
		"axe.png",
		"backA.png",
		"backB.png",
		"background.png",
		"backKeyImage.png",
		"backKeyLeft.png",
		"backKeyRight.png",
		"backToMenu.png",
		"battery.png",
		"batteryBoom1.png",
		"batteryBoom2.png",
		"batteryBoom3.png",
		"batteryBullet.png",
		"bg.png",
		"blinkcoin.png",
		"boss.png",
		"bossBullet.png",
		"brokencoin.png",
		"bulletBorder.png",
		"CloseNormal.png",
		"CloseSelected.png",
		"cloud.png",
		"coinani.png",
		"controlUI.png",
		"darkCloud.png",
		"fireActionL.png",
		"fireActionR.png",
		"fireBall.png",
		"fireLeft.png",
		"fireRight.png",
		"fire_die.png",
		"flag.png",
		"flower0.png",
		"flyFishLeft.png",
		"flyFishRight.png",
		"fps_images.png",
		"gameover.png",
		"HelloWorld.png",
		"ladder.png",
		"left.png",
		"leftright.png",
		"lighting.png",
		"Mushroom0.png",
		"music_off.png",
		"music_on.png",
		"M_n.png",
		"M_s.png",
		"newgameA.png",
		"newgameB.png",
		"nextlevel_normal.png",
		"nextlevel_select.png",
		"normal_die.png",
		"PassFailure.png",
		"PassSuccess.png",
		"princess.png",
		"quitgame_normal.png",
		"quitgame_select.png",
		"restart_n.png",
		"restart_s.png",
		"resume_n.png",
		"resume_s.png",
		"retry_normal.png",
		"retry_select.png",
		"rewardMushroomSet.png",
		"right.png",
		"select_n.png",
		"select_s.png",
		"Setting_n.png",
		"setting_s.png",
		"Set_Menu.png",
		"Set_Music.png",
		"set_n.png",
		"set_s.png",
		"shanshuodecoin.png",
		"singleblock.png",
		"sliderProgress.png",
		"sliderTrack.png",
		"smallWalkLeft.png",
		"smallWalkRight.png",
		"small_die.png",
		"sound_effect_off.png",
		"sound_effect_on.png",
		"startgame_normal.png",
		"startgame_select.png",
		"superMarioMap.png",
		"switchBg.png",
		"Tools.png",
		"tortoise0.png",
		"walkLeft.png",
		"WalkLeft_fire.png",
		"walkRight.png",
		"WalkRight_fire.png",
	};
	static const char* musicfile[] =
	{
		"EatCoin.wma",
	};
	
	// 加载声音文件
	int musicfilecount = sizeof(musicfile) / sizeof(*musicfile);
	for (int i = 0; i < musicfilecount; ++i)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(musicfile[i]);
	}

	// 加载图片，只将图片加载到纹理缓存
	_loadFileCount = 0;
	_totalfile = sizeof(picfiles) / sizeof(*picfiles);
	for (int i = 0; i < _totalfile; ++i)
	{
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(picfiles[i]);
//        TextureCache::sharedTextureCache()->addImageAsync(picfiles[i], callfuncO_selector(LayerGame::loadImageCallBack), this)
//        CCTextureCache::sharedTextureCache()->addImageAsync(picfiles[i], SEL_CallFunc(LayerGame::loadImageCallBack));
//		CCTextureCache::sharedTextureCache()->addImageAsync(picfiles[i], this, callfuncO_selector(LayerGame::loadImageCallBack));
//        void (MyClass::*func)(int);
//        void (LayerGame::loadImageCallBack)(cocos2d::Texture2D *texture);
//        loadImageCallBack = &LayerGame::loadImageCallBack;
//        Director::getInstance()->getTextureCache()->addImageAsync(picfiles[i], _CALLBACK_1(LayerGame::loadImageCallBack, this));
	}

	//schedule(schedule_selector(LayerGame::CheckLoadResource));
}

void LayerGame::addCtrl()
{
	// 控制按钮的背景图片
	CCSprite* sprite = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("controlUI.png"));
	addChild(sprite);
	sprite->setPosition(ccp(0, 0));
	sprite->setAnchorPoint(ccp(0, 0));

	// 显示在菜单位置的纹理
	_textureDirNone = CCTextureCache::sharedTextureCache()->addImage("backKeyImage.png");
	_textureDirLeft = CCTextureCache::sharedTextureCache()->addImage("backKeyLeft.png");
	_textureDirRight = CCTextureCache::sharedTextureCache()->addImage("backKeyRight.png");

	_menuShow = CCSprite::createWithTexture(_textureDirNone);
	addChild (_menuShow);
	CCPoint ptmenuShowPos = ccp(70, 50);
	_menuShow->setPosition(ptmenuShowPos);

	// 定制菜单：每个帧循环都会触发的菜单
	// 菜单项是透明的，菜单的样式由别的精灵来显示
	MenuCtrl* menu = MenuCtrl::create();
	addChild(menu);         

	CCSprite* left1 = CCSprite::create();
	CCSprite* left2 = CCSprite::create();
	left1->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	left2->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	CCMenuItemSprite* left = CCMenuItemSprite::create(left1, left2, this, menu_selector(LayerGame::moveLeft));
	menu->addChild(left);

	CCSprite* right1 = CCSprite::create();
	CCSprite* right2 = CCSprite::create();
	right1->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	right2->setContentSize(CCSizeMake(_textureDirNone->getContentSize().width / 2, _textureDirNone->getContentSize().height));
	CCMenuItemSprite* right = CCMenuItemSprite::create(right1, right2, this, menu_selector(LayerGame::moveRight));
	menu->addChild(right);

	left->setPosition(ccp(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2));
	right->setPosition(ccp(ptmenuShowPos.x - winSize.width / 2, ptmenuShowPos.y - winSize.height / 2));
	Common::moveNode(left, ccp(-_menuShow->getContentSize().width / 4, 0));
	Common::moveNode(right, ccp(_menuShow->getContentSize().width / 4, 0));

	_marioDir = Common::NONE;

	// 跳跃，发射子弹，菜单
	addJumpFireMenuCtrl();
}

void LayerGame::addJumpFireMenuCtrl()
{
	CCMenu* menu = CCMenu::create();
	addChild(menu);

	CCTexture2D* textureAB_Normal = CCTextureCache::sharedTextureCache()->addImage("AB_normal.png");
	CCTexture2D* textureAB_Select = CCTextureCache::sharedTextureCache()->addImage("AB_select.png");
	CCSprite* jumpNormal = CCSprite::createWithTexture(textureAB_Normal);
	CCSprite* jumpSelect = CCSprite::createWithTexture(textureAB_Select);
	CCMenuItemSprite* jump = CCMenuItemSprite::create(jumpNormal, jumpSelect, this, menu_selector(LayerGame::Jump));
	menu->addChild(jump);
	Common::moveNode(jump, ccp(192, -125));
}

void LayerGame::Jump(CCObject*)
{
	if (_mario->_autoRun) return;

	_mario->jump();
}

void LayerGame::moveLeft(CCObject*)
{
	_menuShow->setTexture(this->_textureDirLeft);
	_marioDir = Common::LEFT;
}

void LayerGame::moveRight(CCObject*)
{
	_menuShow->setTexture(this->_textureDirRight);
	_marioDir = Common::RIGHT;
}

void LayerGame::onEnter()
{
	CCLayer::onEnter();
	Item::_itemReward = CCArray::create();
	Item::_itemReward->retain();
}

void LayerGame::onExit()
{
	CCLayer::onExit();
	Item::_itemReward->release();
}

void LayerGame::startGame()
{
	// 加载地图
	_map = CCTMXTiledMap::create(Common::format(_idx + 1, "MarioMap", ".tmx"));
	addChild(_map);
	Common::moveNode(_map, ccp(0, winSize.height - _map->getContentSize().height));

	// 加载蘑菇怪资源
	{
		CCAnimation* animation = Common::CreateAnimation("Mushroom0.png", 0, 1, 16, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "MushroomMoving");
		CCSpriteFrame* dead1 = Common::getSpriteFrame("Mushroom0.png", 2, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(dead1, "MushroomDead1");
		CCSpriteFrame* dead2 = Common::getSpriteFrame("Mushroom0.png", 3, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(dead2, "MushroomDead2");
	}

	// 加载乌龟动画资源
	{
		CCAnimation* animation1 = Common::CreateAnimation("tortoise0.png", 2, 3, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, "TortoiseMoveLeft");
		CCAnimation* animation2 = Common::CreateAnimation("tortoise0.png", 4, 5, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, "TortoiseMoveRight");
		CCAnimation* animation3 = Common::CreateAnimation("tortoise0.png", 8, 9, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation3, "TortoiseDead");

		CCAnimation* animation4 = Common::CreateAnimation("tortoise0.png", 0, 1, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation4, "TortoiseFlyLeft");
		CCAnimation* animation5 = Common::CreateAnimation("tortoise0.png", 6, 7, 18, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation5, "TortoiseFlyRight");
	}

	// Flower资源
	{
		CCAnimation* animation = Common::CreateAnimation("flower0.png", 0, 1, 16, 0.4f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "FlowerShow");
	}
	// MushroomReward
	{
		CCSpriteFrame* frame = Common::getSpriteFrame("rewardMushroomSet.png", 0, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MushroomReward");
	}

	{
		CCSpriteFrame* frame = Common::getSpriteFrame("rewardMushroomSet.png", 1, 16);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "MushroomAddLife");
	}

	// flyfish动画
	{
		CCAnimation* animation1 = Common::CreateAnimation("flyFishLeft.png", 0, 5, 16, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, "FlyFishLeft");
		CCAnimation* animation2 = Common::CreateAnimation("flyFishRight.png", 0, 5, 16, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, "FlyFishRight");
	}

	// boss动画
	{
		CCAnimation* animation1 = Common::CreateAnimation("boss.png", 0, 3, 32, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, "BossWalkLeft");
		CCAnimation* animation2 = Common::CreateAnimation("boss.png", 4, 7, 32, 0.05f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, "BossWalkRight");
	}

	// 增加控制按钮
	addCtrl();

	// 移动马里奥
	schedule(schedule_selector(LayerGame::moveMario));

	// 加载地图对象元素
	_mario = Mario::create();

	Item::_bridge = NULL;

	CCTMXObjectGroup* objGroup = _map->objectGroupNamed("objects");
	ValueVector objs = objGroup->getObjects();
	Value* obj;
//	CCARRAY_FOREACH(objs, obj)
//    int count = objs.size();
//    for (int i = 0; i < count;i++)
    for (auto obj = objs.cbegin(); obj != objs.cend(); obj++)
	{
//		CCDictionary* dict = (CCDictionary*)obj;
//		const CCString* x = dict->valueForKey("x");
//		const CCString* y = dict->valueForKey("y");
////		const CCString* type = dict->valueForKey("type");
//        ValueMap* dict = (ValueMap*)obj;
//        const CCString* x = dict->;
//        const CCString* y = obdictj->valueForKey("y");
//        const CCString* type = dict->valueForKey("type");
//        if (type->_string == "BirthPoint")
//		{
//			// 创建mario
//			_mario->setPosition(ccp(x->intValue(), y->intValue() - _map->getTileSize().height));
//			_mario->setAnchorPoint(ccp(0, 0));
//			_map->addChild(_mario);
//		}
//		else
//		{
//			Item* item = Item::create(dict);
//			
//			if (item)
//			{
//				item->_mario = _mario;
//			//	_items->addObject(item);
//				_map->addChild(item);
//			}
//		}
	}


	schedule(schedule_selector(LayerGame::checkMarioDie));
	//启动定时器来检测Mario是不是碰到旗杆
	schedule(schedule_selector(LayerGame::checkMarioTouchPole));

	if (Mario::_life == 0) Mario::_life = 3;
}

// 检查mario是否碰到旗杆
void LayerGame::checkMarioTouchPole(float)
{
	CCRect rcMario = _mario->boundingBox();
	CCPoint pt = ccp(rcMario.getMaxX()-8, rcMario.getMaxY());
	CCPoint ptInMap = Common::Point2Tile(_map, pt);
	CCTMXLayer* layer = _map->layerNamed("flagpole");

	if (ptInMap.y >= _map->getMapSize().height) return;
	if (ptInMap.y < 0) return;

	// 碰到旗杆了
	if (layer->tileGIDAt(ptInMap) != 0)
	{
		// autoRun第一阶段
		_mario->autoRun();
		unschedule(schedule_selector(LayerGame::checkMarioTouchPole));
	}
}

void LayerGame::checkMarioDie(float)
{
	// 检查Mario的脑袋是不是出了地图下外
	CCRect rc = _mario->boundingBox();
	if (rc.getMaxY() < 0)
		GameOver();
}

#if 0
void LayerGame::CheckLoadResource(float)
{
	if (_loadFileCount == _totalfile)
	{
		_bar->removeFromParent();
		startGame();
		unschedule(schedule_selector(LayerGame::CheckLoadResource));
	}
}
#endif

void LayerGame::loadImageCallBack(cocos2d::Texture2D *texture)
{
	_loadFileCount++;
	_bar->setPercentage((_loadFileCount)*100.0f / _totalfile);

	if (_loadFileCount == _totalfile)
	{
		_bar->removeFromParent();
		startGame();
	}
}

bool LayerGame::init(int idx)
{
	CCLayer::init();

	// 地图的编号
	_idx = idx;
//	_items = CCArray::create();
//	_items->retain();

	// 创建进度条
	_bar = ProgressBar::create("sliderTrack.png", "sliderProgress.png");
	addChild(_bar);
	_bar->setPosition(winSize.width / 2, winSize.height / 2);
	
	// 加载资源
	loadResource();

	// 可以再加些图片丰富界面

	return true;
}

void LayerGame::moveMario(float dt)
{
	if (_mario->_autoRun) return;

#ifdef WIN32
	short key;

	key = GetKeyState('F');
	if (key < 0) _marioDir = Common::RIGHT;

	key = GetKeyState('D');
	if (key < 0) _marioDir = Common::LEFT;

	key = GetKeyState('J');
	if (key < 0)_mario->jump();

#endif

	if (_marioDir == Common::LEFT)
	{
		_marioDir = Common::NONE;
		_mario->moveLeft(dt);
	}
	else if (_marioDir == Common::RIGHT)
	{
		_marioDir = Common::NONE;
		_mario->moveRight(dt);
	}
	else
	{
		_menuShow->setTexture(this->_textureDirNone);
		_mario->stop();
	}

	_mario->moveUp(dt);
	_mario->moveDown(dt);
}


void LayerGame::GameOver()
{
	Mario::_life -= 1;
	if (Mario::_life == 0)
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerStart::create()));
	else
		CCDirector::sharedDirector()->replaceScene(Common::scene(LayerGame::create(_idx)));
}