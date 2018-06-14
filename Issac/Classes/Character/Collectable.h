#ifndef _COLLECTABLE_H_
#define _COLLECTABLE_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

#include "Moveable.h"

class Collectable : public Moveable
{
public:
	static Collectable *createCollectable(int collectableType);
	bool init(int collectableType);
	virtual void createPhyBody();
};

#endif // !_COLLECTABLE_H_
