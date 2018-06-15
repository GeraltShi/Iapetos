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
    int getHealth() const;
    void setHealth(int health);
    void decreaseHealth(int dHealth);
    void increaseHealth(int dHealth);
    double getAttack() const;
    void setAttack(double attack);
    void decreaseAttack(double dAttack);
    void increaseAttack(double dAttack);

private:
    PlayerService();
    static PlayerService *inst_;

    PlayerViewModel model_;
};


#endif