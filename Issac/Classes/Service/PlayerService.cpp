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
    model_.setAttack(defaultAttack_);
    model_.setMoveSpeed(150);
    model_.setShootInterval(0.4);
    model_.setTearExistingTime(20);
    model_.setTearSpeed(100);
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

double PlayerService::getAttack() const
{
    return model_.getAttack();
}

void PlayerService::setAttack(double attack)
{
    model_.setAttack(attack);
}

void PlayerService::decreaseAttack(double dAttack)
{
    model_.setAttack(model_.getAttack() - dAttack);
}

void PlayerService::increaseAttack(double dAttack)
{
    model_.setAttack(model_.getAttack() + dAttack);
}

double PlayerService::getMoveSpeed()
{
    return model_.getMoveSpeed();
}

void PlayerService::setMoveSpeed(double move_speed)
{
    model_.setMoveSpeed(move_speed);
}

void PlayerService::decreaseMoveSpeed(double dmove_speed)
{
    model_.setMoveSpeed(model_.getMoveSpeed() - dmove_speed);
}

void PlayerService::increaseMoveSpeed(double dmove_speed)
{
    model_.setMoveSpeed(model_.getMoveSpeed() + dmove_speed);
}

double PlayerService::getTearSpeed()
{
    return model_.getTearSpeed();
}

void PlayerService::setTearSpeed(double tear_speed)
{
    model_.setTearSpeed(tear_speed);
}

void PlayerService::decreaseTearSpeed(double dtear_speed)
{
    model_.setTearSpeed(model_.getTearSpeed() - dtear_speed);
}

void PlayerService::increaseTearSpeed(double dtear_speed)
{
    model_.setTearSpeed(model_.getTearSpeed() + dtear_speed);
}

int PlayerService::getTearExistingTime()
{
    return model_.getTearExistingTime();
}

void PlayerService::setTearExistingTime(double tear_existing_time)
{
    model_, setTearExistingTime(tear_existing_time);
}

void PlayerService::decreaseTearExistingTime(double dtear_existing_time)
{
    model_.setTearExistingTime(model_.getTearExistingTime() - dtear_existing_time);
}

void PlayerService::increaseTearExistingTime(double dtear_existing_time)
{
    model_.setTearExistingTime(model_.getTearExistingTime() + dtear_existing_time);
}

double PlayerService::getShootInterval()
{
    return model_.getShootInterval();
}

void PlayerService::setShootInterval(double shoot_interval)
{
    model_.setShootInterval(shoot_interval);
}

void PlayerService::decreaseShootInterval(double dshoot_interval)
{
    model_.setShootInterval(model_.getShootInterval() - dshoot_interval);
}

void PlayerService::increaseShootInterval(double dshoot_interval)
{
    model_.setShootInterval(model_.getShootInterval() + dshoot_interval);
}

PlayerService::PlayerService()
{
    max_health = 7;//初始血量6个半心（3颗心）
    defaultAttack_ = 1.3;
}


PlayerService* PlayerService::inst_ = nullptr;