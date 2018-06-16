#ifndef PLAYER_SERVICE_
#define PLAYER_SERVICE_

#include "ViewModel/PlayerViewModel.h"
#include "cocos2d.h"

class PlayerService
{
    CC_SYNTHESIZE(int, max_health, MaxHealth)
    CC_SYNTHESIZE(double, defaultAttack_, DefaultAttack)

public:
    static PlayerService *getInstance();
    void init();

    int getHealth() const;//生命值
    void setHealth(int health);
    void decreaseHealth(int dHealth);
    void increaseHealth(int dHealth);

    double getAttack() const;//攻击力
    void setAttack(double attack);
    void decreaseAttack(double dAttack);
    void increaseAttack(double dAttack);

    double getMoveSpeed() const;//移动速度
    void setMoveSpeed(double move_speed);
    void decreaseMoveSpeed(double dmove_speed);
    void increaseMoveSpeed(double dmove_speed);

    double getTearSpeed() const;//弹速
    void setTearSpeed(double tear_speed);
    void decreaseTearSpeed(double dtear_speed);
    void increaseTearSpeed(double dtear_speed);

    int getTearExistingTime() const;//射程
    void setTearExistingTime(int tear_existing_time);
    void decreaseTearExistingTime(double dtear_existing_time);
    void increaseTearExistingTime(double dtear_existing_time);


    double getShootInterval() const;//射击间隔
    void setShootInterval(double shoot_interval);
    void decreaseShootInterval(double dshoot_interval);
    void increaseShootInterval(double dshoot_interval);


private:
    PlayerService();
    static PlayerService *inst_;
    PlayerViewModel model_;
};


#endif