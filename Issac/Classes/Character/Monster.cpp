#include "Monster.hpp"
#include "cocos2d.h"

using namespace cocos2d;

# define ROOT2 1.41421356



Monster *Monster::createMonster()
{
    return create();
}

Sprite *Monster::createSprite()
{
    return create();
}

bool Monster::init()
{
    if (!Moveable::init())
    {
        return false;
    }

    //不要将Texture保存在类,用的时候直接从TextureCache中获取
    const auto monster_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/rebirth/monster_207_fatty.png");
    SpriteFrame *headFrame = SpriteFrame::createWithTexture(monster_texture_, Rect(0, 0, 32, 32));
    Sprite * headSprite = createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(monster_texture_, Rect(192, 224, 64, 64));
    Sprite * bodySprite = createWithSpriteFrame(bodyFrame);
    
    build_sprite_frame_cache(monster_texture_);
    build_animation_cache();
    
    this->addChild(headSprite, 1, "head");
    this->addChild(bodySprite, 0, "body");
    headSprite->setPosition(Vec2(0, 10));
    this->setPosition(Vec2(221, 143));
    
    
    return true;
}

void Monster::build_sprite_frame_cache(Texture2D *texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0,0,32,32)), "head_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32,0,32,32)), "head_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64,0,32,32)), "head_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(96,0,32,32)), "head_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(128,0,32,32)), "head_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(160,0,32,32)), "head_frame5");
    
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 32, 64, 64)), "monster_hwalk_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 32, 64, 64)), "monster_hwalk_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 32, 64, 64)), "monster_hwalk_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 32, 64, 64)), "monster_hwalk_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 32, 64, 64)), "monster_hwalk_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 5, 32, 64, 64)), "monster_hwalk_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 6, 32, 64, 64)), "monster_hwalk_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 7, 32, 64, 64)), "monster_hwalk_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 32, 64, 64)), "monster_hwalk_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 96, 64, 64)), "monster_hwalk_frame9");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 96, 64, 64)), "monster_hwalk_frame10");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 96, 64, 64)), "monster_hwalk_frame11");
    
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 160, 64, 64)), "monster_vwalk_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 160, 64, 64)), "monster_vwalk_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 160, 64, 64)), "monster_vwalk_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 160, 64, 64)), "monster_vwalk_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 160, 64, 64)), "monster_vwalk_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 5, 160, 64, 64)), "monster_vwalk_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 6, 160, 64, 64)), "monster_vwalk_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 7, 160, 64, 64)), "monster_vwalk_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 160, 64, 64)), "monster_vwalk_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 224, 64, 64)), "monster_vwalk_frame9");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 224, 64, 64)), "monster_vwalk_frame10");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 224, 64, 64)), "monster_vwalk_frame11");
}

