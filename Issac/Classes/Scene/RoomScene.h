#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IRoomSceneListener.h"
#include "Model/RoomSceneModel.hpp"
#include "Item/Issac.hpp"
#include "Item/Monster.hpp"

USING_NS_CC;

class RoomScene : public Scene
{
  public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(RoomScene)
    
    CC_SYNTHESIZE(RoomSceneModel, model, Model)
    CC_SYNTHESIZE_RETAIN(Issac*, player, Player)
    CC_SYNTHESIZE_RETAIN(Monster*, monster, Monster)
    CC_SYNTHESIZE_RETAIN(Monster*, monster2, Monster2)
    CC_SYNTHESIZE_RETAIN(Sprite*, tearSprite, TearSprite)

    void set_event_listener(IRoomSceneListener *listener);
    void update(float delta) override;
    void change_count(int c);
    void fire(float dt);
    void monster_move(float dt);

private:
    IRoomSceneListener * listener_ = nullptr;
    void build_frame_cache() const;
};

#endif // __ROOM_SCENE_H__
