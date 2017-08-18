#include "ItemFlower.h"
#include "Mario.h"

ItemFlower* ItemFlower::create(CCDictionary* dict)
{
	ItemFlower* ret = new ItemFlower;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemFlower::init(CCDictionary* dict)
{
	Item::init();
	_type = Item::IT_flower;

	setPositionByProperty(dict);
	Common::moveNode(this, ccp(-8, 0));
	setZOrder(0);

	_dir = Common::DOWN; // UP, DOWN
	_bShow = true; // 表现状态，就是花全部显示出来之后的状态
	_yTop = getPositionY();
	_yButtom = _yTop - 64;

	// int _yButtom = Common::Tile2PointLB(this->getMap(), ccp(0, 11)).y;
	_speed = 50;


	setDisplayFrameWithAnimationName("FlowerShow", 0);
	CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("FlowerShow"));
	runAction(CCRepeatForever::create(animate));

	// 更新显示
	updateStatus();

	return true;
}

void ItemFlower::updateStatus()
{
	//stopAllActions();
	if (_bShow)
	{
		// 启动定时器取消show
		scheduleOnce(schedule_selector(ItemFlower::unsetShow), 2.0f);
	}
}

void ItemFlower::move(float dt)
{
	if (_bShow) return;

	if (_dir == Common::DOWN)
	{
		Common::moveNode(this, ccp(0, -dt*_speed));
		// 如果向下移动到了某个地方(_yButtom)，改变方向
		if (getPositionY() <= _yButtom)
			_dir = Common::UP;

	//	CCLog("move down");
	}
	else
	{
		CCRect rcItem = this->boundingBox();
		CCPoint ptMario = _mario->getPosition();

		// 如果mario踩在花头顶，花不能上升
		if (ptMario.x > rcItem.getMinX() && ptMario.x < rcItem.getMaxX() && _mario->_bFly==false)
		{
			return;
		}

		Common::moveNode(this, ccp(0, dt*_speed));
		// 如果向上移动到了某个地方，就改变状态
		if (getPositionY() >= _yTop)
		{
			// 微调
			this->setPositionY(_yTop);
			_bShow = true;
			updateStatus();
		}
	}
}

void ItemFlower::collision()
{
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = boundingBox();
	if (rcMario.intersectsRect(rcItem))
	{
		_mario->Die(false);
	}
}