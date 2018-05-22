#ifndef Issac_hpp
#define Issac_hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
using namespace std;
class Issac : public cocos2d::Sprite {
public:
    static Issac * createWithTexture(cocos2d::Texture2D *texture);
    cocos2d::Animate * idleAnimate;
    cocos2d::Animate * moveAnimate;
    void move(int walk_direction, int head_direction);
    cocos2d::Texture2D * texture;
    cocos2d::SpriteFrame * lefthead;
    cocos2d::SpriteFrame * righthead;
    cocos2d::SpriteFrame * uphead;
    cocos2d::SpriteFrame * downhead;
    int head_tmp = 5;
private:
    cocos2d::Action * bodyAction;
    bool moving;
    void initPlayer();
};
#endif /* Issac_hpp */
