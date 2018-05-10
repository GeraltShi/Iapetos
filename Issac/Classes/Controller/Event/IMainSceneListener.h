#ifndef __MAIN_SCENE_LISTENER_H__
#define __MAIN_SCENE_LISTENER_H__

USING_NS_CC;
using namespace std;

class IMainSceneListener
{
public:
    virtual void on_touch_began(Touch* touch, Event* event) = 0;
    virtual void on_mouse_down(Event *event) = 0;
    virtual void on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event) = 0;
    virtual void on_key_released(EventKeyboard::KeyCode keyCode, Event* event) = 0;
};

#endif // __MAIN_SCENE_LISTENER_H__