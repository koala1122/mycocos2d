#ifndef __ItemTortoise_H__
#define __ItemTortoise_H__

#include "Item.h"
class ItemTortoise : public Item
{
public:
	
	static ItemTortoise* create(CCDictionary* dict);
	bool init(CCDictionary* dict);

	Common::DIRECTION _dir;
	int _speedAcc;

	bool _isGod;   // ��mario�ȵ�ʱ��Ҫһ��ʱ�䣨.2�룩���޵�״̬
	bool _isSleep; // ��mario����һ�Σ�����һ��ʱ�䣬Ҫ����
	bool _isDead;
	bool _isCrazy; 


	bool canMove(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);
	bool canMoveDown(float dt);

	void move(float dt);
	void moveDown(float dt);

	void collision();

	void unsetGodmode(float dt)
	{
		_isGod = false;
	}

	void revive(float dt)
	{
		_isSleep = false;
		_speed = 50;
		stopAllActions();
		if (_dir == Common::LEFT)
		{
			this->runAction(CCRepeatForever::create
				(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveLeft"))));

		}
		else
		{
			this->runAction(CCRepeatForever::create
				(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("TortoiseMoveRight"))));
		}
	}

	
};

#endif