#ifndef _Moveable_h
#define _Moveable_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#ifndef _max_
#define _max_
#define max(x,y) ((x)>(y)?(x):(y))
#endif
#ifndef _abs_
#define _abs_
#define abs(x)	((x)<0?(-x):x)
#endif

class Moveable : public Sprite {
public:
	bool init() override;

	CC_SYNTHESIZE_RETAIN(Animate*, idleAnimate, IdleAnimate)
	CC_SYNTHESIZE_RETAIN(Animate*, moveAnimate, MoveAnimate)

	CC_SYNTHESIZE(bool, moving, Moving)
	CC_SYNTHESIZE(int, prev_walk_orientation, PrevWalkOrientation)
	CC_SYNTHESIZE(int, prev_head_orientation, PrevHeadOrientation)
	CC_SYNTHESIZE(double, moveSpeed, MoveSpeed)
	CC_SYNTHESIZE(double, widthSize, WidthSize)

	virtual Rect boundingBox();
};

#endif
