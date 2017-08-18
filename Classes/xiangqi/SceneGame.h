
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


	//////////////////////////////实现逻辑函数
	void SelectStone(CCTouch* touch);
	void MoveStone(CCTouch* touch);

	void recordStep(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo);

	// 移动规则
	bool canMove(int moveid, int row, int col, int killid);
	bool canMoveChe(int moveid, int row, int col);
	bool canMovePao(int moveid, int row, int col, int killid);
	bool canMoveMa(int moveid, int row, int col);
	bool canMoveBing(int moveid, int row, int col);
	bool canMoveJiang(int moveid, int row, int col, int killid);
	bool canMoveShi(int moveid, int row, int col);
	bool canMoveXiang(int moveid, int row, int col);

	void computerMove(float);
	

	//////////////////////////////辅助函数
	// 通过屏幕坐标，获取棋盘坐标，返回值如果是false表示ptScreen在棋盘外
	bool Screen2Plate(const CCPoint& ptScreen, int& row, int& col);
	CCPoint Plate2Screen(int row, int col);

	// 获取两个坐标点之间的棋子个数
	int getStoneCount(int row1, int col1, int row2, int col2);

	// 通过棋盘坐标，获取坐标上的棋子ID，如果返回-1表示该位置上没有棋子，如果不是-1，就是对应棋子id
	int getStoneFromRowCol(int row, int col);

	// 判断两个棋子颜色是否相同
	bool isSameColor(int id1, int id2)
	{
		return _s[id1]->_red == _s[id2]->_red;
	}

	///////////////////////////////成员变量，主要用于游戏过程中的状态标记

	// 记录已经选择的棋子的ID,如果是-1表示之前没有象棋被选中,如果不是-1那么表示具体ID
	int _selectid;

	// 标记目前该谁走
	bool _bRedTurn;

	// 选中标记精灵
	CCSprite* _selectSprite;

	// 记录走棋轨迹用来悔棋
	vector<Step*> _steps;
};

#endif

