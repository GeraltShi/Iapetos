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
    
}

void SimpleItem::build_animation_cache(){
    
}
