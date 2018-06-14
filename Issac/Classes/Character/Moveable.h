#ifndef _Moveable_h
#define _Moveable_h

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#ifndef _max_
#define _max_
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif
#ifndef _abs_
#define _abs_
#define abs(x) ((x) < 0 ? (-x) : x)
#endif
#ifndef _ColClogTime_
#define ColClogTime 3
#endif

class Moveable : public Sprite
{
  public:
	bool init() override;

	CC_SYNTHESIZE_RETAIN(Animate *, idleAnimate, IdleAnimate)
	CC_SYNTHESIZE_RETAIN(Animate *, moveAnimate, MoveAnimate)

	CC_SYNTHESIZE(bool, moving, Moving)
	CC_SYNTHESIZE(int, prev_walk_orientation, PrevWalkOrientation)
	CC_SYNTHESIZE(int, prev_head_orientation, PrevHeadOrientation)
	CC_SYNTHESIZE(double, moveSpeed, MoveSpeed)
	CC_SYNTHESIZE(double, radiusSize, RadiusSize)
	CC_SYNTHESIZE(double, bodyMass, BodyMass)
	CC_SYNTHESIZE(int, invincibleTime, InvincibleTime)
	CC_SYNTHESIZE(double, tearSpeed, TearSpeed)
	CC_SYNTHESIZE(int, tearExistTime, TearExistTime)
	CC_SYNTHESIZE(int, fireSpeed, FireSpeed)

	//初步设定Issac的血量为整数，单位为半颗血。Monster血量为实数，<0时死亡
	CC_SYNTHESIZE(int, health, Health)
	//初步设定Issac的攻击为实数。Monster攻击为整数，普通怪1，精英怪2
	CC_SYNTHESIZE(double, attack, Attack)
	//ColClog用于碰撞阻塞
	CC_SYNTHESIZE(int, colClog, ColClog)

	virtual void createPhyBody() = 0;
	Vec2 calSpeed(int dir);
};

#endif
