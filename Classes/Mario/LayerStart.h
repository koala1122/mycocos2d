
#ifndef __LayerStart_H__
#define __LayerStart_H__
#include "Common.h"

// ��һ����������
class LayerStart : public CCLayer
{
public:
	CREATE_FUNC(LayerStart);
	bool init();

	void Start(CCObject*);
	void Setup(CCObject*);
	void Quit(CCObject*);
	void About(CCObject*);
};

#endif