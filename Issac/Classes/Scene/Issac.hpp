#ifndef Issac_hpp
#define Issac_hpp

#include <stdio.h>
#include "cocos2d.h"

class Issac : public cocos2d::Sprite {
public:
    cocos2d::Animate * idleAnimate;
    cocos2d::Animate * moveAnimate;
    static Issac * create(void);
    void move(int direction);
    void updatehead(int direction);
private:
    ~Issac();
    
    bool moving;
    //int direction;
    
    void initPlayer();
};
#endif /* Issac_hpp */
