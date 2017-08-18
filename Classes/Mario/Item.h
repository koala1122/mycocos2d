#ifndef __Item_H__
#define __Item_H__

#include "Common.h"
class Mario;

// ���࣬�͹�����
// �ָ�ģ�飨��ģ��֮����ھۣ�����ϣ�
// ��̬���麯����
class Item : public CCSprite
{
public:
	enum ItemType{IT_mushroom, IT_tortoise, IT_flower, IT_mushroomReward, IT_mushroomAddLife, IT_flagpoint,
		IT_finalpoint, IT_LadderLR, IT_LadderUD, IT_flyfish, IT_tortoiseRound, IT_tortoiseFly, IT_firestring,
		IT_boss, IT_bridgestartpos
	};
	// Item* item;     delete item;
	virtual ~Item();

	// ���е��߶���Ҫ���õĳ�ʼ������
	bool init()
	{
		CCSprite::init();
		setZOrder(100);
		_bGodMode = false;
		// Ϊ�����ṩ����
		scheduleUpdate();
		return true;
	}

	Mario* _mario;
	static CCArray* _itemReward;
	static Item* _Flag;
	static Item* _Boss;
	static Item* _bridge;
	// �����ӿ�
	static Item* create(CCDictionary* dict);

	// �������ӿ�
	virtual void move(float dt) {}
	virtual void collision() {}
	virtual void wakeup(){}

	void update(float dt)
	{
		move(dt);
		collision();
	}

	////////////////////////////// ������������
	void setPositionByProperty(CCDictionary* dict)
	{
		const CCString* x = dict->valueForKey("x");
		const CCString* y = dict->valueForKey("y");
		setPosition(ccp(x->intValue(), y->intValue() - 16));
		setAnchorPoint(ccp(0, 0));
	}

	CCTMXTiledMap* getMap()
	{
		return (CCTMXTiledMap*)getParent();
	}

	bool isLeftInWindow()
	{
	//	CCPoint ptInMap = getPosition();
		CCRect rcItem = boundingBox();
		CCPoint ptInMap = ccp(rcItem.getMinX(), rcItem.getMinY());

		CCTMXTiledMap* map = getMap();
		CCPoint ptInWorld = map->convertToWorldSpace(ptInMap);
		if (ptInWorld.x <= winSize.width)
		{
			return true;
		}

		return false;
	}

	bool isFarAwayFromMario();
	
	ItemType _type;

	int _speedDown;
	int _speed;

	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);

	void moveLeft(float dt);
	void moveRight(float dt);
	void moveDown(float dt);

	// �����޵�
	bool _bGodMode;
	void setGodMode(int time)
	{
		_bGodMode = true;
		scheduleOnce(schedule_selector(Item::unsetGodMode), time);
	}
	void unsetGodMode(float dt)
	{
		_bGodMode = false;
	}

	void runAnimation(const char* name)
	{
		stopAllActions();
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(name);
		runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	}
};

#if 0
class ItemFactroy
{
public:
	Item* createItem(Item::ItemType it)
	{
		return Item::create(it);
	}
};
#endif

#endif
