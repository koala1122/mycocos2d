#include "SceneGame.h"
#include "AI.h"
#include "CommonUI.h"
bool SceneGame::init()
{
	Layer::init();

	// �ڷ�����
	CreatePlate();

	// ��������
	// ��ɫ
	// ����(che,ma,pao)
	// λ��
	// ��С
	// ID
    auto listener = EventListenerTouchOneByOne::create();
    
    // �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
    listener->setSwallowTouches(true);
    
    // ������ʼʱ,�õ��ú����ķ�ʽ
    listener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this); // ������ʼ
//    listener->onTouchMoved = CC_CALLBACK_2(TouchExa::onTouchMoved, this); // �����ƶ�
    listener->onTouchEnded = CC_CALLBACK_2(SceneGame::onTouchEnded, this); // ��������
//    listener->onTouchCancelled = CC_CALLBACK_2(TouchExa::onTouchCancelled, this); // �����ж�
    
    // ���¼��ַ�����������Ӽ�����,this��ʾ������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // ��������¡
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite2);
    
	Stone::_d = (Director::sharedDirector()->getWinSize().height - ORIGINY * 2)/10;
	Stone::_offx = Stone::_d;
	Stone::_offy = Stone::_d/2 + ORIGINY;

	for (int i = 0; i < 32; i++)
	{
		_s[i] = Stone::create();
		_s[i]->initStone(i);
		addChild(_s[i]);
	}

	// ʹ�ܴ���
	setTouchEnabled(true);
//	setTouchMode(kTouchesOneByOne);

	_selectid = -1;
	_selectSprite = Sprite::create("selected.png");
	_selectSprite->setVisible(false);
	addChild(_selectSprite);
	_selectSprite->setScale(.6);

	_bRedTurn = true;

	_steps.clear();

	// ���ӿ������(�������尴ť)
	addCtrlPanel();

	return true;
}

void SceneGame::addCtrlPanel()
{
	Menu* menu = Menu::create();
	addChild(menu);

	MenuItemImage* regretItem = MenuItemImage::create("regret.jpg", "regret.jpg",
		this, menu_selector(SceneGame::Regret));
	menu->addChild(regretItem);

	moveNode(regretItem, ccp(160, 60));
}

void SceneGame::Regret(Object*)
{
	// ��Ϸ��û�п�ʼ���ܻ���
	if (_steps.size() == 0)
		return;

	// �ָ����һ��
	Step* step = *_steps.rbegin();
	_steps.pop_back();

	// ����ָ�����
	Stone* s = _s[step->moveid];
	s->_row = step->rowFrom;
	s->_col = step->colFrom;
	s->setPosition(s->fromPlate());

	Stone* kill;
	if (step->killid != -1)
	{
		kill = _s[step->killid];
		kill->_dead = false;
		kill->setVisible(true);
	}

	_bRedTurn = !_bRedTurn;
	delete step;

	// ������ѡ�����ӵ�����£�����
	_selectid = -1;
	_selectSprite->setVisible(false);
}

void SceneGame::onExit()
{
	Layer::onExit();
}

void SceneGame :: CreatePlate()
{
	Sprite* plate = Sprite::create("background.png");
	addChild(plate);
    plate->setAnchorPoint(Point(0, 0));
//	plate->setPosition(Vec2(0+ORIGINX, 0+ORIGINY));
    plate->setPosition(Point(0, ORIGINY));
    
	
//	plate->setScale(Director::getInstance()->getWinSize().height / plate->getContentSize().height);
//    plate->setScale(Director::getInstance()->getWinSize().height / plate->getContentSize().height);
    plate->setContentSize(Size(Screen_Height - ORIGINY*2,Screen_Height - ORIGINY*2));
}
bool SceneGame::onTouchBegan(cocos2d::Touch *node, cocos2d::Event *event)
{
    return true;
}

void SceneGame::onTouchEnded(cocos2d::Touch *node, cocos2d::Event *event)
{
    // �ƶ�����
    if (_selectid == -1)
    {
        // ��ͼѡ������
        SelectStone(node);
    }
    else
    {
        // ��ͼ�ƶ�����
        MoveStone(node);
    }
}

void SceneGame::SelectStone(Touch* touch)
{
	// 1��ͨ��touch��õ��λ��
	// 2��ͨ��λ�û��row��col������Ļ����ת������������
	// 3��ͨ����������������id
	// 4����¼ѡ�е����ӵ�ID
	Point ptClicked = touch->getLocation();
	int row, col;
	bool bClick = Screen2Plate(ptClicked, row, col);
	// �������������⣬�ôε����Ч
	if (!bClick)
	{
		return;
	}

	int clickid = getStoneFromRowCol(row, col);
	// ������λ��û�����壬��ô���Ҳ��Ч
	if (clickid == -1)
	{
		return;
	}

	// ��������е����ӣ���_bRedTurn��ɫ��һ�£�����ѡ��
	if (_s[clickid]->_red != _bRedTurn)
		return;

	// ��¼��εĵ��
	_selectid = clickid;

	// ��ʾ�����ӱ�ѡ�е�Ч��
	_selectSprite->setPosition(Plate2Screen(row, col));
	_selectSprite->setVisible(true);
}

