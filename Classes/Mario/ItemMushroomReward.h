#ifndef __ItemMushroomReward_H__
#define __ItemMushroomReward_H__

#include "Item.h"
class ItemMushroomReward : public Item
{
public:
	static ItemMushroomReward* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	enum{SLEEP, GROW, MOVE} _status;

	Common::DIRECTION _dir;
	int _speedAcc;
	
	void wakeup(){
		_status = GROW;
		updateStatus();
		setVisible(true);
		_itemReward->removeObject(this);
	}
	void afterGrow();

	void updateStatus();

	bool canMove(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);

	void moveDown(float dt);

	void move(float dt);
	void collision();
};

#endif