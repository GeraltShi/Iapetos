#include "SimpleItem.h"

using namespace cocos2d;

SimpleItem *SimpleItem::createSimpleItem()
{
    return create();
}

Sprite *SimpleItem::createSprite()
{
    return create();
}

bool SimpleItem::init(){
    if(!Sprite::init()){
        return false;
    }
    const auto bombtexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_016_bomb.png");
    Sprite * bomb = Sprite::createWithTexture(bombtexture, Rect(0,0,32,32));
    this->addChild(bomb);
    return true;
}
