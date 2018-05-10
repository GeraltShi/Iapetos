#ifndef __ROOM_SCENE_LISTENER_H__
#define __ROOM_SCENE_LISTENER_H__

USING_NS_CC;
using namespace std;

class IRoomSceneListener
{
public:
    virtual void on_touch_began(Touch* touch, Event* event) = 0;
    virtual void on_mouse_down(Event *event) = 0;
};

#endif // __ROOM_SCENE_LISTENER_H__