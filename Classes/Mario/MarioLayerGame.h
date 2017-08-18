
#ifndef __LayerGame_H__
#define __LayerGame_H__
#include "Common.h"
#include "ProgressBar.h"
#include "Mario.h"

// ÓÎÏ·Âß¼­Àà
class LayerGame : public CCLayer
{
public:
	//CREATE_FUNC(LayerGame);
	static LayerGame* create(int idx);
	bool init(int idx);

	void loadResource();
	void startGame();
	void addCtrl();
	void addJumpFireMenuCtrl();

	CCTMXTiledMap* _map;
	Mario* _mario;
//	CCArray* _items;

	void onExit();
	void onEnter();

	ProgressBar* _bar;
	void loadImageCallBack(cocos2d::Texture2D *texture);
	void moveLeft(CCObject*);
	void moveRight(CCObject*);
	void moveMario(float);
	void Jump(CCObject*);

	Common::DIRECTION _marioDir;

	int _totalfile;
	int _loadFileCount;
	static int _idx;

	CCTexture2D* _textureDirNone;
	CCTexture2D* _textureDirLeft;
	CCTexture2D* _textureDirRight;
	CCSprite* _menuShow;

	static void GameOver();
	void checkMarioDie(float );
	void checkMarioTouchPole(float);
};

#endif