void SceneGame::recordStep(int moveid, int killid, int rowFrom, int colFrom, int rowTo, int colTo)
{
	Step* s = new Step();
	s->colFrom = colFrom;
	s->colTo = colTo;
	s->killid = killid;
	s->moveid = moveid;
	s->rowFrom = rowFrom;
	s->rowTo = rowTo;

	//_steps->addObject(s);
	_steps.push_back(s);
}

void SceneGame::MoveStone(Touch* touch)
{
	Point ptClicked = touch->getLocation();
	int row, col;
	bool bClick = Screen2Plate(ptClicked, row, col);
	// �������������⣬�ôε����Ч
	if (!bClick)
	{
		return;
	}

	// ���Ŀ��λ���Ƿ������ӣ�����У���ôɱ��
	int clickid = getStoneFromRowCol(row, col);
	// ������λ��û�����壬��ô���Ҳ��Ч
	if (clickid != -1)
	{
		// �����һ�ε�������Ӻ�ǰһ����ͬ����ô��ѡ��
		if (isSameColor(clickid, _selectid))
		{
			_selectid = clickid;
			// ��ʾ�����ӱ�ѡ�е�Ч��
			Point pt = Plate2Screen(row, col);
			_selectSprite->setPosition(pt);
			_selectSprite->setVisible(true);

			// ��ѡ��֮����ε������ͽ�����
			return;
		}
	}

	// �ж������Ƿ�����ƶ�
	if (!canMove(_selectid, row, col, clickid))
	{
		return;
	}

	// �����ƶ�
	// ��¼�ƶ���Ϣ
	recordStep(_selectid, clickid, _s[_selectid]->_row, _s[_selectid]->_col, row, col);

	// �������
	if (clickid != -1)
	{
		// ɱ��
		_s[clickid]->setVisible(false);
		_s[clickid]->_dead = true;
	}

	_s[_selectid]->_row = row;
	_s[_selectid]->_col = col;

	_s[_selectid]->setPosition(Plate2Screen(row, col));

	_selectid = -1;
	_selectSprite->setVisible(false);
	_bRedTurn = !_bRedTurn;

	// �˹�����
	if (!_bRedTurn)
	{
	//	CCDelayTime* delay = CCDelayTime::create(0.01);
	//	CCCallFunc* ai = CCCallFunc::create(this, callfunc_selector(SceneGame::computerMove));

	//	CCSequence* seq = CCSequence::create(delay, ai, NULL);
	//	this->runAction(seq);

		scheduleOnce(schedule_selector(SceneGame::computerMove), 0.01);
	}
}

void SceneGame::computerMove(float )
{
	// ���Բ���һ��step����
	Step* step = AI::getStep(this, 4);

	Stone* moveStone = _s[step->moveid];
	moveStone->_row = step->rowTo;
	moveStone->_col = step->colTo;
	_bRedTurn = !_bRedTurn;
	moveStone->setPosition(moveStone->fromPlate());

	if (step->killid != -1)
	{
		Stone* killStone = _s[step->killid];
		killStone->_dead = true;
		killStone->setVisible(false);
	}

	_steps.push_back(step);
}

int SceneGame::getStoneCount(int row1, int col1, int row2, int col2)
{
	int ret = 0;
	if (row1 != row2 && col1 != col2) return -1;
	if (row1 == row2 && col1 == col2) return -1;

	// row1 == row2 ����col1 == col2

	if (row1 == row2)
	{
		int min, max;
		min = col1 < col2 ? col1 : col2;
		max = col1 > col2 ? col1 : col2;
		for (int col = min + 1; col < max; ++col)
		{
			int id = getStoneFromRowCol(row1, col);
			if (id != -1) ++ret;
		}
	}
	else
	{
		int min, max;
		min = row1 < row2 ? row1 : row2;
		max = row1 > row2 ? row1 : row2;
		for (int row = min + 1; row < max; ++row)
		{
			int id = getStoneFromRowCol(row, col1);
			if (id != -1) ++ret;
		}
	}

	return ret;
}

bool SceneGame::canMoveChe(int moveid, int row, int col)
{
	// һ����,�м䲻��������
	Stone* s = _s[moveid];
	
	return getStoneCount(s->_row, s->_col, row, col) == 0;
}

bool SceneGame::canMovePao(int moveid, int row, int col, int killid)
{
	Stone* s = _s[moveid];
	if (killid == -1)
		return getStoneCount(s->_row, s->_col, row, col) == 0;
	
	return getStoneCount(s->_row, s->_col, row, col) == 1;
}

