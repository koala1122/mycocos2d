#include "Mario.h"
#include "Item.h"
#include "MarioLayerGame.h"

int Mario::_life = 0;

bool Mario::init()
{
	// 设置脸朝右的帧
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("smallWalkRight.png");
	CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, texture->getContentSize().width / 11, 
		texture->getContentSize().height));
	CCSprite::initWithSpriteFrame(frame);

	// 设置mario的zorder，不设置会被山覆盖
	setZOrder(100);

	// 属性的初始化
	_speed = 200;
	_speedUp = 0;
	_speedAcc = 10;
	_speedDown = _speedAcc;
	_bGodMode = false;
	_dead = false;
	

	_dirRun = Common::NONE;
	_dirFace = Common::RIGHT;
	//_life = 3;
	_isBig = false;
	_canFire = false;
	_bFly = false;
	_autoRun = false;
	_flagRunAction = false;
	_onLadder = false;

	{
		// mario用到的动画
		CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("smallWalkLeft.png", 0, 9, 14, 0.05f), "SmallWalkLeft");
		CCAnimationCache::sharedAnimationCache()->addAnimation(
			Common::CreateAnimation("smallWalkRight.png", 0, 9, 14, 0.05f), "SmallWalkRight");

		CCAnimationCache::sharedAnimationCache()->addAnimation(
			Common::CreateAnimation("small_die.png", 0, 6, 16, 0.05f), "smalldie");

		

		// Mario用到的帧
		frame = Common::getSpriteFrame("smallWalkLeft.png", 10, 14);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "SmallJumpLeft");

		frame = Common::getSpriteFrame("smallWalkRight.png", 10, 14);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "SmallJumpRight");
	}

	{
		// mario用到的动画
		CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("walkLeft.png", 0, 9, 18, 0.05f), "BigWalkLeft");
		CCAnimationCache::sharedAnimationCache()->addAnimation(Common::CreateAnimation("walkRight.png", 0, 9, 18, 0.05f), "BigWalkRight");

		// Mario用到的帧
		frame = Common::getSpriteFrame("walkLeft.png", 10, 18);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "BigJumpLeft");

		frame = Common::getSpriteFrame("walkRight.png", 10, 18);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, "BigJumpRight");
	}
	return true;
}

CCTMXTiledMap* Mario::getMap()
{
	return (CCTMXTiledMap*)getParent();
}

bool Mario::canMoveLeft(float dt)
{
	if (_dead) return false;

	// 判断mario的向左移动之后，是不是到了地图外面
	CCRect rcMario = boundingBox();
	CCPoint ptMario = ccp(rcMario.getMinX(), rcMario.getMinY());
	CCTMXTiledMap* map = getMap();
	CCPoint ptMarioInWorld = map->convertToWorldSpace(ptMario);
	if (ptMarioInWorld.x - dt*_speed < 0) // - dt*_speed表示移动后是不是出去了，而不是当前已经出去了
		return false;

	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMinX() - dt*_speed, rcMario.getMidY());
	pt[1] = ccp(rcMario.getMinX() - dt*_speed, rcMario.getMinY());
	pt[2] = ccp(rcMario.getMinX() - dt*_speed, rcMario.getMaxY());

	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height)
			continue;

		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头，地板
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				return false;
			}
		}

	}

	return true;
}
bool Mario::canMoveRight(float dt)
{
	if (_dead) return false;

	CCRect rcMario = boundingBox();
	CCTMXTiledMap* map = getMap();
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMaxX() + dt*_speed, rcMario.getMidY());
	pt[1] = ccp(rcMario.getMaxX() + dt*_speed, rcMario.getMinY());
	pt[2] = ccp(rcMario.getMaxX() + dt*_speed, rcMario.getMaxY());

	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height)
			continue;

		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头，地板
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				return false;
			}
		}
	}

	return true;
}

