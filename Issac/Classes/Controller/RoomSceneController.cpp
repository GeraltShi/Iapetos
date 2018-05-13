#include "RoomSceneController.h"
#include "Scene/RoomScene.h"
#include <iostream>

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


int RoomSceneController::check_key_inRoom(EventKeyboard::KeyCode keyCode)
{
    int dir = -1;
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_A:
            //dir = 0;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            //dir = 1;
            break;
        case EventKeyboard::KeyCode::KEY_W:
            //dir = 2;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            //dir = 3;
            break;
//        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//            dir = 0;
//            break;
//        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//            dir = 1;
//            break;
//        case EventKeyboard::KeyCode::KEY_UP_ARROW:
//            dir = 2;
//            break;
//        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//            dir = 3;
//            break;
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            //TODO 暂停Scene
            //堆栈结构
            //|---栈顶---|
            //|暂停Scene |
            //|RoomScene|
            //|MainScene|
            //|---------|
            //TOOD
            std::cout << "Status" <<paused << endl;
            if(paused){
                scene_->resumeSchedulerAndActions();
                paused = false;
            }else {
                Director::getInstance()->popScene();
                paused = true;
            }
            break;
        default: break;
    }
    int dirx = -1; int diry = -1;
    if(key_map_[EventKeyboard::KeyCode::KEY_A]) dirx = 0;
    if(key_map_[EventKeyboard::KeyCode::KEY_D]) dirx = 1;
    if((!key_map_[EventKeyboard::KeyCode::KEY_A])&& (!key_map_[EventKeyboard::KeyCode::KEY_D])) dirx = -1;
    if(key_map_[EventKeyboard::KeyCode::KEY_W]) diry = 0;
    if(key_map_[EventKeyboard::KeyCode::KEY_S]) diry = 1;
    if((!key_map_[EventKeyboard::KeyCode::KEY_W])&& (!key_map_[EventKeyboard::KeyCode::KEY_S])) diry = -1;
    if(dirx == 0 && diry == 0){return 0;}
    if(dirx == -1 && diry == 0){return 1;}
    if(dirx == 1 && diry == 0){return 2;}
    if(dirx == 0 && diry == -1){return 3;}
    if(dirx == -1 && diry == -1){return 4;}
    if(dirx == 1 && diry == -1){return 5;}
    if(dirx == 0 && diry == 1){return 6;}
    if(dirx == -1 && diry == 1){return 7;}
    if(dirx == 1 && diry == 1){return 8;}
    
    return 4;
}

void RoomSceneController::on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    key_map_[keyCode] = 1;
    scene_->set_model(RoomSceneModel{ check_key_inRoom(keyCode) });
}

void RoomSceneController::on_key_released(EventKeyboard::KeyCode keyCode, Event * event)
{
    key_map_.erase(keyCode);
    scene_->set_model(RoomSceneModel{ check_key_inRoom(keyCode) });
//    key_map_.erase(keyCode);
//
//    if (key_map_.empty())
//    {
//        scene_->set_model(RoomSceneModel{ -1 });
//    }
//    else
//    {
//        keyCode = key_map_.begin()->first;
//        scene_->set_model(RoomSceneModel{ check_key_inRoom(keyCode) });
//    }
//
//
}
