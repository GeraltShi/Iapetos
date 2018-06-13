#include "PlayerService.h"
#include "cocos2d.h"

USING_NS_CC;

PlayerService* PlayerService::getInstance()
{
    if (inst_ == nullptr)
    {
        inst_ = new (std::nothrow) PlayerService();
        CCASSERT(inst_, "FATAL: Not enough memory");
    }

    return inst_;
}

void PlayerService::init()
{
    model_ = PlayerViewModel();

    model_.setHealth(max_health);
}

int PlayerService::getHealth() const
{
    return model_.getHealth();
}

void PlayerService::setHealth(int health)
{
    model_.setHealth(health);
}

void PlayerService::decreaseHealth(int dHealth)
{
    model_.setHealth(model_.getHealth() - dHealth);
}

void PlayerService::increaseHealth(int dHealth)
{
    model_.setHealth(model_.getHealth() + dHealth);
}

PlayerService::PlayerService()
{
    max_health = 7;//初始血量6个半心（3颗心）
}


PlayerService* PlayerService::inst_ = nullptr;