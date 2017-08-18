
#ifndef __AI_H__
#define __AI_H__

#include "SceneGame.h"

class AI
{
public:
	// ���ݵ�ǰ���棬����һ��Step
	static Step* getStep(SceneGame* game);

	// �������
	static int getScore(SceneGame* game);
	// �������ܵ��ƶ�
	static vector<Step*> getAllPossibleMove(SceneGame* game);

	static void fakeMove(SceneGame* game, Step* step);
	static void unfakeMove(SceneGame* game, Step* step);

	// �ಽ�����㷨ʵ��
	static Step* getStep(SceneGame* game, int level);
	static int getMinScore(SceneGame* game, int level, int curMinScore);
	static int getMaxScore(SceneGame* game, int level, int curMaxScore);
};

#endif

