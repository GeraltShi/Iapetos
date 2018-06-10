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
	void move(int walk_direction);
	int ToPointDir(Vec2);
	//怪物的移动策略，这是接口。子类每个怪物重写。
	virtual void moveStrategy(int walk_direction) = 0;
protected:
	void build_sprite_frame_cache(Texture2D *texture_, Texture2D *dead_texture_) const;//必要时需要重载
	static void build_animation_cache();
};

class Fatty : public Monster {
public:
	static Fatty *createFatty();
	virtual bool init();
	CREATE_FUNC(Fatty)
	virtual void moveStrategy(int walk_direction);
};
#endif /* Monster_hpp */
