
#ifndef __AI_H__
#define __AI_H__

#include "SceneGame.h"

class AI
{
public:
	// 根据当前局面，产生一个Step
	static Step* getStep(SceneGame* game);

	// 计算分数
	static int getScore(SceneGame* game);
	// 产生可能的移动
	static vector<Step*> getAllPossibleMove(SceneGame* game);

	static void fakeMove(SceneGame* game, Step* step);
	static void unfakeMove(SceneGame* game, Step* step);

	// 多步智能算法实现
	static Step* getStep(SceneGame* game, int level);
	static int getMinScore(SceneGame* game, int level, int curMinScore);
	static int getMaxScore(SceneGame* game, int level, int curMaxScore);
};

#endif

