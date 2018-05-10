#include "MainSceneController.h"
#include "Scene/MainScene.h"
#include "RoomSceneController.h"

USING_NS_CC;
using namespace std;

Scene * MainSceneController::createScene()
{
    return create();
}

bool MainSceneController::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto l = Label::createWithTTF("Controlled", "fonts/simhei.ttf", 30);
    l->setPosition(640, 600);
    addChild(l);

    scene_ = MainScene::create();
    scene_->set_event_listener(this);
    addChild(scene_);

    return true;
}

void MainSceneController::on_touch_began(Touch* touch, Event* event)
{
    cocos2d::log("main_scene_on_touch");
}

void MainSceneController::on_mouse_down(Event *event)
{
    cocos2d::log("main_scene_on_click");
    
    //TODO 用AOP方式管理Scene和Service
    auto room = RoomSceneController::createScene();
    Director::getInstance()->pushScene(room);
}

int check_key(EventKeyboard::KeyCode keyCode)
{
    int dir = -1;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_A:
        dir = 0;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        dir = 1;
        break;
    case EventKeyboard::KeyCode::KEY_W:
        dir = 2;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        dir = 3;
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        dir = 0;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        dir = 1;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        dir = 2;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        dir = 3;
        break;
    default: break;
    }

    return dir;
}

void MainSceneController::on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    key_map_[keyCode] = 1;
    scene_->set_model(MainSceneModel{ check_key(keyCode) });
}

void MainSceneController::on_key_released(EventKeyboard::KeyCode keyCode, Event * event)
{
    key_map_.erase(keyCode);

    if (key_map_.empty())
    {
        scene_->set_model(MainSceneModel{ -1 });
    }
    else
    {
        keyCode = key_map_.begin()->first;
        scene_->set_model(MainSceneModel{ check_key(keyCode) });
    }

    
}
