#ifndef __ROOM_SCENE_CONTROLLER_H__
#define __ROOM_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "Scene/RoomScene.h"
#include "Service/LevelService.h"

class RoomSceneController : public Scene, IRoomSceneListener
{
    RoomScene * scene_ = nullptr;
public:
    static Scene *createScene();
    virtual bool init();

    CREATE_FUNC(RoomSceneController);

    void on_touch_began(Touch* touch, Event* event) override;
    void on_mouse_down(Event* event) override;

private:
    
    /**
     * \brief //TODO 应该创建Model类存储数据并放在Model文件夹中
     */
    int count = 0;

    LevelService level_service_;

};

#endif // __ROOM_SCENE_CONTROLLER_H__
