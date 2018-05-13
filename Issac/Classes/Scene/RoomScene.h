#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IRoomSceneListener.h"
#include "Model/RoomSceneModel.hpp"


class RoomScene : public cocos2d::Scene
{
  public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(RoomScene);
    
    void set_event_listener(IRoomSceneListener *listener);
    void set_model(RoomSceneModel model);
    void update(float delta) override;
    void change_count(int c);

private:
    IRoomSceneListener * listener_ = nullptr;
    RoomSceneModel model;
    void peppa_move(int direction) const;
    Sprite * issac = nullptr;
};

#endif // __ROOM_SCENE_H__
