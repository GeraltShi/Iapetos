#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IRoomSceneListener.h"


class RoomScene : public cocos2d::Scene
{
  public:
    static cocos2d::Scene *createScene();
    virtual bool init();

    CREATE_FUNC(RoomScene);
    void set_event_listener(IRoomSceneListener *listener);
    void change_count(int c);

private:
    IRoomSceneListener * listener_ = nullptr;
};

#endif // __ROOM_SCENE_H__