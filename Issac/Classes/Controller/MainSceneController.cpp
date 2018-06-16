#include "MainSceneController.h"
#include "Scene/MainScene.h"
#include "RoomSceneController.h"
#include "Service/RoomService.h"
#include "Service/PlayerService.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

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


    //auto l = Label::createWithTTF("Controlled", "fonts/simhei.ttf", 30);
    //l->setPosition(640, 600);
    //addChild(l);

    scene_ = MainScene::create();
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/music/title screen.wav");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("res/music/title screen.wav",true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.2);
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
    //TODO 程序失焦自动暂停
    //TODO 用AOP方式管理Scene和Service
    //auto room = RoomSceneController::createScene();
    //Director::getInstance()->pushScene(room);
}

int MainSceneController::check_key(EventKeyboard::KeyCode keyCode) const
{
    //TODO 上下切换目录，回车确认
    int shift = 0;
    if(scene_->model.view == 1){
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                shift = -1;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                shift = 1;
                break;
            case EventKeyboard::KeyCode::KEY_ENTER:
                shift = 0;
                if(scene_->model.menun == 0){
                    RoomService::getInstance()->init();
                    PlayerService::getInstance()->init();
                    const auto room = RoomSceneController::createScene(RoomService::getInstance()->get_init_room_id());
                    TransitionScene* tx = TransitionFade::create(0.7, room);
                    Director::getInstance()->pushScene(tx);
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
                    SimpleAudioEngine::getInstance()->playBackgroundMusic("res/music/diptera sonata(basement).wav",true);
                }
                break;
            case EventKeyboard::KeyCode::KEY_D:
                {
                RoomService::getInstance()->initDebug();
                PlayerService::getInstance()->init();
                const auto room = RoomSceneController::createScene(RoomService::getInstance()->get_init_room_id());
                TransitionScene* tx = TransitionFade::create(0.7, room);
                Director::getInstance()->pushScene(tx);
                SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
                SimpleAudioEngine::getInstance()->playBackgroundMusic("res/music/diptera sonata(basement).wav", true);
                break;
                }
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                scene_->model.view = 0;
                break;
            default: break;
        }
    } else {
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_ENTER:
                    scene_->model.view = 1;
                break;
            default: break;
        }
    }
    return shift;
}

void MainSceneController::on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    key_map_[keyCode] = 1;
    scene_->model.shift_menu(check_key(keyCode));//MainSceneModel( check_key(keyCode) )
}

void MainSceneController::on_key_released(EventKeyboard::KeyCode keyCode, Event * event)
{
    key_map_.erase(keyCode);

//    if (key_map_.empty())
//    {
//        scene_->set_model(MainSceneModel( 0 ));
//    }
//    else
//    {
//        keyCode = key_map_.begin()->first;
//        scene_->set_model(MainSceneModel( check_key(keyCode) ));
//    }

    
}
