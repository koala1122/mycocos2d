#include "cocos2d.h"
USING_NS_CC;


class MyLayer: public  Layer
{
public:
	CREATE_FUNC(MyLayer);
	/*static MyLayer *create();*/

	static Scene * scene();
	bool init() override;
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    void mySchedule(float dt);
    Sprite *spr;
    Point touchPoint;
    DrawNode *objDraw;

};

