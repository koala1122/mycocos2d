#ifndef __ItemMushroomAddLife_H__
#define __ItemMushroomAddLife_H__

#include "ItemMushroomReward.h"
class ItemMushroomAddLife : public ItemMushroomReward
{
public:
	static ItemMushroomAddLife* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

};

#endif