bool Mario::canMoveDown(float dt)
{
	if (_dead) return false;
	//if (_autoRun) return false;
	if (_onLadder) return false;

	CCRect rcMario = boundingBox();
	CCTMXTiledMap* map = getMap();
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMidX(), rcMario.getMinY() - dt*_speedDown);
	pt[1] = ccp(rcMario.getMinX(), rcMario.getMinY() - dt*_speedDown);
	pt[2] = ccp(rcMario.getMaxX(), rcMario.getMinY() - dt*_speedDown);

	if (pt[0].y >= map->getContentSize().height)
		return true;

	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头，地板
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// 微调
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile+ccp(0, -1));
				this->setPositionY(ptLB.y);

				// 在自动运行情况下，
				int dist = abs(Item::_Flag->getPositionX() - getPositionX());
				CCLog("canMoveDown return false _autoRun is %d, dist=%d", (int)_autoRun, dist);
				if (_autoRun && !_flagRunAction)
				{
						_flagRunAction = true;
						CCPoint ptFlagEnd = Common::Tile2PointLB(map, ptTile);
						Item::_Flag->runAction(CCMoveTo::create(1, ccp(Item::_Flag->getPositionX(), ptFlagEnd.y + 16)));
					
				}
				
				return false;
			}
		}
	}

	return true;
}

bool Mario::canMoveUp(float dt)
{
	if (_dead) return false;
	//if (_autoRun) return false;

	CCRect rcMario = boundingBox();
	CCTMXTiledMap* map = getMap();
	CCPoint pt[3];
	pt[0] = ccp(rcMario.getMidX(), rcMario.getMaxY() + dt*_speedUp);
	pt[1] = ccp(rcMario.getMinX(), rcMario.getMaxY() + dt*_speedUp);
	pt[2] = ccp(rcMario.getMaxX(), rcMario.getMaxY() + dt*_speedUp);

	if (pt[0].y >= map->getContentSize().height)
		return true;

	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头，地板
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// 微调
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile+ccp(0, 1));
				this->setPositionY(ptLB.y);
				
				// 顶到东西了
				Hit(layerName[j], gid, ptTile);

				return false;
			}
		}
	}

	return true;
}

void Mario::Hit(const std::string&layername, int gid, CCPoint ptTile)
{
	if (layername != "block") return;

	CCTMXLayer* layer = getMap()->layerNamed(layername.c_str());
	CCSprite* sprite = layer->tileAt(ptTile);
	
	CCJumpBy* jump = CCJumpBy::create(0.1f, ccp(0, 0), 20, 1);
	CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(Mario::wakeupMushroomReward));

	sprite->runAction(CCSequence::createWithTwoActions(jump, callfunc));
}

// 检查转头中是否有蘑菇
void Mario::wakeupMushroomReward(CCNode* sprite)
{
	// 唤醒隐藏的蘑菇奖赏
	CCObject* obj;
	CCARRAY_FOREACH(Item::_itemReward, obj)
	{
		Item* item = (Item*)obj;
		CCRect rcBlock = sprite->boundingBox();
		rcBlock.origin = rcBlock.origin + ccp(4, 4);
		rcBlock.size.width /= 2;
		rcBlock.size.height /= 2;
		if (item->boundingBox().intersectsRect(rcBlock))
		{
			item->wakeup();
			break;
		}
	}
}

void Mario::moveLeft(float dt)
{
	if (_dirRun != Common::LEFT)
	{
		_dirRun = Common::LEFT;
		_dirFace = Common::LEFT;
		updateStatus();
	}

	if (!canMoveLeft(dt))
		return;

	Common::moveNode(this, ccp(-dt*_speed, 0));
}
void Mario::moveRight(float dt)
{
	if (_dirRun != Common::RIGHT)
	{
		_dirRun = Common::RIGHT;
		_dirFace = Common::RIGHT;
		updateStatus();
	}

	if (!canMoveRight(dt))
		return;

	Common::moveNode(this, ccp(dt*_speed, 0));

	// 判断Mario已经到了地图最右边，不需要卷动地图
	CCPoint ptLastInMap = ccp(getMap()->getContentSize().width, 0);
	CCPoint ptLastInWorld = getMap()->convertToWorldSpace(ptLastInMap);
	if (ptLastInWorld.x <= winSize.width) // 地图最后一个点在窗口内
		return;

	// 卷动地图
	// 如果mario位置超过了地图的一半，就应该卷动地图
	// mario的在世界坐标中的x坐标，超过了窗口的一半
	CCNode* map = getParent();
	CCPoint ptWorld = map->convertToWorldSpace(this->getPosition());
	if (ptWorld.x > winSize.width / 2)
	{
		Common::moveNode(map, ccp(-dt*_speed, 0));
	}
}

