//
//  Player.hpp
//  Issac
//
//  Created by 光梓 on 08/03/2018.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
    cocos2d::Animate * idleAnimate;
    cocos2d::Animate * moveAnimate;
    
    static Player * create(void);
    void move(int directionParam);
    void idle();
    
    void update();
    
private:
    ~Player();
    
    bool moving;
    int direction;
    
    void initPlayer();
};

#endif /* Player_hpp */
