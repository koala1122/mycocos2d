#include "ItemFlagPoint.h"
#include "Mario.h"
#include "ItemBoss.h"
ItemFlagPoint* ItemFlagPoint::create(CCDictionary* dict)
{
	ItemFlagPoint* ret = new ItemFlagPoint;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemFlagPoint::init(CCDictionary* dict)
{
	Item::init();
	_Flag = this;

	_type = Item::IT_flagpoint;

	setPositionByProperty(dict);

	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("flag.png");
	setTexture(texture);
	setTextureRect(CCRect(0, 0, texture->getContentSize().width, texture->getContentSize().height));

	Common::moveNode(this, ccp(-texture->getContentSize().width/2, 0));

	_bCollisionWithMario = false;

	return true;
}

// 旗子和mario的碰撞，碰撞之后，mario进入autoRun第二个阶段
void ItemFlagPoint::collision()
{
	if (_bCollisionWithMario) return;

	if (_mario->boundingBox().intersectsRect(boundingBox()))
	{
		_bCollisionWithMario = true;
		_mario->autoRun2();

		if (_bridge)
		{

			ItemBoss* boss = (ItemBoss*)_Boss;
			boss->_status = ItemBoss::DROPPING;

			// 拆桥
			CCTMXLayer* land = getMap()->layerNamed("land");
			CCPoint ptTile = Common::Point2Tile(getMap(), _bridge->getPosition());
			for (int i = 0; i < 13; ++i)
				land->setTileGID(0, ccp(ptTile.x + i, ptTile.y));
		}
	}
}
