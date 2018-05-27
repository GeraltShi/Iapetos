#ifndef Issac_hpp
#define Issac_hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Issac : public cocos2d::Sprite {
public:
    //static Issac * createWithTexture(cocos2d::Texture2D *texture);

    static Issac *createIssac();
    static Sprite *createSprite();
    virtual bool init();
    CREATE_FUNC(Issac);


    Animate * idleAnimate;
    Animate * moveAnimate;
    void move(int walk_direction, int head_direction);
    Texture2D * texture;
    SpriteFrame * lefthead;
    SpriteFrame * righthead;
    SpriteFrame * uphead;
    SpriteFrame * downhead;

    
    Vector<SpriteFrame*> animFrames;
    Animation * animation;
    Animate * animate;
    int head_tmp = 5;
private:
    bool moving;
    void initPlayer();
};
#endif /* Issac_hpp */
