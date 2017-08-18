#ifndef __Mario_H__
#define __Mario_H__

#include "Common.h"
#include "Item.h"
// Mario抽象
class Mario : public CCSprite
{
public:
	CREATE_FUNC(Mario);
	bool init();
	CCTMXTiledMap* getMap();

	// status
	Common::DIRECTION _dirRun;  // 水平运动方向，如果是NONE表示静止，LEFT, RIGHT, NONE
	Common::DIRECTION _dirFace; // LEFT, RIGHT 静止的时候的脸朝向
	int _speedUp;	// 向上运动的速度，如果速度不为0，说明mario要继续上升
	int _speedDown; // 向下的速度
	int _speedAcc;  // 重力加速度
	static int _life;		// 命的数量
	bool _canFire;  // 是否可以发子弹
	bool _isBig;    // 是否变大
	int _speed;     // 水平移动的速度
	bool _bFly;     // 是不是在空中
	bool _bGodMode; // 无敌模式
	bool _dead;     // 死了
	bool _autoRun; // 自动行走
	bool _flagRunAction;

	bool _onLadder;

	// 根据上述状态，修改mario当前的表现方式
	void updateStatus();

	// 水平运动的操作函数
	void moveLeft(float dt);
	void moveRight(float dt);
	void stop();

	// 竖直方向运动
	void jump();
	void moveUp(float dt);
	void moveDown(float dt);

	// 移动控制
	bool canMoveDown(float dt);
	bool canMoveUp(float dt);
	bool canMoveLeft(float dt);
	bool canMoveRight(float dt);

	void Die(bool dead = true);

	void Hit(const std::string& layer, int gid, CCPoint ptTile);
	void wakeupMushroomReward(CCNode*);
	void eatMushroom(Item::ItemType type);

	void unsetGodMode(float)
	{
		this->_bGodMode = false;
	}
	void setGodMode(int time)
	{
		this->_bGodMode = true;
		scheduleOnce(schedule_selector(Mario::unsetGodMode), time);
	}
	void Dead();

	void autoRun(){ 
		_autoRun = true; updateStatus(); _speedUp = 0; _speedDown = 10;
		schedule(schedule_selector(Mario::moveDown));
	}
	
	void autoRun2() {
		schedule(schedule_selector(Mario::moveRight));
	}
//	CCAnimation* _walkLeftAnimationSmall;
//	CCAnimation* _walkRightAnimationSmall;
};

#endif

