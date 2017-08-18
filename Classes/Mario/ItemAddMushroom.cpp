#include "ItemAddMushroom.h"

ItemAddMushroom* ItemAddMushroom::create(CCDictionary* dict)
{
	ItemAddMushroom* ret = new ItemAddMushroom;
	ret->init(dict);
	ret->autorelease();
	return ret;
}
bool ItemAddMushroom::init(CCDictionary* dict)
{
	Item::init();
	_type = Item::IT_mushroom;

	setPositionByProperty(dict);



	// ͼƬ
	setDisplayFrameWithAnimationName("MushroomMoving", 0);


	return true;
}
