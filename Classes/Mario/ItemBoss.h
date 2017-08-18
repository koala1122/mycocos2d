#ifndef __ItemBoss_H__
#define __ItemBoss_H__

#include "Item.h"
class ItemBoss : public Item
{
public:
	static ItemBoss* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	int _speedAcc;
	Common::DIRECTION _dir;
	int _left;
	int _right;
	enum{NORMAL, DROPPING} _status;

	//int _jumpCD;
	bool _bCanJump;
	void setAccJumpTrue(){ _bCanJump = true; }

	void updateStatus();
	void move(float dt);
};

#endif