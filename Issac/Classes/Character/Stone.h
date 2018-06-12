#ifndef _STONE_H_
#define _STONE_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Stone : public Sprite
{
  public:
	static Stone *createStone(int type_, Size stoneSize_);
	bool init(int stoneType, Size stoneSize);
};

#endif // !_STONE_H_
