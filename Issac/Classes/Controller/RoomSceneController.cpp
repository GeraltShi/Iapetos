#include "RoomSceneController.h"
#include "Scene/RoomScene.h"
#include <iostream>
#include "Service/RoomService.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

Scene * RoomSceneController::createScene(int roomID)
{
    return create(roomID);
}

bool RoomSceneController::init(int roomID)
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    scene_ = RoomScene::create(roomID);
    scene_->set_event_listener(this);
    addChild(scene_);
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
}

int RoomSceneController::check_key_inRoom(EventKeyboard::KeyCode keyCode)
{
    if(scene_->model.game_stat == 0){
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                scene_->stopAllActions();
                scene_->model.game_stat = 1;//1为暂停
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
        if(dirx == 0 && diry == 0){return 1;}
        if(dirx == -1 && diry == 0){return 2;}
        if(dirx == 1 && diry == 0){return 3;}
        if(dirx == 0 && diry == -1){return 4;}
        if(dirx == -1 && diry == -1){return 5;}
        if(dirx == 1 && diry == -1){return 6;}
        if(dirx == 0 && diry == 1){return 7;}
        if(dirx == -1 && diry == 1){return 8;}
        if(dirx == 1 && diry == 1){return 9;}
    }
    if(scene_->model.game_stat == 2){
        switch (keyCode){
            case EventKeyboard::KeyCode::KEY_SPACE:
                scene_->model.game_stat = 0;
                // TODO 因为已经死了所以还在这个死亡菜单界面，需要发射重设参数
                break;
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                scene_->stopAllActions();
                scene_->model.game_stat = 0;
                Director::getInstance()->popScene();
                SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
                SimpleAudioEngine::getInstance()->stopAllEffects();
                SimpleAudioEngine::getInstance()->playBackgroundMusic("res/music/title screen.wav",true);
                break;
            default:
                break;
        }
    }
    return 4;
}

int RoomSceneController::check_head(){
    if(key_map_[EventKeyboard::KeyCode::KEY_UP_ARROW]) return 2;
    if(key_map_[EventKeyboard::KeyCode::KEY_DOWN_ARROW]) return 8;
    if(key_map_[EventKeyboard::KeyCode::KEY_LEFT_ARROW]) return 4;
    if(key_map_[EventKeyboard::KeyCode::KEY_RIGHT_ARROW]) return 6;
    return 5;
}

int RoomSceneController::check_pause(EventKeyboard::KeyCode keyCode){
    int shift = 0;
    if(scene_->model.game_stat == 1){
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                shift = -1;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                shift = 1;
                break;
            case EventKeyboard::KeyCode::KEY_ENTER:
                //cursor = 0,跳转到option
                if(scene_->model.paused_menu_cursor == 0){
                    scene_->model.option_display = 1;
                }
                else if(scene_->model.paused_menu_cursor == 1){
                    scene_->model.game_stat = 0;
                } else if (scene_->model.paused_menu_cursor == 2){
                    Director::getInstance()->popScene();
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
                    SimpleAudioEngine::getInstance()->playBackgroundMusic("res/music/title screen.wav",true);
                }
                break;
            default:
                break;
        }
    }
    return shift;
}

int RoomSceneController::check_option(EventKeyboard::KeyCode keyCode){
    int shift = 0;
    if(scene_->model.game_stat == 1 && scene_->model.option_display == 1){
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                shift = -1;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                shift = 1;
                break;
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                if(scene_->model.option_menu_cursor == 0){
                    if(RoomService::getInstance()->getSFXVolume() != 0){
                        RoomService::getInstance()->setSFXVolume(RoomService::getInstance()->getSFXVolume() - 1);
                    }
                } 
                else if(scene_->model.option_menu_cursor == 1)
                {
                    if(RoomService::getInstance()->getMusicVolume() != 0){
                        RoomService::getInstance()->setMusicVolume(RoomService::getInstance()->getMusicVolume() - 1);
                    }
                } else if(scene_->model.option_menu_cursor == 2){
                    RoomService::getInstance()->decrease_mini_opacity();
                }
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                if(scene_->model.option_menu_cursor == 0){
                    if (RoomService::getInstance()->getSFXVolume() != 10) {
                        RoomService::getInstance()->setSFXVolume(RoomService::getInstance()->getSFXVolume() + 1);
                    }
                } else if(scene_->model.option_menu_cursor == 1){
                    if (RoomService::getInstance()->getMusicVolume() != 10) {
                        RoomService::getInstance()->setMusicVolume(RoomService::getInstance()->getMusicVolume() + 1);
                    }
                } else if(scene_->model.option_menu_cursor == 2){
                    RoomService::getInstance()->increase_mini_opacity();
                }
                break;
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                if(scene_->model.option_display == 1){
                    scene_->model.option_display = 0;
                }
            default:
                break;
        }
    }
    return shift;
}

void RoomSceneController::check_bomb(EventKeyboard::KeyCode keyCode){
    if(scene_->model.game_stat == 0){
        switch (keyCode) {
            case cocos2d::EventKeyboard::KeyCode::KEY_E:
                scene_->model.bomb = true;
                break;
            default:
                break;
        }
    }
}

void RoomSceneController::on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    key_map_[keyCode] = 1;
    //scene_->set_model(RoomSceneModel{ check_key_inRoom(keyCode), check_head() });
    scene_->model.walk_direction = check_key_inRoom(keyCode);
    scene_->model.tear_direction = check_head();
    scene_->model.shift_pausemenu(check_pause(keyCode));
    scene_->model.shift_optionmenu(check_option(keyCode));
    check_bomb(keyCode);
}

void RoomSceneController::on_key_released(EventKeyboard::KeyCode keyCode, Event * event)
{
    key_map_.erase(keyCode);
    scene_->model.walk_direction = check_key_inRoom(keyCode);
    scene_->model.tear_direction = check_head();
}
