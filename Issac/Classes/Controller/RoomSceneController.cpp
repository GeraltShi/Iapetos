#include "RoomSceneController.h"

USING_NS_CC;
using namespace std;

Scene * RoomSceneController::createScene()
{
    return create();
}

bool RoomSceneController::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto l = Label::createWithTTF("Controlled", "fonts/simhei.ttf", 30);
    l->setPosition(640, 600);
    addChild(l);

    scene_ = RoomScene::create();
    scene_->set_event_listener(this);
    addChild(scene_);

    //TODO 地图服务
    level_service_ = LevelService();

    return true;
}

void RoomSceneController::on_touch_began(Touch * touch, Event * event)
{
    cocos2d::log("room_scene_on_touch");
}

void RoomSceneController::on_mouse_down(Event * event)
{
    cocos2d::log("room_scene_on_touch");

    count++;

    scene_->change_count(count);
}
