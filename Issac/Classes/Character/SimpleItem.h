#ifndef SIMPLE_ITEM_H_
#define SIMPLE_ITEM_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SimpleItem : public Sprite
{
public:
    static SimpleItem *createSimpleItem();
    bool init() override;
    
    CREATE_FUNC(SimpleItem)
    void build_sprite_frame_cache() const;
    static void build_animation_cache();
};


#endif
