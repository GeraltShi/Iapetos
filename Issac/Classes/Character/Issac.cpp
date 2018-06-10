#include "Issac.hpp"
#include "cocos2d.h"

using namespace cocos2d;


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
    if (!Moveable::init())
    {
        return false;
    }

	//初始化类变量
	moveSpeed = 150;
	radiusSize = 10;
	bodyMass = 50;
	moving = false;
	tearSpeed = 50;
	tearExistTime = 100;
	//初始血量6个半心（3颗心）
	health = 6;
	//初始攻击
	attack = 1.3;
	this->setTag(1);


    //不要将Texture保存在类,用的时候直接从TextureCache中获取
    const auto texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/characters/costumes/character_001_isaac.png");
    const auto shadow_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/shadow.png");
    SpriteFrame *headFrame = SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32));
    Sprite * headSprite = createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(texture_, Rect(0, 32, 32, 32));
    Sprite * bodySprite = createWithSpriteFrame(bodyFrame);
    Sprite * shadow = createWithTexture(shadow_);
    shadow->setOpacity(0x44);//更改shadow透明度
    shadow->setScale(0.15, 0.15);
    shadow->setPosition(0,-8);
    const auto light_gradient_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/light_gradient.png");
    Sprite * light_gradient = Sprite::createWithTexture(light_gradient_texture, Rect(200,100,100,100));
    //light_gradient->setScale(2, 2);
    build_sprite_frame_cache(texture_);
    build_animation_cache();
    this->addChild(shadow, -1);
    this->addChild(headSprite, 1, "head");
    this->addChild(bodySprite, 0, "body");
    this->addChild(light_gradient,2);
    light_gradient->setOpacity(0x99);//更改light gradient透明度
    BlendFunc blend = {GL_SRC_ALPHA,GL_ONE};
    light_gradient->setBlendFunc(blend);
    headSprite->setPosition(Vec2(0, 10));
    this->setPosition(Vec2(221, 143));
    

    return true;
}

void Issac::build_sprite_frame_cache(Texture2D *texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "lefthead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "righthead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(128, 0, 32, 32)), "uphead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32)), "downhead");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 0, 32, 32)), "vwalk_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 0, 32, 32)), "vwalk_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32 * 1, 32, 32)), "vwalk_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32 * 1, 32, 32)), "vwalk_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 2, 32 * 1, 32, 32)), "vwalk_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 3, 32 * 1, 32, 32)), "vwalk_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 4, 32 * 1, 32, 32)), "vwalk_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 5, 32 * 1, 32, 32)), "vwalk_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 1, 32, 32)), "vwalk_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 1, 32, 32)), "vwalk_frame9");

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32 * 2, 32, 32)), "hwalk_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32 * 2, 32, 32)), "hwalk_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 2, 32 * 2, 32, 32)), "hwalk_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 3, 32 * 2, 32, 32)), "hwalk_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 4, 32 * 2, 32, 32)), "hwalk_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 5, 32 * 2, 32, 32)), "hwalk_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 6, 32 * 2, 32, 32)), "hwalk_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 7, 32 * 2, 32, 32)), "hwalk_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32 * 3, 32, 32)), "hwalk_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32 * 3, 32, 32)), "hwalk_frame9");

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32, 0, 32, 32)), "downshake");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(96, 0, 32, 32)), "rightshake");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(160, 0, 32, 32)), "upshake");
}

