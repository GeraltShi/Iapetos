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

    //不要将Texture保存在类,用的时候直接从TextureCache中获取
    const auto texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/characters/costumes/character_001_isaac.png");

    SpriteFrame *headFrame = SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32));
    Sprite * headSprite = Sprite::createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(texture_, Rect(0, 32, 32, 32));
    Sprite * bodySprite = Sprite::createWithSpriteFrame(bodyFrame);

    this->addChild(headSprite, 1, "head");
    this->addChild(bodySprite, 0, "body");
    headSprite->setPosition(Vec2(0, 10));
    this->setPosition(Vec2(221, 143));

    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "lefthead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "righthead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(128, 0, 32, 32)), "uphead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32)),"downhead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 0, 32, 32)),"frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 0, 32, 32)),"frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32 * 1, 32, 32)),"frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32 * 1, 32, 32)),"frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 2, 32 * 1, 32, 32)),"frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 3, 32 * 1, 32, 32)),"frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 4, 32 * 1, 32, 32)),"frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 5, 32 * 1, 32, 32)),"frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 1, 32, 32)),"frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 1, 32, 32)),"frame9");
    
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32, 0, 32, 32)),"downshake");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(96, 0, 32, 32)),"rightshake");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(160, 0, 32, 32)),"upshake");
    return true;
}


void Issac::move(int walk_direction, int head_direction)
{
    //直接获取缓存，不要将SpriteFrame保存在类中
    auto spriteCache = SpriteFrameCache::getInstance();
    
    const auto frame0 = spriteCache->getSpriteFrameByName("frame0");
    const auto frame1 = spriteCache->getSpriteFrameByName("frame1");
    const auto frame2 = spriteCache->getSpriteFrameByName("frame2");
    const auto frame3 = spriteCache->getSpriteFrameByName("frame3");
    const auto frame4 = spriteCache->getSpriteFrameByName("frame4");
    const auto frame5 = spriteCache->getSpriteFrameByName("frame5");
    const auto frame6 = spriteCache->getSpriteFrameByName("frame6");
    const auto frame7 = spriteCache->getSpriteFrameByName("frame7");
    const auto frame8 = spriteCache->getSpriteFrameByName("frame8");
    const auto frame9 = spriteCache->getSpriteFrameByName("frame9");
    
    const auto uphead = spriteCache->getSpriteFrameByName("uphead");
    const auto lefthead = spriteCache->getSpriteFrameByName("lefthead");
    const auto righthead = spriteCache->getSpriteFrameByName("righthead");
    
    const auto downhead = spriteCache->getSpriteFrameByName("downhead");
    const auto downshake = spriteCache->getSpriteFrameByName("downshake");
    Vector<SpriteFrame*> downshakeFrames;
    downshakeFrames.pushBack(downhead);
    downshakeFrames.pushBack(downshake);
    Animation * downshakeAnimation = Animation::createWithSpriteFrames(downshakeFrames, 0.1f);
    downshakeAnimation->setLoops(-1);
    downshakeAnimation->setRestoreOriginalFrame(true);
    Animate * downshakeAnimate = Animate::create(downshakeAnimation);
    
    Vector<SpriteFrame*> animFrames;
    animFrames.pushBack(frame0);
    animFrames.pushBack(frame1);
    animFrames.pushBack(frame2);
    animFrames.pushBack(frame3);
    animFrames.pushBack(frame4);
    animFrames.pushBack(frame5);
    animFrames.pushBack(frame6);
    animFrames.pushBack(frame7);
    animFrames.pushBack(frame8);
    animFrames.pushBack(frame9);
    Animation * animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    Animate * animate = Animate::create(animation);
    
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
    const int direction = walk_direction * walk_mask + head_direction * head_mask;
    const double moveSpeed = 6.5;
    int offset_x = 0, offset_y = 0;
    Sprite * new_head;    //TODO 换头会导致绘制节点增加
    switch (walk_direction)
    {
            //123
            //456
            //789
        case 4://左
            if(this->getPositionX() > 60){ offset_x = -moveSpeed;}
            else {offset_x = 0;}
            prev_walk_orientation = 4;
            break;
        
        case 6://右
            if(this->getPositionX() < 441-60){ offset_x = moveSpeed;}
            else {offset_x = 0;}
            prev_walk_orientation = 6;
            break;
        
        case 2://上
            if(this->getPositionY() < 286-60){ offset_y = moveSpeed;}
            else {offset_y = 0;}
            prev_walk_orientation = 2;
            break;
            
        case 8://下
            if(this->getPositionY() > 60){offset_y = -moveSpeed;}
            else {offset_y = 0;}
            prev_walk_orientation = 8;
            break;
            
        case 1://左上
            if(this->getPositionX() > 60) offset_x = -moveSpeed/root2;
            else offset_x = 0;
            if(this->getPositionY() < 441-60) offset_y = moveSpeed/root2;
            else offset_y = 0;
            prev_walk_orientation = 1;
            break;
            
        case 3://右上
            if(this->getPositionX() < 441-60) offset_x = moveSpeed/root2;
            else offset_x = 0;
            if(this->getPositionY() < 286-60) offset_y = moveSpeed/root2;
            else offset_y = 0;
            prev_walk_orientation = 3;
            break;
        
        case 7://左下
            if(this->getPositionX() > 60) offset_x = -moveSpeed/root2;
            else offset_x = 0;
            if(this->getPositionY() > 60) offset_y = -moveSpeed/root2;
            else offset_y = 0;
            prev_walk_orientation = 7;
            break;
            
        case 9://右下
            if(this->getPositionX() < 441-60) offset_x = moveSpeed/root2;
            else offset_x = 0;
            if(this->getPositionY() > 60) offset_y = -moveSpeed/root2;
            else offset_y = 0;
            prev_walk_orientation = 9;
            break;
            
        case 5://无，头要默认复位
            offset_x = 0;
            offset_y = 0;
            this->stopActionByTag(1);
            prev_walk_orientation = 5;
            break;
            
        default:
            break;
    }
    switch (direction) {
        case 1: case 2: case 3:
            if(prev_head_orientation != 2){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("uphead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1,"head");
                prev_head_orientation = 2;
            }
            break;
        case 4:
            if(prev_head_orientation != 4){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("lefthead"));
                new_head->setFlippedX(true);
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 4;
            }
            break;
        case 5:
            if(prev_head_orientation != 8){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("downhead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 8;
            }
            break;
        case 6:
            if(prev_head_orientation != 6){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("righthead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 6;
            }
            break;
        case 7: case 8: case 9:
            if(prev_head_orientation != 8){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("downhead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 8;
                this->getChildByName("head")->runAction(downshakeAnimate);
            }
            break;
        default:
            break;
    }
    if(walk_direction != 5){
        const auto new_posX = getPositionX() + offset_x;
        const auto new_posY = getPositionY() + offset_y;
        ActionInterval * MoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
        std::cout << animFrames.size() << std::endl;
        Action * action = Spawn::create(MoveTo, NULL);
        this->runAction(action);
        if(walk_direction != prev_walk_orientation){
            this->getChildByName("body")->stopAction(animate);
            this->getChildByName("body")->runAction(animate);
        }
    }
    
    
    //TODO 移动动画
}

int Issac::get_prev_head_orientation() const
{
    return prev_head_orientation;
}
