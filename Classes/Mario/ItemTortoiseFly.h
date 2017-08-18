#ifndef __ItemTortoiseFly_H__
#define __ItemTortoiseFly_H__

#include "Item.h"
class ItemTortoiseFly : public Item
{
public:
	static ItemTortoiseFly* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	/*
		״̬
	*/
	enum {NORMAL, DROPPING, ONLAND, SLEEP, CRAZY} _status;
	int _speedAcc;
	Common::DIRECTION _dir;
	int _flyDis;
	// ����ߺ����ұߵ�λ��
	int _left;
	int _right;

	void updateStatus();

	void move(float dt);
	void collision();

	void Recover(float dt);
};

#endif