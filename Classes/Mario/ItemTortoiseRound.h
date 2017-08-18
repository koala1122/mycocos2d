#ifndef __ItemTortoiseRound_H__
#define __ItemTortoiseRound_H__

#include "Item.h"
class ItemTortoiseRound : public Item
{
public:
	static ItemTortoiseRound* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	enum{NORMAL, SLEEP, CRAZY} _status;

	int _roundDis;
	//float _dis;
	int _leftMost;
	int _rightMost;

	Common::DIRECTION _dir;
	bool _bGodMode;
	void unsetGodMode(float){ _bGodMode = false; }

	void updateStatus();
	void move(float dt);
	void collision();

	

	void Recover(float);
};

#endif