void Monster::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto head_frame0 = spriteCache->getSpriteFrameByName("head_frame0");
    const auto head_frame1 = spriteCache->getSpriteFrameByName("head_frame1");
    const auto head_frame2 = spriteCache->getSpriteFrameByName("head_frame2");
    const auto head_frame3 = spriteCache->getSpriteFrameByName("head_frame3");
    const auto head_frame4 = spriteCache->getSpriteFrameByName("head_frame4");
    const auto head_frame5 = spriteCache->getSpriteFrameByName("head_frame5");
    Vector<SpriteFrame*> headFrames;
    headFrames.pushBack(head_frame0);
    headFrames.pushBack(head_frame1);
    headFrames.pushBack(head_frame2);
    headFrames.pushBack(head_frame3);
    headFrames.pushBack(head_frame4);
    headFrames.pushBack(head_frame5);
    Animation * head_animation = Animation::createWithSpriteFrames(headFrames, 0.1f);
    head_animation->setLoops(-1);
    head_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(head_animation, "head_animation");
    
    const auto vwalk_frame0 = spriteCache->getSpriteFrameByName("monster_vwalk_frame0");
    const auto vwalk_frame1 = spriteCache->getSpriteFrameByName("monster_vwalk_frame1");
    const auto vwalk_frame2 = spriteCache->getSpriteFrameByName("monster_vwalk_frame2");
    const auto vwalk_frame3 = spriteCache->getSpriteFrameByName("monster_vwalk_frame3");
    const auto vwalk_frame4 = spriteCache->getSpriteFrameByName("monster_vwalk_frame4");
    const auto vwalk_frame5 = spriteCache->getSpriteFrameByName("monster_vwalk_frame5");
    const auto vwalk_frame6 = spriteCache->getSpriteFrameByName("monster_vwalk_frame6");
    const auto vwalk_frame7 = spriteCache->getSpriteFrameByName("monster_vwalk_frame7");
    const auto vwalk_frame8 = spriteCache->getSpriteFrameByName("monster_vwalk_frame8");
    const auto vwalk_frame9 = spriteCache->getSpriteFrameByName("monster_vwalk_frame9");
    const auto vwalk_frame10 = spriteCache->getSpriteFrameByName("monster_vwalk_frame10");
    const auto vwalk_frame11 = spriteCache->getSpriteFrameByName("monster_vwalk_frame11");
    Vector<SpriteFrame*> vwalkFrames;
    vwalkFrames.pushBack(vwalk_frame0);
    vwalkFrames.pushBack(vwalk_frame1);
    vwalkFrames.pushBack(vwalk_frame2);
    vwalkFrames.pushBack(vwalk_frame3);
    vwalkFrames.pushBack(vwalk_frame4);
    vwalkFrames.pushBack(vwalk_frame5);
    vwalkFrames.pushBack(vwalk_frame6);
    vwalkFrames.pushBack(vwalk_frame7);
    vwalkFrames.pushBack(vwalk_frame8);
    vwalkFrames.pushBack(vwalk_frame9);
    vwalkFrames.pushBack(vwalk_frame10);
    vwalkFrames.pushBack(vwalk_frame11);
    Animation * vwalk_animation = Animation::createWithSpriteFrames(vwalkFrames, 0.1f);
    vwalk_animation->setLoops(-1);
    vwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(vwalk_animation, "monster_vwalk_animation");
    
    
    const auto hwalk_frame0 = spriteCache->getSpriteFrameByName("monster_hwalk_frame0");
    const auto hwalk_frame1 = spriteCache->getSpriteFrameByName("monster_hwalk_frame1");
    const auto hwalk_frame2 = spriteCache->getSpriteFrameByName("monster_hwalk_frame2");
    const auto hwalk_frame3 = spriteCache->getSpriteFrameByName("monster_hwalk_frame3");
    const auto hwalk_frame4 = spriteCache->getSpriteFrameByName("monster_hwalk_frame4");
    const auto hwalk_frame5 = spriteCache->getSpriteFrameByName("monster_hwalk_frame5");
    const auto hwalk_frame6 = spriteCache->getSpriteFrameByName("monster_hwalk_frame6");
    const auto hwalk_frame7 = spriteCache->getSpriteFrameByName("monster_hwalk_frame7");
    const auto hwalk_frame8 = spriteCache->getSpriteFrameByName("monster_hwalk_frame8");
    const auto hwalk_frame9 = spriteCache->getSpriteFrameByName("monster_hwalk_frame9");
    const auto hwalk_frame10 = spriteCache->getSpriteFrameByName("monster_hwalk_frame10");
    const auto hwalk_frame11 = spriteCache->getSpriteFrameByName("monster_hwalk_frame11");
    Vector<SpriteFrame*> hwalkFrames;
    hwalkFrames.pushBack(hwalk_frame0);
    hwalkFrames.pushBack(hwalk_frame1);
    hwalkFrames.pushBack(hwalk_frame2);
    hwalkFrames.pushBack(hwalk_frame3);
    hwalkFrames.pushBack(hwalk_frame4);
    hwalkFrames.pushBack(hwalk_frame5);
    hwalkFrames.pushBack(hwalk_frame6);
    hwalkFrames.pushBack(hwalk_frame7);
    hwalkFrames.pushBack(hwalk_frame8);
    hwalkFrames.pushBack(hwalk_frame9);
    hwalkFrames.pushBack(hwalk_frame10);
    hwalkFrames.pushBack(hwalk_frame11);
    Animation * hwalk_animation = Animation::createWithSpriteFrames(hwalkFrames, 0.1f);
    hwalk_animation->setLoops(-1);
    hwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(hwalk_animation, "monster_hwalk_animation");
}


