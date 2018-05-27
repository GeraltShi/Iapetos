#include "Issac.hpp"
#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;
# define root2 1.41421356

Issac *Issac::createIssac()
{
    return create();
}

Sprite *Issac::createSprite()
{
    return create();
}

bool Issac::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    auto texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/characters/costumes/character_001_isaac.png");

    

    SpriteFrame *headFrame = SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32));
    Sprite * headSprite = Sprite::createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(texture_, Rect(0, 32, 32, 32));
    Sprite * bodySprite = Sprite::createWithSpriteFrame(bodyFrame);
    this->texture = texture_;
    this->addChild(headSprite, 1, "head");
    this->addChild(bodySprite, 0, "body");
    headSprite->setPosition(Vec2(0, 10));
    this->setPosition(Vec2(221, 143));
    this->lefthead = SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32));
    this->righthead = SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32));
    this->uphead = SpriteFrame::createWithTexture(texture_, Rect(128, 0, 32, 32));
    this->downhead = SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32));
    SpriteFrame* frame0 = SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 0, 32, 32));
    SpriteFrame* frame1 = SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 0, 32, 32));
    SpriteFrame* frame2 = SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32 * 1, 32, 32));
    SpriteFrame* frame3 = SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32 * 1, 32, 32));
    SpriteFrame* frame4 = SpriteFrame::createWithTexture(texture_, Rect(32 * 2, 32 * 1, 32, 32));
    SpriteFrame* frame5 = SpriteFrame::createWithTexture(texture_, Rect(32 * 3, 32 * 1, 32, 32));
    SpriteFrame* frame6 = SpriteFrame::createWithTexture(texture_, Rect(32 * 4, 32 * 1, 32, 32));
    SpriteFrame* frame7 = SpriteFrame::createWithTexture(texture_, Rect(32 * 5, 32 * 1, 32, 32));
    SpriteFrame* frame8 = SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 1, 32, 32));
    SpriteFrame* frame9 = SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 1, 32, 32));
    this->animFrames.pushBack(frame0);
    this->animFrames.pushBack(frame1);
    this->animFrames.pushBack(frame2);
    this->animFrames.pushBack(frame3);
    this->animFrames.pushBack(frame4);
    this->animFrames.pushBack(frame5);
    this->animFrames.pushBack(frame6);
    this->animFrames.pushBack(frame7);
    this->animFrames.pushBack(frame8);
    this->animFrames.pushBack(frame9);
    this->animation = Animation::createWithSpriteFrames(this->animFrames, 0.1f);
    this->animate = Animate::create(this->animation);

    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "lefthead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "righthead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(128, 0, 32, 32)), "uphead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32)),"downhead");

    return true;
}


void Issac::move(int walk_direction, int head_direction)
{
    auto spriteCache = SpriteFrameCache::getInstance();

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
            if(this->getPositionX() > 60){ offsetX = -moveSpeed;}
            else {offsetX = 0;}
            break;
        
        case 6://右
            if(this->getPositionX() < 441-60){ offsetX = moveSpeed;}
            else {offsetX = 0;}
            break;
        
        case 2://上
            if(this->getPositionY() < 286-60){ offsetY = moveSpeed;}
            else {offsetY = 0;}
            break;
            
        case 8://下
            if(this->getPositionY() > 60){offsetY = -moveSpeed;}
            else {offsetY = 0;}
            break;
            
        case 1://左上
            if(this->getPositionX() > 60) offsetX = -moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() < 441-60) offsetY = moveSpeed/root2;
            else offsetY = 0;
            break;
            
        case 3://右上
            if(this->getPositionX() < 441-60) offsetX = moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() < 286-60) offsetY = moveSpeed/root2;
            else offsetY = 0;
            break;
        
        case 7://左下
            if(this->getPositionX() > 60) offsetX = -moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() > 60) offsetY = -moveSpeed/root2;
            else offsetY = 0;
            break;
            
        case 9://右下
            if(this->getPositionX() < 441-60) offsetX = moveSpeed/root2;
            else offsetX = 0;
            if(this->getPositionY() > 60) offsetY = -moveSpeed/root2;
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
                newHead = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("uphead"));
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 2;
            }
            break;
        case 4:
            if(head_tmp != 4){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("lefthead"));
                newHead->setFlippedX(true);
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 4;
            }
            break;
        case 5:
            if(head_tmp != 8){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("downhead"));
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 8;
            }
            break;
        case 6:
            if(head_tmp != 6){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("righthead"));
                newHead->setPosition(Vec2(0,10));
                this->addChild(newHead,1);
                head_tmp = 6;
            }
            break;
        case 7: case 8: case 9:
            if(head_tmp != 8){
                this->removeChild(this->getChildByName("head"), true);
                newHead = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("downhead"));
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
