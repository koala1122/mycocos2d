#ifndef __ItemMushroom_H__
#define __ItemMushroom_H__

#include "Item.h"
class ItemMushroom : public Item
{
public:
	static ItemMushroom* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	Common::DIRECTION _dir;
	int _speedAcc;
	bool _isDead;

	bool canMove(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);

	void moveDown(float dt);

	// �ӿڴ�����
	void move(float dt);
	void collision();
};

#endif