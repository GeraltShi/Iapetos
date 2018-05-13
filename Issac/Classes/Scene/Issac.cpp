//
//  Issac.cpp
//  Issac
//
//  Created by 光梓 on 13/05/2018.
//

#include "Issac.hpp"
#include "cocos2d.h"

using namespace cocos2d;

Issac::~Issac()
{
    CC_SAFE_RELEASE(idleAnimate);
    CC_SAFE_RELEASE(moveAnimate);
}

Issac * Issac::create()
{
    Issac * issac = new Issac();
    if(issac && issac->initWithFile("idle_1.png"))
    {
        issac->autorelease();
        issac->initPlayer();
        return issac;
    }
    
    CC_SAFE_DELETE(issac);
    return NULL;
}

void Issac::initPlayer()
{
    moving = false;
    char str[100] = {0};
    
    Vector<SpriteFrame*> idleAnimFrames(6);
    for(int i = 1; i <= 2; i++) //Iterate for the number of images you have
    {
        sprintf(str, "idle_%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,40,160)); //The size of the images in an action should be the same
        idleAnimFrames.pushBack(frame);
    }
    
    auto idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.20f);
    idleAnimate = Animate::create(idleAnimation);
    idleAnimate->retain(); //Retain to use it later
    this->runAction(RepeatForever::create(idleAnimate)); //This will be the starting animation
    
    Vector<SpriteFrame*> moveAnimFrames(6);
    for(int i = 1; i <= 4; i++)
    {
        sprintf(str, "move_%i.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,68,160));
        moveAnimFrames.pushBack(frame);
    }
    
    auto moveAnimation = Animation::createWithSpriteFrames(moveAnimFrames, 0.09f);
    moveAnimate = Animate::create(moveAnimation);
    moveAnimate->retain();
}

void Issac::move(int direction)
{
    //this->stopAllActions();
    //this->runAction(RepeatForever::create(moveAnimate));
    //TODO 动画
    //direction = directionParam;
    
    const int moveSpeed = 6.5;
    int offsetX = 0, offsetY = 0;
    //Todo 以身体作为Position计算，如有需要可重新定义锚点，头只是跟着身体动
    switch (direction)
    {
            //012
            //345
            //678
        case 3:if(this->getPositionX() > 135){
            offsetX = -moveSpeed;
        }
        else {
            offsetX = 0;
        }
            break;
        case 5:if(this->getPositionX() < 749)
        {offsetX = moveSpeed;
        }
        else {
            offsetX = 0;
        }
            break;
        case 1:if(this->getPositionY() < 500)
        {offsetY = moveSpeed;
        }
        else {
            offsetY = 0;
        }
            break;
        case 7:if(this->getPositionY() > 190)
        {offsetY = -moveSpeed;
        }
        else {
            offsetY = 0;
        }
            break;
            
        case 0:if(this->getPositionX() > 135)
            offsetX = -moveSpeed;
        else offsetX = 0;
            if(this->getPositionY() < 500)
                offsetY = moveSpeed;
            else offsetY = 0;
            break;
            
        case 2:if(this->getPositionX() < 749)
            offsetX = moveSpeed;
        else offsetX = 0;
            if(this->getPositionY() < 500)
                offsetY = moveSpeed;
            else offsetY = 0;
            break;
            
        case 6:if(this->getPositionX() > 135)
            offsetX = -moveSpeed;
        else offsetX = 0;
            if(this->getPositionY() > 190)
                offsetY = -moveSpeed;
            else offsetY = 0;
            break;
            
        case 8:if(this->getPositionX() < 749)
            offsetX = moveSpeed;
        else offsetX = 0;
            if(this->getPositionY() > 190)
                offsetY = -moveSpeed;
            else offsetY = 0;
            break;
            
        case 4:
            offsetX = 0;
            offsetY = 0;
            break;
        default:
            break;
    }
    auto new_posX = this->getPositionX() + offsetX;
    auto new_posY = this->getPositionY() + offsetY;
    const auto MoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
    this->runAction(MoveTo);
}

void Issac::idle()
{
    moving = false;
    this->stopAllActions();
    this->runAction(RepeatForever::create(idleAnimate));
}
