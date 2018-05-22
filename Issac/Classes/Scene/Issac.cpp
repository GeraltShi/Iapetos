#include "Issac.hpp"
#include "cocos2d.h"

using namespace cocos2d;

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
    auto frame0 = SpriteFrame::createWithTexture(texture_, Rect(32*6,32*0,32,32));
    auto frame1 = SpriteFrame::createWithTexture(texture_, Rect(32*7,32*0,32,32));
    auto frame2 = SpriteFrame::createWithTexture(texture_, Rect(32*0,32*1,32,32));
    auto frame3 = SpriteFrame::createWithTexture(texture_, Rect(32*1,32*1,32,32));
    auto frame4 = SpriteFrame::createWithTexture(texture_, Rect(32*2,32*1,32,32));
    auto frame5 = SpriteFrame::createWithTexture(texture_, Rect(32*3,32*1,32,32));
    auto frame6 = SpriteFrame::createWithTexture(texture_, Rect(32*4,32*1,32,32));
    auto frame7 = SpriteFrame::createWithTexture(texture_, Rect(32*5,32*1,32,32));
    auto frame8 = SpriteFrame::createWithTexture(texture_, Rect(32*6,32*1,32,32));
    auto frame9 = SpriteFrame::createWithTexture(texture_, Rect(32*7,32*1,32,32));
    
    auto frame10 = SpriteFrame::createWithTexture(texture_, Rect(32*0,32*2,32,32));
    auto frame11 = SpriteFrame::createWithTexture(texture_, Rect(32*1,32*2,32,32));
    auto frame12 = SpriteFrame::createWithTexture(texture_, Rect(32*2,32*2,32,32));
    auto frame13 = SpriteFrame::createWithTexture(texture_, Rect(32*3,32*2,32,32));
    auto frame14 = SpriteFrame::createWithTexture(texture_, Rect(32*4,32*2,32,32));
    auto frame15 = SpriteFrame::createWithTexture(texture_, Rect(32*5,32*2,32,32));
    auto frame16 = SpriteFrame::createWithTexture(texture_, Rect(32*6,32*2,32,32));
    auto frame17 = SpriteFrame::createWithTexture(texture_, Rect(32*7,32*2,32,32));
    auto frame18 = SpriteFrame::createWithTexture(texture_, Rect(32*0,32*3,32,32));
    auto frame19 = SpriteFrame::createWithTexture(texture_, Rect(32*1,32*3,32,32));
    
    Vector<cocos2d::SpriteFrame *> array;
    array.clear();
    array.pushBack(frame0);
    array.pushBack(frame1);
    array.pushBack(frame2);
    array.pushBack(frame3);
    array.pushBack(frame4);
    array.pushBack(frame5);
    array.pushBack(frame6);
    array.pushBack(frame7);
    array.pushBack(frame8);
    array.pushBack(frame9);
    auto animation = Animation::createWithSpriteFrames(array, 0.1f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    sprite->bodyAction = Animate::create(animation);
    if (sprite)
    {
        sprite->autorelease(); return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Issac::move(int direction)
{
//    this->runAction(bodyAction);
    const int moveSpeed = 6.5;
    int offsetX = 0, offsetY = 0;
    Sprite * newHead;    //TODO 换头会导致绘制节点增加
    //Todo 以身体作为Position计算，如有需要可重新定义锚点，头只是跟着身体动
    switch (direction)
    {
            //012
            //345
            //678
        case 3:{//左
            if(this->getPositionX() > 135){
                offsetX = -moveSpeed;
            }
            else {
                offsetX = 0;
            }
            this->removeChild(this->getChildByName("head"), true);
            Sprite * newHead = Sprite::createWithSpriteFrame(lefthead);
            newHead->setFlippedX(true);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
        case 5:{//右
            if(this->getPositionX() < 749){
                offsetX = moveSpeed;
            }
            else {
                offsetX = 0;
            }
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(righthead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
        case 1:{//上
            if(this->getPositionY() < 500){
                offsetY = moveSpeed;
            }
            else {
                offsetY = 0;
            }
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(uphead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;}
        case 7:{//下
            if(this->getPositionY() > 190)
            {
                offsetY = -moveSpeed;
            }
            else {
                offsetY = 0;
            }
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(downhead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;}
            
        case 0:{//左上
            if(this->getPositionX() > 135)
                offsetX = -moveSpeed;
            else offsetX = 0;
            if(this->getPositionY() < 500)
                offsetY = moveSpeed;
            else offsetY = 0;
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(uphead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
            
        case 2:{//右上
            if(this->getPositionX() < 749)
                offsetX = moveSpeed;
            else offsetX = 0;
            if(this->getPositionY() < 500)
                offsetY = moveSpeed;
            else offsetY = 0;
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(uphead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
            
        case 6:{//左下
            if(this->getPositionX() > 135)
                offsetX = -moveSpeed;
            else offsetX = 0;
            if(this->getPositionY() > 190)
                offsetY = -moveSpeed;
            else offsetY = 0;
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(downhead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
            
        case 8:{//右下
            if(this->getPositionX() < 749)
                offsetX = moveSpeed;
            else offsetX = 0;
            if(this->getPositionY() > 190)
                offsetY = -moveSpeed;
            else offsetY = 0;
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(downhead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
            
        case 4:{//无，头要默认复位
            offsetX = 0;
            offsetY = 0;
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(downhead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
            
        default:
            break;
    }
    auto new_posX = getPositionX() + offsetX;
    auto new_posY = getPositionY() + offsetY;
    const auto MoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
    this->runAction(MoveTo);
}
//方向键更新头，与射击有关
void Issac::updatehead(int direction){
    SpriteFrame * newFrame;
    Sprite * newHead;
    switch (direction) {
        case 0:{//上
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(uphead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
        case 1:{//下
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(downhead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            
            break;
        }
        case 2:{//左
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(lefthead);
            newHead->setFlippedX(true);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            break;
        }
        case 3:{//右
            this->removeChild(this->getChildByName("head"), true);
            newHead = Sprite::createWithSpriteFrame(righthead);
            newHead->setPosition(Vec2(0,10));
            this->addChild(newHead,1);
            
            break;
        }
        default:
            break;
    }
}

