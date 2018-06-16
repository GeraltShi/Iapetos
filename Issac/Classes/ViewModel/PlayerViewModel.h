#ifndef PLAYER_VIEW_MODEL_
#define PLAYER_VIEW_MODEL_

#include "cocos2d.h"

USING_NS_CC;

class PlayerViewModel
{
    CC_SYNTHESIZE(int, health, Health)
    CC_SYNTHESIZE(double, attack_, Attack)
    CC_SYNTHESIZE(double, move_speed_, MoveSpeed)
    CC_SYNTHESIZE(double, tear_speed_, TearSpeed)
    CC_SYNTHESIZE(int, tear_existing_time, TearExistingTime)
    CC_SYNTHESIZE(double, shoot_interval_, ShootInterval)
    CC_SYNTHESIZE(double, radius_size_, RadiusSize)
    CC_SYNTHESIZE(double, body_mass_, BodyMass)
    CC_SYNTHESIZE(bool, en_fly_, EnFly)
    CC_SYNTHESIZE(bool, en_bounce_, EnBounce)
};

#endif