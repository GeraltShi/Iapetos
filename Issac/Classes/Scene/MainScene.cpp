#include "MainScene.h"
#include <iostream>
USING_NS_CC;
using namespace std;

Scene * MainScene::createScene()
{
	return create();
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
    //TODO 做！类！ 面！向！对！象！
        //TODO 1.Issac对象    gfx\characters
        //TODO 1.1 Tear对象
        //TODO 2.物品对象       gfx\items
        //TODO 3.怪物对象       gfx\monsters gfx\bosses
        //TODO 4.房间对象       gfx\backdrops
    //TODO peppa的房子位置不对，现在在主界面。主界面应该是菜单，不是房间    gfx\ui
    
    Vector<MenuItem*> MenuItems;
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    MenuItems.pushBack(closeItem);
    
    // repeat for as many menu items as needed
    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu, 1);
    
    peppa = Sprite::create("Peppa.png");
    peppa->setPosition(640, 360);

    addChild(peppa,1,"pig");

    auto l = Label::createWithTTF("开场界面","fonts/simhei.ttf",30);
    l->setPosition(640, 500);
    addChild(l);
    
    scheduleUpdate();

	return true;
}

void MainScene::set_event_listener(IMainSceneListener * listener)
{
    this->listener_ = listener;

    //TODO 事件监听
    auto _touchListener = EventListenerTouchOneByOne::create();

    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        this->listener_->on_touch_began(touch,event);
        return false;
    };

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = [this](Event * event)
    {
        this->listener_->on_mouse_down(event);
        return false;
    };

    auto _keyboard_listener = EventListenerKeyboard::create();
    _keyboard_listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        this->listener_->on_key_pressed(keyCode, event);
    };

    _keyboard_listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        this->listener_->on_key_released(keyCode, event);
    };

    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboard_listener, this);
}

void MainScene::set_model(MainSceneModel model)
{
    this->model = model;
}

void MainScene::update(float delta)
{
    if (model.walking_direction != -1)
    {
        peppa_move(model.walking_direction);
    }
    //TODO Issac所有的状态更新：如碰撞掉血，被炸弹炸掉血，吃小邢邢回血，自身物品状态都由场景触发
        //TODO 碰撞方向判定，闪动效果（提醒玩家螳臂当车了）
        //TODO 碰撞效果，Issac固定掉半格血，怪物可能自爆，也可能还活着
    cout << "Peppa Position: " << peppa->getPositionX() << " " << peppa->getPositionY()<<endl;
}

void MainScene::peppa_move(int direction) const
{
    const int moveSpeed = 6.5;
    int offsetX = 0, offsetY = 0;
    //Todo 以身体作为Position计算，如有需要可重新定义锚点，头只是跟着身体动
    switch (direction)
    {
        case 0:if(peppa->getPositionX() > 135)
                offsetX = -moveSpeed;
            else offsetX = 0;
            break;
        case 1:if(peppa->getPositionX() < 749)
                offsetX = moveSpeed;
            else offsetX = 0;
            break;
        case 2:if(peppa->getPositionY() < 500)
            offsetY = moveSpeed;
            else offsetY = 0;
            break;
        case 3:if(peppa->getPositionY() > 190)
            offsetY = -moveSpeed;
            else offsetY = 0;
            break;
    default:break;
    }
    auto new_posX = peppa->getPositionX() + offsetX;
    auto new_posY = peppa->getPositionY() + offsetY;
    const auto peppaMoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
    peppa->runAction(peppaMoveTo);
}
