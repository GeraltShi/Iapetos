#ifndef _DOOR_H_
#define _DOOR_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Door : public Sprite
{
  public:
	static Door *createDoor(int doorType, const string &doorStyle, const Size &winSize);
	bool init(int doorType, const string &doorStyle, const Size &winSize);
};

#endif // !_STONE_H_