void Mario::moveUp(float dt)
{
	if (_speedUp <= 0)
	{
		return;
	}

	if (!canMoveUp(dt))
	{
		// 反弹效果
		_speedDown = _speedUp;
		_speedUp = 0; // 不继续上升了
		return;
	}

	Common::moveNode(this, ccp(0, dt*_speedUp));
	_speedUp -= _speedAcc;
	
//	_speedDown = _speedUp;
}

void Mario::moveDown(float dt)
{
	if (_speedUp <= 0)
	{
		if (canMoveDown(dt))
		{
			
			if (_bFly == false)
			{
				_bFly = true;
				updateStatus();
			}

			Common::moveNode(this, ccp(0, -dt*_speedDown));
			_speedDown += _speedAcc;
		}
		else
		{
			if (_bFly)
			{
				
				_bFly = false;
				_speedDown = _speedAcc;
				updateStatus();
			}
		}
	}
}

void Mario::stop()
{
	if (_dirRun != Common::NONE)
	{
		_dirRun = Common::NONE;
		updateStatus();
	}
}

void Mario::jump()
{
	if (_bFly)
		return;
	
	if (this->_dead)
		return;

	_speedUp = 300;
	_bFly = true;
	updateStatus();
}

void Mario::Dead()
{
	LayerGame::GameOver();
}

void Mario::updateStatus()
{
	stopAllActions();

	if (_autoRun)
	{
		if (this->_isBig)
			this->setDisplayFrameWithAnimationName("BigWalkRight", 0);
		else
			this->setDisplayFrameWithAnimationName("SmallWalkRight", 0);

		return;
	}

	if (_dead)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("smalldie");
		CCAnimate* animate = CCAnimate::create(animation);

		CCMoveBy* moveBy = CCMoveBy::create(winSize.height/_speed, ccp(0, -winSize.height));
		CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Mario::Dead));

		CCSequence* seq = CCSequence::create(animate, moveBy, callfunc, NULL);
		runAction(seq);

		return;
		//runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BigWalkLeft"))));

	}

	if (_bFly)
	{
		if (_isBig)
		{
			if (_dirFace == Common::LEFT)
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BigJumpLeft"));
			}
			else
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BigJumpRight"));
			}
		}
		else
		{

			if (_dirFace == Common::LEFT)
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallJumpLeft"));
			}
			else
			{
				setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("SmallJumpRight"));
			}
		}
		return;
	}

	if (_isBig)
	{
		if (_dirRun == Common::LEFT)
		{
			runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BigWalkLeft"))));
			//runAction
		}
		else if (_dirRun == Common::RIGHT)
		{
			// runAction
			runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("BigWalkRight"))));
		}
		else // 静止
		{
			if (_dirFace == Common::LEFT)
			{
				this->setDisplayFrameWithAnimationName("BigWalkLeft", 0);
			}
			else
			{
				this->setDisplayFrameWithAnimationName("BigWalkRight", 0);
			}
		}
	}
	else
	{

		if (_dirRun == Common::LEFT)
		{
			runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallWalkLeft"))));
			//runAction
		}
		else if (_dirRun == Common::RIGHT)
		{
			// runAction
			runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("SmallWalkRight"))));
		}
		else // 静止
		{
			if (_dirFace == Common::LEFT)
			{
				this->setDisplayFrameWithAnimationName("SmallWalkLeft", 0);
			}
			else
			{
				this->setDisplayFrameWithAnimationName("SmallWalkRight", 0);
			}
		}

	}
}

void Mario::eatMushroom(Item::ItemType type)
{
	if (type == Item::IT_mushroomReward)
	{
		if (!_isBig)
		{
			_isBig = true;
			updateStatus();
		}
	}
	else if (type == Item::IT_mushroomAddLife)
	{
		_life++;
	}
}

void Mario::Die(bool dead)
{
	return;

	// 掉沟里
	if (dead)
	{
		LayerGame::GameOver();
	}

	// 无敌模式下被撞一下也没关系
	if (dead == false && this->_bGodMode)
		return;

	if (dead == false && _isBig)
	{
		_isBig = false;
		updateStatus();

		// 无敌一段时间
		setGodMode(5);
		return;
	}

	_dead = true;
	updateStatus();
}