void Monster::move(int walk_direction)
{
    //直接获取缓存，不要将SpriteFrame保存在类中
//    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();
    
    const auto vwalk_animation = aniCache->getAnimation("monster_vwalk_animation");
    const auto hwalk_animation = aniCache->getAnimation("monster_hwalk_animation");
    const auto head_animation = aniCache->getAnimation("head_animation");
    
    Animate * vwalk_animate = Animate::create(vwalk_animation);
    Animate * hwalk_animate = Animate::create(hwalk_animation);
    Animate * head_animate = Animate::create(head_animation);
    
    int offset_x = 0, offset_y = 0;
//    Sprite * new_head;
    switch (walk_direction)
    {
            //123
            //456
            //789
        case 4://左
            if(this->getPositionX() > 60){ offset_x = -moveSpeed;}
            else {offset_x = 0;}
            if(prev_walk_orientation != 4){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->setScaleX(-1);//翻转
                this->getChildByName("body")->runAction(hwalk_animate);
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 4;
            break;
            
        case 6://右
            if(this->getPositionX() < 441-60){ offset_x = moveSpeed;}
            else {offset_x = 0;}
            if(prev_walk_orientation != 6){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->setScaleX(1);//翻转
                this->getChildByName("body")->runAction(hwalk_animate);
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 6;
            break;
            
        case 2://上
            if(this->getPositionY() < 286-60){ offset_y = moveSpeed;}
            else {offset_y = 0;}
            if(prev_walk_orientation != 2){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate->reverse());//向上走要倒放
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 2;
            break;
            
        case 8://下
            if(this->getPositionY() > 60){offset_y = -moveSpeed;}
            else {offset_y = 0;}
            if(prev_walk_orientation != 8){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate);
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 8;
            break;
            
        case 1://左上
            if(this->getPositionX() > 60) offset_x = -moveSpeed/ROOT2;
            else offset_x = 0;
            if(this->getPositionY() < 286-60) offset_y = moveSpeed/ROOT2;
            else offset_y = 0;
            if(prev_walk_orientation != 1){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate->reverse());
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 1;
            break;
            
        case 3://右上
            if(this->getPositionX() < 441-60) offset_x = moveSpeed/ROOT2;
            else offset_x = 0;
            if(this->getPositionY() < 286-60) offset_y = moveSpeed/ROOT2;
            else offset_y = 0;
            if(prev_walk_orientation != 3){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate->reverse());
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 3;
            break;
            
        case 7://左下
            if(this->getPositionX() > 60) offset_x = -moveSpeed/ROOT2;
            else offset_x = 0;
            if(this->getPositionY() > 60) offset_y = -moveSpeed/ROOT2;
            else offset_y = 0;
            if(prev_walk_orientation != 7){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate);
                this->getChildByName("head")->runAction(head_animate);
            }
            prev_walk_orientation = 7;
            break;
            
        case 9://右下
            if(this->getPositionX() < 441-60) offset_x = moveSpeed/ROOT2;
            else offset_x = 0;
            if(this->getPositionY() > 60) offset_y = -moveSpeed/ROOT2;
            else offset_y = 0;
            if(prev_walk_orientation != 9){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate);
            }
            prev_walk_orientation = 9;
            break;
            
        case 5://无，头要默认复位
            offset_x = 0;
            offset_y = 0;
            this->getChildByName("body")->stopAllActions();
            prev_walk_orientation = 5;
            break;
            
        default:
            break;
    }
    if(walk_direction != 5){
        const auto new_posX = getPositionX() + offset_x;
        const auto new_posY = getPositionY() + offset_y;
        ActionInterval * MoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
        Action * action = Spawn::create(MoveTo, NULL);
        this->runAction(action);
        
    }
}

int Monster::ToPointDir(Vec2 PlayerPos)
{
	double diff_x = PlayerPos.x - getPositionX();
	double diff_y = PlayerPos.y - getPositionY();
	//将坐标差标准化
	double max_xy = max(abs(diff_x), abs(diff_y));
	diff_x /= max_xy;
	diff_y /= max_xy;
	if (diff_x == 1) {
		if (diff_y < -0.3) return 9;
		if (abs(diff_y) < 0.3)	return 6;
		if (diff_y > 0.3) return 3;
	}
	if (diff_x == -1) {
		if (diff_y < -0.3) return 7;
		if (abs(diff_y) < 0.3)	return 4;
		if (diff_y > 0.3) return 1;
	}
	if (diff_y == 1) {
		if (diff_x < -0.3) return 1;
		if (abs(diff_x) < 0.3)	return 2;
		if (diff_x > 0.3) return 3;
	}
	if (diff_y == -1) {
		if (diff_x < -0.3) return 7;
		if (abs(diff_x) < 0.3)	return 8;
		if (diff_x > 0.3) return 9;
	}
	return 5;
}


