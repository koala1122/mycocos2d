#include "ItemBullet.h"

ItemBullet* ItemBullet::create(CCDictionary* dict)
{
#if 0
	ItemBullet* ret = new ItemBullet;
	ret->init(dict);
	ret->autorelease();

	return ret;
#endif
	return NULL;
}
bool ItemBullet::init(CCDictionary* dict)
{
	Item::init();
#if 0
	_type = Item::IT_mushroom;

	setPositionByProperty(dict);



	// ͼƬ
	setDisplayFrameWithAnimationName("MushroomMoving", 0);
#endif

	return true;
}


bool ItemBullet::init()
{
	Item::init();

	//.....

	return true;
}
