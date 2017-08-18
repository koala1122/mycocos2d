#ifndef __ItemAddMushroom_H__
#define __ItemAddMushroom_H__

#include "Item.h"
class ItemAddMushroom : public Item
{
public:
	static ItemAddMushroom* create(CCDictionary* dict);
	bool init(CCDictionary* dict);
};

#endif