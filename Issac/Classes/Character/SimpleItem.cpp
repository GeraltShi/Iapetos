#include "SimpleItem.h"

using namespace cocos2d;

SimpleItem *SimpleItem::createSimpleItem()
{
    return create();
}

bool SimpleItem::init(){
    if(!Sprite::init()){
        return false;
    }
    const auto bombtexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_016_bomb.png");
    Sprite * bomb = Sprite::createWithTexture(bombtexture, Rect(0,0,32,32));
    build_sprite_frame_cache();
    build_animation_cache();
    this->addChild(bomb);
    return true;
}

void SimpleItem::build_sprite_frame_cache() const {
    auto fcache = SpriteFrameCache::getInstance();
    Texture2D * explosion_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/effects/effect_029_explosion.png");
    const auto explosion0 = SpriteFrame::createWithTexture(explosion_texture,Rect(0,0,96,96));
    const auto explosion1 = SpriteFrame::createWithTexture(explosion_texture,Rect(96,0,96,96));
    const auto explosion2 = SpriteFrame::createWithTexture(explosion_texture,Rect(192,0,96,96));
    const auto explosion3 = SpriteFrame::createWithTexture(explosion_texture,Rect(288,0,96,96));
    const auto explosion4 = SpriteFrame::createWithTexture(explosion_texture,Rect(0,96,96,96));
    const auto explosion5 = SpriteFrame::createWithTexture(explosion_texture,Rect(96,96,96,96));
    const auto explosion6 = SpriteFrame::createWithTexture(explosion_texture,Rect(192,96,96,96));
    const auto explosion7 = SpriteFrame::createWithTexture(explosion_texture,Rect(288,96,96,96));
    const auto explosion8 = SpriteFrame::createWithTexture(explosion_texture,Rect(0,192,96,96));
    const auto explosion9 = SpriteFrame::createWithTexture(explosion_texture,Rect(96,192,96,96));
    const auto explosion10 = SpriteFrame::createWithTexture(explosion_texture,Rect(192,192,96,96));
    const auto explosion11 = SpriteFrame::createWithTexture(explosion_texture,Rect(288,192,96,96));
    fcache->addSpriteFrame(explosion0,"explosion0");
    fcache->addSpriteFrame(explosion1,"explosion1");
    fcache->addSpriteFrame(explosion2,"explosion2");
    fcache->addSpriteFrame(explosion3,"explosion3");
    fcache->addSpriteFrame(explosion4,"explosion4");
    fcache->addSpriteFrame(explosion5,"explosion5");
    fcache->addSpriteFrame(explosion6,"explosion6");
    fcache->addSpriteFrame(explosion7,"explosion7");
    fcache->addSpriteFrame(explosion8,"explosion8");
    fcache->addSpriteFrame(explosion9,"explosion9");
    fcache->addSpriteFrame(explosion10,"explosion10");
    fcache->addSpriteFrame(explosion11,"explosion11");
}

void SimpleItem::build_animation_cache(){
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();
    
    const auto explosion_frame0 = spriteCache->getSpriteFrameByName("explosion0");
    const auto explosion_frame1 = spriteCache->getSpriteFrameByName("explosion1");
    const auto explosion_frame2 = spriteCache->getSpriteFrameByName("explosion2");
    const auto explosion_frame3 = spriteCache->getSpriteFrameByName("explosion3");
    const auto explosion_frame4 = spriteCache->getSpriteFrameByName("explosion4");
    const auto explosion_frame5 = spriteCache->getSpriteFrameByName("explosion5");
    const auto explosion_frame6 = spriteCache->getSpriteFrameByName("explosion6");
    const auto explosion_frame7 = spriteCache->getSpriteFrameByName("explosion7");
    const auto explosion_frame8 = spriteCache->getSpriteFrameByName("explosion8");
    const auto explosion_frame9 = spriteCache->getSpriteFrameByName("explosion9");
    const auto explosion_frame10 = spriteCache->getSpriteFrameByName("explosion10");
    const auto explosion_frame11 = spriteCache->getSpriteFrameByName("explosion11");
    Vector<SpriteFrame *> explosionFrames;
    explosionFrames.pushBack(explosion_frame0);
    explosionFrames.pushBack(explosion_frame1);
    explosionFrames.pushBack(explosion_frame2);
    explosionFrames.pushBack(explosion_frame3);
    explosionFrames.pushBack(explosion_frame4);
    explosionFrames.pushBack(explosion_frame5);
    explosionFrames.pushBack(explosion_frame6);
    explosionFrames.pushBack(explosion_frame7);
    explosionFrames.pushBack(explosion_frame8);
    explosionFrames.pushBack(explosion_frame9);
    explosionFrames.pushBack(explosion_frame10);
    explosionFrames.pushBack(explosion_frame11);
    Animation *explosion_animation = Animation::createWithSpriteFrames(explosionFrames, 0.1f);
    explosion_animation->setLoops(1);
    aniCache->addAnimation(explosion_animation, "explosion_animation");
}
