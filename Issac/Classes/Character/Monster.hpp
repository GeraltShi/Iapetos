#ifndef Monster_hpp
#define Monster_hpp

#include "cocos2d.h"
#include "Moveable.h"

USING_NS_CC;
using namespace std;

class Monster : public Moveable {
public:
    static Monster *createMonster();
    static Sprite *createSprite();
    bool init() override;
    
    CREATE_FUNC(Monster)
    
	virtual void createPhyBody();
	void move(int walk_direction);
	int ToPointDir(Vec2);
private:
    void build_sprite_frame_cache(Texture2D *texture_) const;//必要时需要重载
    static void build_animation_cache();
};
#endif /* Monster_hpp */
