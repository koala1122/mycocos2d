#ifndef __ItemFlower_H__
#define __ItemFlower_H__

#include "Item.h"
class ItemFlower : public Item
{
public:
	static ItemFlower* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	Common::DIRECTION _dir; // UP, DOWN
	bool _bShow; // ����״̬�����ǻ�ȫ����ʾ����֮���״̬
	int _yTop;
	int _yButtom;

	void updateStatus();
	void move(float dt);
	void collision();

	void unsetShow(float dt)
	{ 
		_bShow = false; 
		//stopAllActions(); 
		_dir = Common::DOWN;
	}
};

#endif