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
    static Scene *createScene(int roomID);
    //bool init() override;
	bool init(int roomID);

    //CREATE_FUNC(RoomSceneController)
	static RoomSceneController* create(int roomID)
	{
		RoomSceneController *pRet = new(std::nothrow) RoomSceneController();
		if (pRet && pRet->init(roomID))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}



    CC_SYNTHESIZE_RETAIN(RoomScene*,scene_,MScene)

    void on_touch_began(Touch* touch, Event* event) override;
    void on_mouse_down(Event* event) override;
    void on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event) override;
    void on_key_released(EventKeyboard::KeyCode keyCode, Event* event) override;
    int check_key_inRoom(EventKeyboard::KeyCode keyCode) ;
    int check_head();
    int check_pause(EventKeyboard::KeyCode keyCode);
    int check_option(EventKeyboard::KeyCode keyCode);
    void check_bomb(EventKeyboard::KeyCode keyCode);
    
private:
    map<EventKeyboard::KeyCode,int> key_map_;

    int count = 0;
    LevelService level_service_;

};

#endif // __ROOM_SCENE_CONTROLLER_H__
