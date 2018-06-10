#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IRoomSceneListener.h"
#include "Model/RoomSceneModel.hpp"
#include "Character/Issac.hpp"
#include "Character/Monster.hpp"
#include "Character/Tear.h"
#include "ViewModel/MiniMapViewModel.h"
#include "ViewModel/RoomViewModel.h"
#include "ViewModel/SimpleItemViewModel.h"
#include "Character/SimpleItem.h"
#include "Character/Stone.h"
#include "Character/Door.h"

#include <vector>

USING_NS_CC;

class RoomScene : public cocos2d::Scene
{
public:
    static Scene *createScene(int roomID);
    //bool init() override;

	bool init(int roomID);
    //CREATE_FUNC(RoomScene)
	static RoomScene* create(int roomID) 
	{ 
		RoomScene *pRet = new(std::nothrow) RoomScene(); 
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
    
//    CC_SYNTHESIZE(RoomSceneModel, model, Model)
    RoomSceneModel model;
    void set_model(RoomSceneModel model);
    CC_SYNTHESIZE_RETAIN(Issac*, player, Player)
    CC_SYNTHESIZE_RETAIN(Sprite*, tearSprite, TearSprite)
    CC_SYNTHESIZE_RETAIN(Sprite*, pausescreen, Pausescreen)
    CC_SYNTHESIZE_RETAIN(SimpleItem*, bomb, Bomb)
	CC_SYNTHESIZE(int, roomID, RoomID)

    void set_event_listener(IRoomSceneListener *listener);
    void update(float delta) override;
    void fire(float dt);
    void monster_move(float dt);
	bool onContactBegin(PhysicsContact& contact);

private:
    IRoomSceneListener * listener_ = nullptr;
    void build_frame_cache() const;
    //使用cocos2d内置Vector管理Sprite等Ref类型的内存
    //和CC_SYNTHESIZE_RETAIN作用类似
	Vector<Monster*> monsters_;
	Vector<Tear*> tears_;
	Vector<Stone*> stones_;
	Vector<Door*> doors_;

    MiniMapViewModel mini_map_vm_;
    RoomViewModel room_vm_;
};

#endif // __ROOM_SCENE_H__
