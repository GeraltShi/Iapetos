#ifndef Monster_hpp
#define Monster_hpp

#include "cocos2d.h"
#include "Moveable.h"
#include "Tear.h"
#include "ViewModel/RoomViewModel.h"

USING_NS_CC;
using namespace std;

#define MonTearOffset 15
const GridPoint moveStep[8] = {GridPoint(1, 0), GridPoint(-1, 0), GridPoint(0, 1), GridPoint(0, -1), GridPoint(1, 1), GridPoint(-1, -1), GridPoint(-1, 1), GridPoint(1, -1)};

class Monster : public Moveable
{
  public:
    virtual bool init();
    virtual void createPhyBody();

    Tear *Fire(Vec2 targetPos);
    int ToPointDir(Vec2);
    GridPoint CalGridPos(Vec2 truePos)
    {
        return GridPoint((int)(truePos.x - 48) / RoomUnitSize.width, (int)(truePos.y - 48) / RoomUnitSize.height);
    }
    double CalDistance(Vec2 x1, Vec2 x2)
    {
        return sqrt((x1.x - x2.x) * (x1.x - x2.x) + (x1.y - x2.y) * (x1.y - x2.y));
    }
	virtual void move(int walk_direction)=0;
    //怪物的移动策略，这是接口。子类每个怪物重写。
    virtual void moveStrategy(const RoomViewModel &roomMap) = 0; 
    //怪物的开火策略，这是接口。子类每个怪物重写。
    virtual void fireStrategy(Vector<Tear *> &tears_) = 0;
	//怪物的生孩子策略，这是借口。子类每个怪物重写。
	virtual void giveBirth(Vector<Monster *> &monsters_) = 0;
    //怪物的死亡动画，每个子类可以重载
    virtual string getDeadAnimation();

    CC_SYNTHESIZE(int, fireCoolTime, FireCoolTime)
  protected:
    void build_sprite_frame_cache(Texture2D *dead_texture_) const;
    static void build_animation_cache();
};

class Fatty : public Monster
{
public:
    static Fatty *createFatty();
    virtual bool init();
    CREATE_FUNC(Fatty)
	virtual void move(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
	virtual void fireStrategy(Vector<Tear *> &tears_) {}
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};

class FattyFire : public Fatty
{
public:
	static FattyFire *createFattyFire() {
		return create();
	}
	virtual bool init() {
		if (!(Fatty::init())) {
			return false;
		}
		fireSpeed = 20;		//射速
		tearSpeed = 20;		//弹速
		tearExistTime = 30; //射程
		return true;
	}
	CREATE_FUNC(FattyFire)
	virtual void move(int walk_direction) { Fatty::move(walk_direction); }
	virtual void moveStrategy(const RoomViewModel &roomMap);
	virtual void fireStrategy(Vector<Tear *> &tears_);
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
};

class Fly : public Monster
{
  public:
    static Fly *createFly();
    virtual bool init();
    CREATE_FUNC(Fly)
	virtual void move(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
	virtual void fireStrategy(Vector<Tear *> &tears_) {}
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
    string getDeadAnimation() override;
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};

class FlyFire : public Fly
{
public:
	static FlyFire *createFlyFire() {
		return create();
	}
	virtual bool init() { 
		if (!(Fly::init())) {
			return false;
		};
		fireSpeed = 50;		//射速
		tearSpeed = 40;		//弹速
		tearExistTime = 200; //射程
		return true;
	}
	CREATE_FUNC(FlyFire)
	virtual void move(int walk_direction) { Fly::move(walk_direction); }
	virtual void moveStrategy(const RoomViewModel &roomMap) { Fly::moveStrategy(roomMap); }
	virtual void fireStrategy(Vector<Tear *> &tears_);
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
};

class Gaper : public Monster
{
  public:
    static Gaper *createGaper();
    virtual bool init();
    CREATE_FUNC(Gaper)
	virtual void move(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
	virtual void fireStrategy(Vector<Tear *> &tears_) {}
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
    void build_sprite_frame_cache(Texture2D *headtexture_, Texture2D *bodytexture_) const;
    static void build_animation_cache();
};

class GaperFire : public Gaper
{
public:
	static GaperFire *createGaperFire() {
		return create();
	}
	virtual bool init() { 
		if (!Gaper::init()) {
			return false;
		}
		fireSpeed = 40;		//射速
		tearSpeed = 20;		//弹速
		tearExistTime = 50; //射程
		return true;
	}
	CREATE_FUNC(GaperFire)
	virtual void move(int walk_direction) { Gaper::move(walk_direction); }
	virtual void moveStrategy(const RoomViewModel &roomMap) { Gaper::moveStrategy(roomMap); }
	virtual void fireStrategy(Vector<Tear *> &tears_);
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
};

class Spider : public Monster
{
  public:
    static Spider *createSpider();
    virtual bool init();
    CREATE_FUNC(Spider)
	virtual void move(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
	virtual void fireStrategy(Vector<Tear *> &tears_) {}
	virtual void giveBirth(Vector<Monster *> &monsters_) {}
    string getDeadAnimation() override;
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};
#endif /* Monster_hpp */
