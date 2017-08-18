#ifndef __ItemBullet_H__
#define __ItemBullet_H__

#include "Item.h"
class ItemBullet : public Item
{
public:
	static ItemBullet* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	CREATE_FUNC(ItemBullet);
	bool init();
};

#endif