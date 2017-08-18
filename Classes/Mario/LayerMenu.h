
#ifndef __LayerMenu_H__
#define __LayerMenu_H__
#include "Common.h"

// ักนุ
class LayerMenu : public CCLayer
{
public:
	CREATE_FUNC(LayerMenu);
	bool init();


	void Back(CCObject*);
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	bool isClick(CCTouch* pTouch);

	ScrollView* _view;
};

#endif