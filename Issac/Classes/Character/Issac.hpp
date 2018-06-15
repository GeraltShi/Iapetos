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
	Tear* Fire(int fireDir) const;
    void move(int walk_direction, int tear_direction);
    void hurt();
    void dead();
    double getMoveSpeed();//移动速度
    double getTearSpeed();//弹速
    double getAttack();//攻击力
    int getTearExistingTime();//射程
    double getShootInterval();//射击间隔

    void setHealth(int health) override;
    void setAttack(double attack) override;

private:
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};
#endif
