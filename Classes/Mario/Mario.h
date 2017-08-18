#ifndef __Mario_H__
#define __Mario_H__

#include "Common.h"
#include "Item.h"
// Mario����
class Mario : public CCSprite
{
public:
	CREATE_FUNC(Mario);
	bool init();
	CCTMXTiledMap* getMap();

	// status
	Common::DIRECTION _dirRun;  // ˮƽ�˶����������NONE��ʾ��ֹ��LEFT, RIGHT, NONE
	Common::DIRECTION _dirFace; // LEFT, RIGHT ��ֹ��ʱ���������
	int _speedUp;	// �����˶����ٶȣ�����ٶȲ�Ϊ0��˵��marioҪ��������
	int _speedDown; // ���µ��ٶ�
	int _speedAcc;  // �������ٶ�
	static int _life;		// ��������
	bool _canFire;  // �Ƿ���Է��ӵ�
	bool _isBig;    // �Ƿ���
	int _speed;     // ˮƽ�ƶ����ٶ�
	bool _bFly;     // �ǲ����ڿ���
	bool _bGodMode; // �޵�ģʽ
	bool _dead;     // ����
	bool _autoRun; // �Զ�����
	bool _flagRunAction;

	bool _onLadder;

	// ��������״̬���޸�mario��ǰ�ı��ַ�ʽ
	void updateStatus();

	// ˮƽ�˶��Ĳ�������
	void moveLeft(float dt);
	void moveRight(float dt);
	void stop();

	// ��ֱ�����˶�
	void jump();
	void moveUp(float dt);
	void moveDown(float dt);

	// �ƶ�����
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

