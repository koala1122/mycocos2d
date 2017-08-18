#include "ProgressBar.h"

ProgressBar* ProgressBar::create(const char* bgFile, const char* foreFile)
{
	ProgressBar* ret = new ProgressBar;
	ret->init(bgFile, foreFile);
	ret->autorelease();
	return ret;
}


bool ProgressBar::init(const char* bgFile, const char* foreFile)
{
	CCLayer::init();
	// ������������
	_bg = CCSprite::create(bgFile);
	addChild(_bg);

	// ����ǰ������
	CCSprite* fore = CCSprite::create(foreFile);
	_bar = CCProgressTimer::create(fore);

	// �������εģ��������˶��Ľ�����
	_bar->setType(kCCProgressTimerTypeBar);
	_bar->setMidpoint(ccp(0, 0));
	_bar->setBarChangeRate(ccp(1, 0));

	_bar->setPercentage(0);
	addChild(_bar);

	return true;
}