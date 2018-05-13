#ifndef __MAIN_SCENE_CONTROLLER_H__
#define __MAIN_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "Scene/MainScene.h"
#include <map>

/**
 * \brief MainScene逻辑控制部分
 */
class MainSceneController : public Scene , IMainSceneListener
{
    MainScene * scene_ = nullptr;
public:
    static Scene *createScene();
    virtual bool init();

    CREATE_FUNC(MainSceneController);
    
    void on_touch_began(Touch* touch, Event* event) override;
    void on_mouse_down(Event* event) override;
    void on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event) override;
    void on_key_released(EventKeyboard::KeyCode keyCode, Event* event) override;
    int check_key(EventKeyboard::KeyCode keyCode);
private:
    map<EventKeyboard::KeyCode,int> key_map_;
};

#endif // __MAIN_SCENE_CONTROLLER_H__
