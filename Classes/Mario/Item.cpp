#include "Item.h"
#include "Mario.h"
#include "ItemMushroom.h"
#include "ItemTortoise.h"
#include "ItemFlower.h"
#include "ItemMushroomReward.h"
#include "ItemFlagPoint.h"
#include "ItemMushroomAddLife.h"
#include "ItemFinalPoint.h"
#include "ItemLadderLR.h"
#include "ItemFlyFish.h"
#include "ItemTortoiseRound.h"
#include "ItemTortoiseFly.h"
#include "ItemLadderUD.h"
#include "ItemFireString.h"
#include "ItemBoss.h"
#include "ItemBridgeStartPos.h"
CCArray* Item::_itemReward;
Item* Item::_Flag;
Item* Item::_Boss;
Item* Item::_bridge;
Item::~Item()
{
}

Item* Item::create(CCDictionary* dict)
{
	const CCString* type = dict->valueForKey("type");

	if (type->_string == "mushroom")
		return ItemMushroom::create(dict);
	else if (type->_string == "tortoise")
		return ItemTortoise::create(dict);
	else if (type->_string == "flower")
		return ItemFlower::create(dict);
	else if (type->_string == "MushroomReward")
		return ItemMushroomReward::create(dict);
	else if (type->_string == "flagpoint")
		return ItemFlagPoint::create(dict);
	else if (type->_string == "MushroomAddLife")
		return ItemMushroomAddLife::create(dict);
	else if (type->_string == "finalpoint")
		return ItemFinalPoint::create(dict);
	else if (type->_string == "ladderLR")
		return ItemLadderLR::create(dict);
	else if (type->_string == "ladderUD")
		return ItemLadderUD::create(dict);
	else if (type->_string == "flyfish")
		return ItemFlyFish::create(dict);
	else if (type->_string == "tortoise_round")
		return ItemTortoiseRound::create(dict);
	else if (type->_string == "tortoise_fly")
		return ItemTortoiseFly::create(dict);
	else if (type->_string == "fire_string")
		return ItemFireString::create(dict);
	else if (type->_string == "boss")
		return ItemBoss::create(dict);
	else if (type->_string == "bridgestartpos")
		return ItemBridgeStartPos::create(dict);
	

	return NULL;
}

bool Item::isFarAwayFromMario()
{
	CCRect rcItem = this->boundingBox();
	CCRect rcMario = _mario->boundingBox();
	if (rcMario.getMinX() - rcItem.getMaxX() > winSize.width)
		return true;
	return false;
}

bool Item::canMoveLeft(float dt)
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
				return false;
			}
		}
	}

	return true;
}
bool Item::canMoveRight(float dt)
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
				return false;
			}
		}
	}

	return true;
}
bool Item::canMoveDown(float dt)
{

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

void Item::moveLeft(float dt)
{
	Common::moveNode(this, ccp(-dt*_speed, 0));
}
void Item::moveRight(float dt)
{
	Common::moveNode(this, ccp(dt*_speed, 0));
}
void Item::moveDown(float dt)
{
	Common::moveNode(this, ccp(0, -dt*_speedDown));
}