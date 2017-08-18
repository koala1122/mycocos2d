
#ifndef __COMMON_H__
#define __COMMON_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define winSize CCDirector::sharedDirector()->getWinSize()



struct Common
{
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, NONE };

	static CCScene* scene(CCLayer* layer)
	{
		CCScene* s = CCScene::create();
		s->addChild(layer);
		return s;
	}

	static void moveNode(CCNode* node, CCPoint pt)
	{
		node->setPosition(node->getPosition() + pt);
	}

	static char* format(int v, const char* prefix = "", const char* suffix = "")
	{
		static char buf[2048];
		sprintf(buf, "%s%d%s", prefix, v, suffix);
		return buf;
	}

	static Animation* CreateAnimation(const char* filename, int start, int end, int width, float delay)
	{
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage(filename);
        Vector<SpriteFrame*> frames;
//		Array* arr = Array::create();
		for (int i = start; i <= end; ++i)
		{
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, CCRectMake(i*width, 0, width, texture->getContentSize().height));
//			arr->addObject(frame);
            frames.pushBack(frame);
		}

		return CCAnimation::createWithSpriteFrames(frames, delay);

	}
	static CCSpriteFrame* getSpriteFrame(const char* filename, int pos, int width)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(pos*width, 0, width, texture->getContentSize().height));
		return frame;
	}

	static CCPoint Point2Tile(CCTMXTiledMap* map, CCPoint ptInMap)
	{
		int dx = map->getTileSize().width;
		int dy = map->getTileSize().height;

		int x = ptInMap.x / dx;
		int y = ptInMap.y / dy;
		y = map->getMapSize().height - 1 - y;

		return ccp(x, y);
	}

	static CCPoint Tile2PointLB(CCTMXTiledMap* map, CCPoint ptTile)
	{
		ptTile.y = map->getMapSize().height - 1 - ptTile.y;

		return ccp(ptTile.x * map->getTileSize().width,
			ptTile.y * map->getTileSize().height);
	}
};

#endif