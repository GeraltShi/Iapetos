#ifndef _COLLECTABLE_H_
#define _COLLECTABLE_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Collectable : public Sprite
{
  public:
	static Collectable *createCollectable(int collectableType);
	bool init(int collectableType);
	CC_SYNTHESIZE(double, addmoveSpeed, addMoveSpeed)
	CC_SYNTHESIZE(double, addradiusSize, addRadiusSize)
	CC_SYNTHESIZE(double, addtearSpeed, addTearSpeed)
	CC_SYNTHESIZE(int, addtearExistTime, addTearExistTime)
	CC_SYNTHESIZE(int, addhealth, addHealth)
	CC_SYNTHESIZE(double, addattack, addAttack)
	CC_SYNTHESIZE(bool, enFly, EnFly)
};

#endif // !_COLLECTABLE_H_
