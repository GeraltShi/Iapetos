#ifndef __ROOM_SCENE_CONTROLLER_H__
#define __ROOM_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "Scene/RoomScene.h"
#include <map>
#include "Service/LevelService.h"
/**
 * \brief RoomScene逻辑控制部分
 */
class RoomSceneController : public Scene, IRoomSceneListener
{
public:
    static Scene *createScene();
    bool init() override;

    CREATE_FUNC(RoomSceneController)
    CC_SYNTHESIZE_RETAIN(RoomScene*,scene_,MScene)

    void on_touch_began(Touch* touch, Event* event) override;
    void on_mouse_down(Event* event) override;
    void on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event) override;
    void on_key_released(EventKeyboard::KeyCode keyCode, Event* event) override;
    int check_key_inRoom(EventKeyboard::KeyCode keyCode);
    int check_head();
    
private:
    map<EventKeyboard::KeyCode,int> key_map_;

    int count = 0;
    bool paused = false;
    LevelService level_service_;

};

#endif // __ROOM_SCENE_CONTROLLER_H__
