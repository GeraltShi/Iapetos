#ifndef _TEAR_H_
#define	_TEAR_H_

#include "cocos2d.h"
#include "Moveable.h"

USING_NS_CC;
using namespace std;

class Tear : public Moveable {
public:
	static Tear *createTear();
	virtual bool init();
	virtual void createPhyBody();
	CREATE_FUNC(Tear)
};


#endif