void Issac::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto lefthead = spriteCache->getSpriteFrameByName("lefthead");
    const auto leftshake = spriteCache->getSpriteFrameByName("rightshake");

    Vector<SpriteFrame*> leftshakeFrames;
    leftshakeFrames.pushBack(lefthead);
    leftshakeFrames.pushBack(leftshake);
    Animation * leftshakeAnimation = Animation::createWithSpriteFrames(leftshakeFrames, 0.3f);
    leftshakeAnimation->setLoops(-1);
    leftshakeAnimation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(leftshakeAnimation, "leftshakeAnimation");

    const auto righthead = spriteCache->getSpriteFrameByName("righthead");
    const auto rightshake = spriteCache->getSpriteFrameByName("rightshake");
    Vector<SpriteFrame*> rightshakeFrames;
    rightshakeFrames.pushBack(righthead);
    rightshakeFrames.pushBack(rightshake);
    Animation * rightshakeAnimation = Animation::createWithSpriteFrames(rightshakeFrames, 0.3f);
    rightshakeAnimation->setLoops(-1);
    rightshakeAnimation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(rightshakeAnimation, "rightshakeAnimation");

    const auto downhead = spriteCache->getSpriteFrameByName("downhead");
    const auto downshake = spriteCache->getSpriteFrameByName("downshake");
    Vector<SpriteFrame*> downshakeFrames;
    downshakeFrames.pushBack(downhead);
    downshakeFrames.pushBack(downshake);
    Animation * downshakeAnimation = Animation::createWithSpriteFrames(downshakeFrames, 0.3f);
    downshakeAnimation->setLoops(-1);
    downshakeAnimation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(downshakeAnimation, "downshakeAnimation");

    const auto uphead = spriteCache->getSpriteFrameByName("uphead");
    const auto upshake = spriteCache->getSpriteFrameByName("upshake");
    Vector<SpriteFrame*> upshakeFrames;
    upshakeFrames.pushBack(uphead);
    upshakeFrames.pushBack(upshake);
    Animation * upshakeAnimation = Animation::createWithSpriteFrames(upshakeFrames, 0.3f);
    upshakeAnimation->setLoops(-1);
    upshakeAnimation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(upshakeAnimation, "upshakeAnimation");

    const auto vwalk_frame0 = spriteCache->getSpriteFrameByName("vwalk_frame0");
    const auto vwalk_frame1 = spriteCache->getSpriteFrameByName("vwalk_frame1");
    const auto vwalk_frame2 = spriteCache->getSpriteFrameByName("vwalk_frame2");
    const auto vwalk_frame3 = spriteCache->getSpriteFrameByName("vwalk_frame3");
    const auto vwalk_frame4 = spriteCache->getSpriteFrameByName("vwalk_frame4");
    const auto vwalk_frame5 = spriteCache->getSpriteFrameByName("vwalk_frame5");
    const auto vwalk_frame6 = spriteCache->getSpriteFrameByName("vwalk_frame6");
    const auto vwalk_frame7 = spriteCache->getSpriteFrameByName("vwalk_frame7");
    const auto vwalk_frame8 = spriteCache->getSpriteFrameByName("vwalk_frame8");
    const auto vwalk_frame9 = spriteCache->getSpriteFrameByName("vwalk_frame9");
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
    Animation * vwalk_animation = Animation::createWithSpriteFrames(vwalkFrames, 0.1f);
    vwalk_animation->setLoops(-1);
    vwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(vwalk_animation, "vwalk_animation");


    const auto hwalk_frame0 = spriteCache->getSpriteFrameByName("hwalk_frame0");
    const auto hwalk_frame1 = spriteCache->getSpriteFrameByName("hwalk_frame1");
    const auto hwalk_frame2 = spriteCache->getSpriteFrameByName("hwalk_frame2");
    const auto hwalk_frame3 = spriteCache->getSpriteFrameByName("hwalk_frame3");
    const auto hwalk_frame4 = spriteCache->getSpriteFrameByName("hwalk_frame4");
    const auto hwalk_frame5 = spriteCache->getSpriteFrameByName("hwalk_frame5");
    const auto hwalk_frame6 = spriteCache->getSpriteFrameByName("hwalk_frame6");
    const auto hwalk_frame7 = spriteCache->getSpriteFrameByName("hwalk_frame7");
    const auto hwalk_frame8 = spriteCache->getSpriteFrameByName("hwalk_frame8");
    const auto hwalk_frame9 = spriteCache->getSpriteFrameByName("hwalk_frame9");
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
    Animation * hwalk_animation = Animation::createWithSpriteFrames(hwalkFrames, 0.1f);
    hwalk_animation->setLoops(-1);
    hwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(hwalk_animation, "hwalk_animation");
}

