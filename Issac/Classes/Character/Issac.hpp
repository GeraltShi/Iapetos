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
    int getHealth() const override;
    double getMoveSpeed() const override;//移动速度
    double getTearSpeed() const override;//弹速
    double getAttack() const override;//攻击力
    int getTearExistTime() const override;//射程
    double getShootInterval() const override;//射击间隔
    double getRadiusSize() const override;
    double getBodyMass() const override;
    bool getEnFly() const override;
    bool getEnBounce() const override;

    void setHealth(int health) override;
    void setAttack(double attack) override;
    void setMoveSpeed(double var) override;
    void setTearSpeed(double var) override;
    void setTearExistTime(int var) override;
    void setShootInterval(double var) override;
    void setRadiusSize(double var) override;
    void setBodyMass(double var) override;
    void setEnFly(bool var) override;
    void setEnBounce(bool var) override;

private:
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};
#endif
