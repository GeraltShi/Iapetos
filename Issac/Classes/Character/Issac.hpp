#ifndef Issac_hpp
#define Issac_hpp

#include "cocos2d.h"
#include "Moveable.h"
#include "Tear.h"

USING_NS_CC;
using namespace std;

class Issac : public Moveable {
public:
    static Issac *createIssac();
    bool init() override;

	CREATE_FUNC(Issac)

	virtual void createPhyBody();
	Tear* Fire(int fireDir);
    void move(int walk_direction, int tear_direction);
private:
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};
#endif
