#include "ItemTortoiseRound.h"
#include "Mario.h"
ItemTortoiseRound* ItemTortoiseRound::create(CCDictionary* dict)
{
	ItemTortoiseRound* ret = new ItemTortoiseRound;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemTortoiseRound::init(CCDictionary* dict)
{
	Item::init();
	_type = Item::IT_tortoiseRound;

	setPositionByProperty(dict);
	_speed = 50;
	_roundDis = dict->valueForKey("roundDis")->intValue();

	_dir = Common::LEFT;
	_status = NORMAL;
	_rightMost = getPositionX();
	_leftMost = _rightMost - _roundDis;

	_bGodMode = false;
	updateStatus();
	
	

#if 0
	CCAnimation* animation1 = Common::CreateAnimation("tortoise0.png", 2, 3, 18, 0.4f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, "TortoiseMoveLeft");
	CCAnimation* animation2 = Common::CreateAnimation("tortoise0.png", 4, 5, 18, 0.4f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, "TortoiseMoveRight");
	CCAnimation* animation3 = Common::CreateAnimation("tortoise0.png", 8, 9, 18, 0.4f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation3, "TortoiseDead");
#endif


#if 0
	<object name = "enemy" type = "tortoise_round" x = "1664" y = "112">
		<properties>
		<property name = "roundDis" value = "64" / >
		< / properties>
		< / object>
#endif

	return true;
}

void ItemTortoiseRound::move(float dt)
{
	//return;
	if (!isLeftInWindow())
	{
		return;
	}

	if (isFarAwayFromMario())
	{ 
		removeFromParent();
		return;
	}

	if (_status == SLEEP)
		return;

	if (_status == NORMAL)
	{
		if (_dir == Common::LEFT)
		{
			Common::moveNode(this, ccp(-dt*_speed, 0));
			if (getPositionX() <= _leftMost)
			{
				_dir = Common::RIGHT;
				updateStatus();
			}
		}
		else
		{
			Common::moveNode(this, ccp(dt*_speed, 0));
			if (getPositionX() >= _rightMost)
			{
				_dir = Common::LEFT;
				updateStatus();
			}
		}
	}

	if (_status == CRAZY)
	{
		if (_dir == Common::LEFT)
		{
			if (canMoveLeft(dt))
				moveLeft(dt);
			else
				_dir = Common::RIGHT;
		}
		else
		{
			if (canMoveRight(dt))
				moveRight(dt);
			else
				_dir = Common::LEFT;
		}

		if (canMoveDown(dt))
			moveDown(dt);
	}
}

void ItemTortoiseRound::updateStatus()
{
	if (_status == NORMAL)
	{
		stopAllActions();
		CCAnimation* animation = NULL;
		if (_dir == Common::LEFT)
		{
			animation = CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveLeft");
		}
		else
		{
			animation = CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveRight");
		}
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));
	}
	else if (_status==SLEEP)
	{
		stopAllActions();
		CCAnimation* animation = NULL;
		animation = CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseDead");
		CCAnimate* animate = CCAnimate::create(animation);
		runAction(CCRepeatForever::create(animate));

		// 过一段时间恢复
		scheduleOnce(schedule_selector(ItemTortoiseRound::Recover), 10);

		// 不接受碰撞一段时间
		_bGodMode = true;
		scheduleOnce(schedule_selector(ItemTortoiseRound::unsetGodMode), .2f);

		// 微调位置
		if (_mario->getPositionX() < getPositionX())
		{
			setPositionX(_mario->getPositionX() + _mario->boundingBox().size.width + 1);
		}
		else
		{
			setPositionX(_mario->getPositionX() - boundingBox().size.width - 1);
		}
	}
	else if (_status == CRAZY)
	{
		// 禁止恢复
		unschedule(schedule_selector(ItemTortoiseRound::Recover));
		_speed = 200;
		_dir = _mario->_dirFace;
	}

}

void ItemTortoiseRound::Recover(float)
{
	_status = NORMAL;
	updateStatus();
}

void ItemTortoiseRound::collision()
{
	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = this->boundingBox();

	// 判断碰撞检测
	if (rcMario.intersectsRect(rcItem))
	{
		if (_status == NORMAL)
		{
			if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
			{
				_status = SLEEP;
				updateStatus();
			}
			else
			{

			}
		}
		else if (_status == SLEEP && !_bGodMode)
		{
			_status = CRAZY;
			updateStatus();
		}
	}
}
