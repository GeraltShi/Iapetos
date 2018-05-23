#include "Issac.hpp"
#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;
# define root2 1.41421356
//Issac::~Issac()
//{
//    CC_SAFE_RELEASE(idleAnimate);
//    CC_SAFE_RELEASE(moveAnimate);
//}
Issac * Issac::createWithTexture(cocos2d::Texture2D *texture_)
{
    Issac * sprite = new Issac();
    SpriteFrame *headFrame = SpriteFrame::createWithTexture(texture_, Rect(0,0,32,32));
    Sprite * headSprite = Sprite::createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(texture_, Rect(0,32,32,32));
    Sprite * bodySprite = Sprite::createWithSpriteFrame(bodyFrame);
    sprite->texture = texture_;
    sprite->addChild(headSprite,1,"head");
    sprite->addChild(bodySprite,0,"body");
    headSprite->setPosition(Vec2(0,10));
    sprite->setPosition(Vec2(442, 286));
    sprite->lefthead = SpriteFrame::createWithTexture(texture_, cocos2d::Rect(64,0,32,32));
    sprite->righthead = SpriteFrame::createWithTexture(texture_, cocos2d::Rect(64,0,32,32));
    sprite->uphead = SpriteFrame::createWithTexture(texture_, cocos2d::Rect(128,0,32,32));
    sprite->downhead = SpriteFrame::createWithTexture(texture_, cocos2d::Rect(0,0,32,32));
    SpriteFrame* frame0 = SpriteFrame::createWithTexture(texture_, Rect(32*6,32*0,32,32));
    SpriteFrame* frame1 = SpriteFrame::createWithTexture(texture_, Rect(32*7,32*0,32,32));
    SpriteFrame* frame2 = SpriteFrame::createWithTexture(texture_, Rect(32*0,32*1,32,32));
    SpriteFrame* frame3 = SpriteFrame::createWithTexture(texture_, Rect(32*1,32*1,32,32));
    SpriteFrame* frame4 = SpriteFrame::createWithTexture(texture_, Rect(32*2,32*1,32,32));
    SpriteFrame* frame5 = SpriteFrame::createWithTexture(texture_, Rect(32*3,32*1,32,32));
    SpriteFrame* frame6 = SpriteFrame::createWithTexture(texture_, Rect(32*4,32*1,32,32));
    SpriteFrame* frame7 = SpriteFrame::createWithTexture(texture_, Rect(32*5,32*1,32,32));
    SpriteFrame* frame8 = SpriteFrame::createWithTexture(texture_, Rect(32*6,32*1,32,32));
    SpriteFrame* frame9 = SpriteFrame::createWithTexture(texture_, Rect(32*7,32*1,32,32));
    sprite->animFrames.pushBack(frame0);
    sprite->animFrames.pushBack(frame1);
    sprite->animFrames.pushBack(frame2);
    sprite->animFrames.pushBack(frame3);
    sprite->animFrames.pushBack(frame4);
    sprite->animFrames.pushBack(frame5);
    sprite->animFrames.pushBack(frame6);
    sprite->animFrames.pushBack(frame7);
    sprite->animFrames.pushBack(frame8);
    sprite->animFrames.pushBack(frame9);
    sprite->animation = Animation::createWithSpriteFrames(sprite->animFrames, 0.1f);
    sprite->animate = Animate::create(sprite->animation);
    if (sprite)
    {
        sprite->autorelease(); return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Issac::move(int walk_direction, int head_direction)
{
    // Mask, 用于walk_direction和head_direction合并成direction
    int walk_mask;
    int head_mask;
    if(head_direction == 5){
        walk_mask = 1;
        head_mask = 0;
    } else {
        walk_mask = 0;
        head_mask = 1;
    }
    int direction = walk_direction * walk_mask + head_direction * head_mask;
    const int moveSpeed = 6.5;
    int offsetX = 0, offsetY = 0;
    Sprite * newHead;    //TODO 换头会导致绘制节点增加
    switch (walk_direction)
    {
            //123
            //456
            //789
        case 4://左
            if(this->getPositionX() > 135){ offsetX = -moveSpeed;}
            else {offsetX = 0;}
            break;
        
        case 6://右
            if(this->getPositionX() < 749){ offsetX = moveSpeed;}
            else {offsetX = 0;}
            break;
        
        case 2://上
            if(this->getPositionY() < 500){ offsetY = moveSpeed;}
            else {offsetY = 0;}
            break;
            
        case 8://下
            if(this->getPositionY() > 190){offsetY = -moveSpeed;}
            else {offsetY = 0;}
            break;
            
        case 1://左上
            if(this->getPositionX() > 135) offsetX = -moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() < 500) offsetY = moveSpeed/root2;
            else offsetY = 0;
            break;
            
        case 3://右上
            if(this->getPositionX() < 749) offsetX = moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() < 500) offsetY = moveSpeed/root2;
            else offsetY = 0;
            break;
        
        case 7://左下
            if(this->getPositionX() > 135) offsetX = -moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() > 190) offsetY = -moveSpeed/root2;
            else offsetY = 0;
            break;
            
        case 9://右下
            if(this->getPositionX() < 749) offsetX = moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() > 190) offsetY = -moveSpeed/root2;
            else offsetY = 0;
            break;
            
        case 5://无，头要默认复位
            offsetX = 0;
            offsetY = 0;
            this->stopActionByTag(1);
            break;
            
        default:
            break;
    }
    switch (direction) {
        case 1: case 2: case 3:
            if(head_tmp != 2){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(uphead);
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 2;
            }
            break;
        case 4:
            if(head_tmp != 4){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(lefthead);
                newHead->setFlippedX(true);
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 4;
            }
            break;
        case 5:
            if(head_tmp != 8){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(downhead);
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 8;
            }
            break;
        case 6:
            if(head_tmp != 6){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(righthead);
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 6;
            }
            break;
        case 7: case 8: case 9:
            if(head_tmp != 8){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(downhead);
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 8;
            }
            break;
        default:
            break;
    }
    auto new_posX = getPositionX() + offsetX;
    auto new_posY = getPositionY() + offsetY;
    ActionInterval * MoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
    std::cout << animFrames.size() << std::endl;
    Action * action = Spawn::create(MoveTo, NULL);
    this->runAction(action);
    //TODO 移动动画
}
