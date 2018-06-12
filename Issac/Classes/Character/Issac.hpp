#ifndef Issac_hpp
#define Issac_hpp

#include "cocos2d.h"
#include "Moveable.h"

USING_NS_CC;
using namespace std;

class Issac : public Moveable {
public:
    static Issac *createIssac();
    static Sprite *createSprite();
    bool init() override;

	CREATE_FUNC(Issac)

	virtual void createPhyBody();
    void move(int walk_direction, int tear_direction);
private:
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};
#endif
