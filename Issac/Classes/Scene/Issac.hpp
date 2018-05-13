#ifndef Issac_hpp
#define Issac_hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
using namespace std;
class Issac : public cocos2d::Sprite {
public:
    cocos2d::Animate * idleAnimate;
    cocos2d::Animate * moveAnimate;
    static Issac * create(void);
    void move(int direction);
    void updatehead(int direction);
    //void fire(float dt);
    //vector <Sprite *> tears;
private:
    ~Issac();
    
    bool moving;
    //int direction;
    
    void initPlayer();
};
#endif /* Issac_hpp */
