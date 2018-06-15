#ifndef _TEAR_H_
#define _TEAR_H_

#include "cocos2d.h"
#include "Moveable.h"

USING_NS_CC;
using namespace std;

class Tear : public Moveable
{
  public:
	static Tear *createTear();
	virtual bool init();
	virtual void createPhyBody();
	CREATE_FUNC(Tear)
    virtual string getPoofAnimation();
    CC_SYNTHESIZE_RETAIN(Animation *, poof_animation, PoofAnimation)
};

class MonsterTear : public Tear
{
public:
    static MonsterTear *createMonsterTear();
    virtual bool init();
    virtual void createPhyBody();
    CREATE_FUNC(MonsterTear)
    virtual string getPoofAnimation();
    CC_SYNTHESIZE_RETAIN(Animation *, mt_poof_animation, MtPoofAnimation)
};

#endif
