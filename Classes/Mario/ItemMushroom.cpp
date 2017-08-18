#include "ItemMushroom.h"
#include "Mario.h"

ItemMushroom* ItemMushroom::create(CCDictionary* dict)
{
	ItemMushroom* ret = new ItemMushroom;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemMushroom::init(CCDictionary* dict)
{
	Item::init();
	_type = Item::IT_mushroom;

	setPositionByProperty(dict);

	// ͼƬ
	// setDisplayFrameWithAnimationName("MushroomMoving", 0);

	_dir = Common::LEFT;
	_speed = 50;
	_speedAcc = _speedDown = 10;
	_isDead = false;

	// ����
	this->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("MushroomMoving"))));
	
	return true;
}

bool ItemMushroom::canMoveLeft(float dt)
{
	// �ж�mario�������ƶ�֮���ǲ��ǵ��˵�ͼ����
	CCRect rcItem = boundingBox();
	CCPoint ptItem = ccp(rcItem.getMinX(), rcItem.getMinY());
	CCTMXTiledMap* map = getMap();
	CCPoint ptItemInWorld = map->convertToWorldSpace(ptItem);
	if (ptItemInWorld.x - dt*_speed < 0) // - dt*_speed��ʾ�ƶ����ǲ��ǳ�ȥ�ˣ������ǵ�ǰ�Ѿ���ȥ��
		return true;

	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMinX() - dt*_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMinX() - dt*_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMinX() - dt*_speed, rcItem.getMaxY());

	// ����ת������ptת���ɵ�ͼ��������,Ȼ���ȡgid���ж�gid�ǲ��Ǳ��赲
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height)
			continue;
		if (pt[i].y < 0) 
			continue;

		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// ˮ�ܡ�שͷ���ذ�
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// �Զ��仯����
				_dir = Common::RIGHT;
				return false;
			}
		}
	}

	return true;
}

bool ItemMushroom::canMoveRight(float dt)
{
	CCRect rcItem = boundingBox();
	CCTMXTiledMap* map = getMap();
	CCPoint pt[3];
	pt[0] = ccp(rcItem.getMaxX() + dt*_speed, rcItem.getMidY());
	pt[1] = ccp(rcItem.getMaxX() + dt*_speed, rcItem.getMinY());
	pt[2] = ccp(rcItem.getMaxX() + dt*_speed, rcItem.getMaxY());

	// ����ת������ptת���ɵ�ͼ��������,Ȼ���ȡgid���ж�gid�ǲ��Ǳ��赲
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].y >= map->getContentSize().height)
			continue;
		if (pt[i].y < 0) continue;

		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// ˮ�ܡ�שͷ���ذ�
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// �Զ��任����
				_dir = Common::LEFT;
				return false;
			}
		}
	}

	return true;
}

bool ItemMushroom::canMoveDown(float dt)
{
	// ���Ģ���������ˣ�����movedown
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


	// ����ת������ptת���ɵ�ͼ��������,Ȼ���ȡgid���ж�gid�ǲ��Ǳ��赲
	for (int i = 0; i < 3; ++i)
	{
		if (pt[i].x <= 0)
			continue;

		CCPoint ptTile = Common::Point2Tile(map, pt[i]);
		// ˮ�ܡ�שͷ���ذ�
		static const char* layerName[3] = { "block", "pipe", "land" };
		for (int j = 0; j < 3; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
				// ΢��
				CCPoint ptLB = Common::Tile2PointLB(map, ptTile + ccp(0, -1));
				this->setPositionY(ptLB.y);

				return false;
			}
		}
	}

	return true;
}

bool ItemMushroom::canMove(float dt)
{
	// Ģ���������ˣ������ƶ�
	if (_isDead) return false;

	// Ģ����û�н�����Ұ��Χ��Ҳ�����ƶ�
	if (!isLeftInWindow())
	{
		return false;
	}

	// ���ݷ����پ���ȷ��
	if (_dir == Common::LEFT)
		return canMoveLeft(dt);

	return canMoveRight(dt);
}

void ItemMushroom::moveDown(float dt)
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

void ItemMushroom::move(float dt)
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

	// Ģ���ֵĻ��գ���������λ�ú�Mario��λ�ã�������һ�����ڵľ��룬������mario��ߣ�Ȼ���Ҫ����
	if (isFarAwayFromMario())
	{
		removeFromParent();
	}
}

void ItemMushroom::collision()
{
	// ��ֹ������ײ���
	if (_isDead) return;

	CCRect rcMario = _mario->boundingBox();
	CCRect rcItem = this->boundingBox();

	// �ж���ײ���
	if (rcMario.intersectsRect(rcItem))
	{
		// Ģ����������������1)Mario�ڷɣ�2��Mario���½���3��Mario��λ�ñ�Ģ���ָߣ��߰����λ
		if (_mario->_bFly && _mario->_speedUp <= 0 && rcMario.getMinY() > rcItem.getMaxY() - rcItem.size.height / 2)
		{
			this->stopAllActions();
			this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MushroomDead1"));
			_isDead = true;
			// CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(ItemMushroom::removeFromParent));
			this->runAction(CCMoveBy::create(3.0, ccp(0, -winSize.height)));
		}
		else
		{
			_mario->Die(false);

		}
	}
}