//TODO MoveTo 有bug，贴墙以后在墙附近怼墙 会卡住
void Issac::move(int walk_direction, int tear_direction)
{
	//移动
	//移动速度不是之前的情况，说明发生碰撞
	if (colClog == ColClogTime
		&& this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation)) {
		colClog = 0;
	}
	else {
		this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
	}

	//移动的图形显示
    //直接获取缓存，不要将SpriteFrame保存在类中
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto leftshakeAnimation = aniCache->getAnimation("leftshakeAnimation");
    const auto rightshakeAnimation = aniCache->getAnimation("rightshakeAnimation");
    const auto downshakeAnimation = aniCache->getAnimation("downshakeAnimation");
    const auto upshakeAnimation = aniCache->getAnimation("upshakeAnimation");
    const auto vwalk_animation = aniCache->getAnimation("vwalk_animation");
    const auto hwalk_animation = aniCache->getAnimation("hwalk_animation");
    
    Animate * leftshakeAnimate = Animate::create(leftshakeAnimation);
    Animate * rightshakeAnimate = Animate::create(rightshakeAnimation);
    Animate * downshakeAnimate = Animate::create(downshakeAnimation);
    Animate * upshakeAnimate = Animate::create(upshakeAnimation);
    Animate * vwalk_animate = Animate::create(vwalk_animation);
    Animate * hwalk_animate = Animate::create(hwalk_animation);
    
    // Mask, 用于walk_direction和head_direction合并成direction
    int head_direction;
    if(tear_direction == 5){
        head_direction = walk_direction;
    } else {
        head_direction = tear_direction;
    }
    Sprite * new_head;
    switch (walk_direction)
    {
            //123
            //456
            //789
        case 4://左
            if(prev_walk_orientation != 4){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->setScaleX(-1);//翻转
                this->getChildByName("body")->runAction(hwalk_animate);
            }
            prev_walk_orientation = 4;
            break;
        
        case 6://右
            if(prev_walk_orientation != 6){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->setScaleX(1);//翻转
                this->getChildByName("body")->runAction(hwalk_animate);
            }
            prev_walk_orientation = 6;
            break;
        
        case 2://上
            if(prev_walk_orientation != 2){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate->reverse());//向上走要倒放
            }
            prev_walk_orientation = 2;
            break;
            
        case 8://下
            if(prev_walk_orientation != 8){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate);
            }
            prev_walk_orientation = 8;
            break;
            
        case 1://左上
            if(prev_walk_orientation != 1){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate->reverse());
            }
            prev_walk_orientation = 1;
            break;
            
        case 3://右上
            if(prev_walk_orientation != 3){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate->reverse());
            }
            prev_walk_orientation = 3;
            break;
        
        case 7://左下
            if(prev_walk_orientation != 7){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate);
            }
            prev_walk_orientation = 7;
            break;
            
        case 9://右下
            if(prev_walk_orientation != 9){
                this->getChildByName("body")->stopAllActions();
                this->getChildByName("body")->runAction(vwalk_animate);
            }
            prev_walk_orientation = 9;
            break;
            
        case 5://无，头要默认复位
            this->getChildByName("body")->stopAllActions();
            prev_walk_orientation = 5;
            break;
            
        default:
            break;
    }
    switch (head_direction) {
        case 1: case 2: case 3:
            if(prev_head_orientation != 2){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("uphead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1,"head");
                prev_head_orientation = 2;
                if(tear_direction != 5)
                this->getChildByName("head")->runAction(upshakeAnimate);
            }else if(prev_head_orientation == 2 && tear_direction == 5){
                this->getChildByName("head")->runAction(upshakeAnimate);
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
                if(tear_direction != 5)
                this->getChildByName("head")->runAction(leftshakeAnimate);
            }else if(prev_head_orientation == 4 && tear_direction == 5){
                this->getChildByName("head")->runAction(leftshakeAnimate);
            }
            break;
        case 5:
            if(prev_head_orientation != 5){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("downhead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 5;
            }
            break;
        case 6:
            if(prev_head_orientation != 6){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("righthead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 6;
                if(tear_direction != 5)
                this->getChildByName("head")->runAction(rightshakeAnimate);
            }else if(prev_head_orientation == 6 && tear_direction == 5){
                this->getChildByName("head")->runAction(rightshakeAnimate);
            }
            break;
        case 7: case 8: case 9:
            if(prev_head_orientation != 8){
                this->removeChild(this->getChildByName("head"), true);
                new_head = createWithSpriteFrame(spriteCache->getSpriteFrameByName("downhead"));
                new_head->setPosition(Vec2(0,10));
                this->addChild(new_head,1, "head");
                prev_head_orientation = 8;
                if(tear_direction != 5)
                this->getChildByName("head")->runAction(downshakeAnimate);
            } else if(prev_head_orientation == 8 && tear_direction == 5){
                this->getChildByName("head")->runAction(downshakeAnimate);
            }
            break;
        default:
            break;
    }

	if (colClog == 0) {
		prev_walk_orientation = 5;
	}
}

void Issac::createPhyBody()
{
	auto phyBody = PhysicsBody::createCircle(radiusSize, PHYSICSBODY_MATERIAL_DEFAULT);
	//是否设置物体为静态  
	phyBody->setDynamic(true);
	//设置物体的恢复力  
	phyBody->getShape(0)->setRestitution(1.0f);
	//设置物体的摩擦力  
	phyBody->getShape(0)->setFriction(0.0f);
	//设置物体密度  
	phyBody->getShape(0)->setDensity(1.0f);
	//设置质量  
	phyBody->getShape(0)->setMass(bodyMass);
	//设置物体是否受重力系数影响  
	phyBody->setGravityEnable(false);
	//速度
	phyBody->setVelocity(Vec2(0, 0));
	//碰撞筛选:所有都碰撞，选择性监听:和item,tear，monster碰撞监听，石头不监听
	phyBody->setCategoryBitmask(0x01);    // 0000_0001
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111
	phyBody->setContactTestBitmask(0x06);	//0000_0110
	//添加物理躯体
	this->addComponent(phyBody);
}
