#ifndef PLAYER_VIEW_MODEL_
#define PLAYER_VIEW_MODEL_

#include "cocos2d.h"

USING_NS_CC;

class PlayerViewModel
{
    CC_SYNTHESIZE(int, health, Health)
    CC_SYNTHESIZE(double, attack_, Attack)
};

#endif