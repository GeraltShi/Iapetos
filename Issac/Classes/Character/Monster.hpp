#ifndef Monster_hpp
#define Monster_hpp

#include "cocos2d.h"
#include "Moveable.h"

USING_NS_CC;
using namespace std;

class Monster : public Moveable {
public:
	static Sprite *createSprite();
	virtual bool init();

	//CREATE_FUNC(Monster)

	virtual void createPhyBody();
	
	int ToPointDir(Vec2);
	//怪物的移动策略，这是接口。子类每个怪物重写。
	virtual void moveStrategy(int walk_direction) = 0;
//protected:
	
};

class Fatty : public Monster {
public:
	static Fatty *createFatty();
	virtual bool init();
	CREATE_FUNC(Fatty)
    void move(int walk_direction);
	virtual void moveStrategy(int walk_direction);
    void build_sprite_frame_cache(Texture2D *texture_, Texture2D *dead_texture_) const;
    static void build_animation_cache();
};

class Fly : public Monster {
public:
    static Fly *createFly();
    virtual bool init();
    CREATE_FUNC(Fly)
    void move(int walk_direction);
    virtual void moveStrategy(int walk_direction);
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};

class Gaper : public Monster {
public:
    static Gaper *createGaper();
    virtual bool init();
    CREATE_FUNC(Gaper)
    void move(int walk_direction);
    virtual void moveStrategy(int walk_direction);
    void build_sprite_frame_cache(Texture2D *headtexture_, Texture2D *bodytexture_, Texture2D *dead_texture_) const;
    static void build_animation_cache();
};
#endif /* Monster_hpp */
