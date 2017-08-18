
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Stone.h"

#include <vector>
using namespace std;

struct Step
{
	int moveid;
	int killid;
	int rowFrom;
	int colFrom;
	int rowTo;
	int colTo;
};

class SceneGame : public CCLayer
{
public:
	
	CREATE_FUNC(SceneGame);
	bool init();
	void onExit();

	void CreatePlate();

	Stone* _s[32];

    bool onTouchBegan(Touch* node, Event* event) ;
    void onTouchEnded(Touch* node, Event* event);
//    void registerWithTouchDispatcher();
//    bool ccTouchesBegan(set<Touch>* touches, Event* event);
//    bool ccTouchesEnded(set<Touch>* touches, Event* event);
    
//	bool ccTouchBegan(CCTouch*, CCEvent*);
//	void ccTouchEnded(CCTouch*, CCEvent*);

	void addCtrlPanel();
	void Regret(CCObject*);

	void moveNode(CCNode* node, CCPoint pt)
	{
		node->setPosition(node->getPosition() + pt);
	}


	//////////////////////////////ʵ���߼�����
	void SelectStone(CCTouch* touch);
	void MoveStone(CCTouch* touch);

	void recordStep(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo);

	// �ƶ�����
	bool canMove(int moveid, int row, int col, int killid);
	bool canMoveChe(int moveid, int row, int col);
	bool canMovePao(int moveid, int row, int col, int killid);
	bool canMoveMa(int moveid, int row, int col);
	bool canMoveBing(int moveid, int row, int col);
	bool canMoveJiang(int moveid, int row, int col, int killid);
	bool canMoveShi(int moveid, int row, int col);
	bool canMoveXiang(int moveid, int row, int col);

	void computerMove(float);
	

	//////////////////////////////��������
	// ͨ����Ļ���꣬��ȡ�������꣬����ֵ�����false��ʾptScreen��������
	bool Screen2Plate(const CCPoint& ptScreen, int& row, int& col);
	CCPoint Plate2Screen(int row, int col);

	// ��ȡ���������֮������Ӹ���
	int getStoneCount(int row1, int col1, int row2, int col2);

	// ͨ���������꣬��ȡ�����ϵ�����ID���������-1��ʾ��λ����û�����ӣ��������-1�����Ƕ�Ӧ����id
	int getStoneFromRowCol(int row, int col);

	// �ж�����������ɫ�Ƿ���ͬ
	bool isSameColor(int id1, int id2)
	{
		return _s[id1]->_red == _s[id2]->_red;
	}

	///////////////////////////////��Ա��������Ҫ������Ϸ�����е�״̬���

	// ��¼�Ѿ�ѡ������ӵ�ID,�����-1��ʾ֮ǰû�����屻ѡ��,�������-1��ô��ʾ����ID
	int _selectid;

	// ���Ŀǰ��˭��
	bool _bRedTurn;

	// ѡ�б�Ǿ���
	CCSprite* _selectSprite;

	// ��¼����켣��������
	vector<Step*> _steps;
};

#endif