bool SceneGame::canMoveMa(int moveid, int row, int col)
{
	Stone* s = _s[moveid];
	int dRow = abs(s->_row - row);
	int dCol = abs(s->_col - col);
	int d = dRow * 10 + dCol;

	// ����������
	if (d == 12 || d == 21)
	{
		// ����λ��
		int cRow, cCol;
		if (d == 12)
		{
			cCol = (col + s->_col) / 2;
			cRow = s->_row;
		}
		else
		{
			cCol = s->_col;
			cRow = (s->_row + row)/2;
		}

		// û�����ŵ�����
		if (getStoneFromRowCol(cRow, cCol) == -1)
			return true;
	}

	return false;
}

bool SceneGame::canMoveBing(int moveid, int row, int col)
{
	Stone* s = _s[moveid];
	int dRow = abs(s->_row - row);
	int dCol = abs(s->_col - col);
	int d = dRow * 10 + dCol;

	// ��̫Զ����,ֻ����һ��
	if (d != 1 && d != 10)
		return false;

	if (s->_red)
	{
		// ���ܺ���
		if (row < s->_row) return false;

		// ����ǰ����ƽ��
		if (s->_row <= 4 && s->_row == row) return false;
	}
	else
	{
		if (row > s->_row) return false;
		if (s->_row >= 5 && s->_row == row) return false;
	}

	return true;
}

bool SceneGame::canMoveJiang(int moveid, int row, int col, int killid)
{
	Stone* s = _s[moveid];

	// ������
	if (killid != -1)
	{
		Stone* kill = _s[killid];
		if (kill->_type == Stone::JIANG)
		{
			return canMoveChe(moveid, row, col);
		}
	}

	int dRow = abs(s->_row - row);
	int dCol = abs(s->_col - col);
	int d = dRow * 10 + dCol;
	// ��̫Զ����,ֻ����һ��
	if (d != 1 && d != 10)
		return false;

	// ���ܳ��Ź�
	if (col < 3 || col > 5) return false;
	if (s->_red)
	{
		if (row < 0 || row > 2) return false;
	}
	else
	{
		if (row < 7 || row > 9) return false;
	}

	return true;
}

bool SceneGame::canMoveShi(int moveid, int row, int col)
{
	Stone* s = _s[moveid];
	int dRow = abs(s->_row - row);
	int dCol = abs(s->_col - col);
	int d = dRow * 10 + dCol;
	if (d != 11) return false;

	// ���ܳ��Ź�
	if (col < 3 || col > 5) return false;
	if (s->_red)
	{
		if (row < 0 || row > 2) return false;
	}
	else
	{
		if (row < 7 || row > 9) return false;
	}

	return true;
}

bool SceneGame::canMoveXiang(int moveid, int row, int col)
{
	Stone* s = _s[moveid];
	int dRow = abs(s->_row - row);
	int dCol = abs(s->_col - col);
	int d = dRow * 10 + dCol;
	if (d != 22) return false;

	// ����
	int cRow, cCol;
	cRow = (row + s->_row) / 2;
	cCol = (col + s->_col) / 2;
	if (getStoneFromRowCol(cRow, cCol) != -1)
		return false;

	// �ж����ܹ���
	if (s->_red)
	{
		if (row > 4) return false;
	}
	else
	{
		if (row < 5) return false;
	}

	return true;
}

bool SceneGame::canMove(int moveid, int row, int col, int killid)
{
	Stone* s = _s[moveid];
	switch (s->_type)
	{
	case Stone::CHE:
		return canMoveChe(moveid, row, col);

	case Stone::MA:
		return canMoveMa(moveid, row, col);

	case Stone::PAO:
		return canMovePao(moveid, row, col, killid);

	case Stone::BING:
		return canMoveBing(moveid, row, col);
		
	case Stone::JIANG:
		return canMoveJiang(moveid, row, col, killid);

	case Stone::SHI:
		return canMoveShi(moveid, row, col);

	case Stone::XIANG:
		break;
	}
	return false;
}

CCPoint SceneGame::Plate2Screen(int row, int col)
{
	int x = col * Stone::_d + Stone::_offx;
	int y = row * Stone::_d + Stone::_offy;

	return ccp(x, y);
}

bool SceneGame::Screen2Plate(const Point& ptSceen, int& row, int& col)
{
	// ����������������㣬�������̸�����������㵽����ĵ�ľ��룬���С�ڰ뾶����ô�Ͷ���
	int distance = Stone::_d*Stone::_d / 4;
	for (row = 0; row <= 9; ++row)
	for (col = 0; col <= 8; ++col)
	{
		CCPoint ptCenter = Plate2Screen(row, col);
		// getDistance, getDistanceSq
		if (ptCenter.getDistanceSq(ptSceen) < distance)
		{
			return true;
		}
	}
	return false;
}

int SceneGame::getStoneFromRowCol(int row, int col)
{
	for (int i = 0; i < 32; ++i)
	{
		if (_s[i]->_row == row && _s[i]->_col == col && !_s[i]->_dead)
			return i;
	}
	return -1;
}
