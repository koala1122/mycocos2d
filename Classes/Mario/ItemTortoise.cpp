#include "ItemTortoise.h"
#include "Mario.h"
ItemTortoise* ItemTortoise::create(CCDictionary* dict)
{
	ItemTortoise* ret = new ItemTortoise;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemTortoise::init(CCDictionary* dict)
{
	Item::init();
	_type = Item::IT_tortoise;

	setPositionByProperty(dict);



	// 
	// setDisplayFrameWithAnimationName("MushroomMoving", 0);

	_dir = Common::LEFT;
	_speed = 50;
	_speedAcc = _speedDown = 10;
	_isDead = false;

	this->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveLeft"))));


	_isGod = false;
	_isSleep = false;
	_isCrazy = false;

	return true;
}

bool ItemTortoise::canMoveLeft(float dt)
{
	// 判断mario的向左移动之后，是不是到了地图外面
	CCRect rcItem = boundingBox();
	CCPoint ptItem = ccp(rcItem.getMinX(), rcItem.getMinY());
	CCTMXTiledMap* map = getMap();
	CCPoint ptItemInWorld = map->convertToWorldSpace(ptItem);
	if (ptItemInWorld.x - dt*_speed < 0) // - dt*_speed表示移动后是不是出去了，而不是当前已经出去了
		return true;

	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMinX() - dt*_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMinX() - dt*_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMinX() - dt*_speed, rcItem.getMaxY());

	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height)
			continue;
		if (pt[i].y < 0) 
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
				// 自动变化方向
				_dir = Common::RIGHT;
				if (!_isCrazy)
				{
					stopAllActions();
					this->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveRight"))));
				}
				return false;
			}
		}
	}

	return true;
}

bool ItemTortoise::canMoveRight(float dt)
{
	CCRect rcItem = boundingBox();
	CCTMXTiledMap* map = getMap();
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMaxX() + dt*_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMaxX() + dt*_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMaxX() + dt*_speed, rcItem.getMaxY());

	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height)
			continue;
		if (pt[i].y < 0) continue;

		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// 水管、砖头，地板
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// 自动变换方向
				_dir = Common::LEFT;
				if (!_isCrazy)
				{
					stopAllActions();
					this->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveLeft"))));
				}
				return false;
			}
		}
	}

	return true;
}

bool ItemTortoise::canMoveDown(float dt)
{
	// 如果蘑菇怪死掉了，则不能movedown
	if (_isDead) return false;

	CCRect rcItem = boundingBox();
	CCTMXTiledMap* map = getMap();
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMidX(), rcItem.getMinY() - dt*_speedDown);
	pt[1] = ccp(rcItem.getMinX(), rcItem.getMinY() - dt*_speedDown);
	pt[2] = ccp(rcItem.getMaxX(), rcItem.getMinY() - dt*_speedDown);

	if (pt[0].y >= map->getContentSize().height)
		return true;
	if (pt[0].y <= 0)
		return true;


	// 坐标转换，将pt转化成地图格子坐标,然后获取gid，判断gid是不是被阻挡
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].x <= 0)
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
				// 微调
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile + ccp(0, -1));
				this->setPositionY(ptLB.y);

				return false;
			}
		}
	}

	return true;
}

bool ItemTortoise::canMove(float dt)
{
	// 蘑菇怪死掉了，不能移动
	if (_isDead) return false;
	if (_isSleep) return false;

	// 蘑菇怪没有进入视野范围，也不能移动
	if (!isLeftInWindow())
	{
		return false;
	}

	// 根据方向，再具体确定
	if (_dir == Common::LEFT)
		return canMoveLeft(dt);

	return canMoveRight(dt);
}

void ItemTortoise::moveDown(float dt)
{
	if (canMoveDown(dt))
	{
		Common::moveNode(this, ccp(0, -dt*_speedDown));
		_speedDown += _speedAcc;
	}
	else
	{
		_speedDown = 10;
	}
}

void ItemTortoise::move(float dt)
{
	if (canMove(dt))
	{
		if (_dir == Common::LEFT)
		{
			Common::moveNode(this, ccp(-dt*_speed, 0));
		}
		else
		{
			Common::moveNode(this, ccp(dt*_speed, 0));
		}
	}

	moveDown(dt);

	// 蘑菇怪的回收，如果怪物的位置和Mario的位置，超出了一个窗口的距离，并且在mario左边，然后就要回收
	if (isFarAwayFromMario())
	{
		removeFromParent();
	}
}

void ItemTortoise::collision()
{
	// 防止持续碰撞检测
	if (_isDead) return;
	if (_isGod) return;

	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = this->boundingBox();

	// 判断碰撞检测
	if (rcMario.intersectsRect(rcItem))
	{
		if(_isSleep == false)
		{
			// 蘑菇怪死亡的条件，1)Mario在飞，2）Mario在下降，3）Mario的位置比蘑菇怪高，高半个身位
			if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
			{
				stopAllActions();
				this->runAction(CCRepeatForever::create(
					CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseDead"))));

				// 无敌一段时间
				_isGod = true;
				scheduleOnce(schedule_selector(ItemTortoise::unsetGodmode), .5f);

				// 过一段时间要复活
				scheduleOnce(schedule_selector(ItemTortoise::revive), 10.0f);

				_isSleep = true;
				_speed = 0;

				// 微调位置，让Mario和sleep状态的乌龟不再冲突
				if (_mario->getPositionX() > getPositionX())
				{
					setPositionX(_mario->getPositionX() - 18);
				}
				else
				{
					setPositionX(_mario->getPositionX() + 18);
				}
			}
			else
			{
				// Mario死亡
				_mario->Die(false);
			}

			return;
		}

		// 在乌龟处于_isSleep状态下，如果和Mario冲突了，，，
		else
		{
			_speed = 200;
			_isCrazy = true;
			_isSleep = false;
			if(_mario->getPositionX() < getPositionX())
			{
				_dir = Common::RIGHT;
			}
			else
			{
				_dir = Common::LEFT;
			}

			// 取消复活
			unschedule(schedule_selector(ItemTortoise::revive));
		}
#if 0
		// 蘑菇怪死亡的条件，1)Mario在飞，2）Mario在下降，3）Mario的位置比蘑菇怪高，高半个身位
		if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
		{

			this->stopAllActions();
			this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MushroomDead1"));
			_isDead = true;
			// CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ItemTortoise::removeFromParent));
			this->runAction(CCMoveBy::create(3.0, ccp(0, -winSize.height)));

		}
#endif
	}
}