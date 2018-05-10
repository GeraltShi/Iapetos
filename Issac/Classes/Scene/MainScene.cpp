#include "MainScene.h"

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


    peppa = Sprite::create("Peppa.png");
    peppa->setPosition(640, 360);

    addChild(peppa,1,"pig");

    auto l = Label::createWithTTF("开场界面","fonts/simhei.ttf",30);
    l->setPosition(640, 500);
    addChild(l);
    
    //TODO 加载所有界面元素


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
}

void MainScene::peppa_move(int direction) const
{
    const int moveSpeed = 5;
    int offsetX = 0, offsetY = 0;

    switch (direction)
    {
    case 0:offsetX = -moveSpeed; break;
    case 1:offsetX = moveSpeed; break;
    case 2:offsetY = moveSpeed; break;
    case 3:offsetY = -moveSpeed; break;
    default:break;
    }

    const auto peppaMoveTo = MoveTo::create(0.3, Vec2(peppa->getPositionX() + offsetX, peppa->getPositionY() + offsetY));
    peppa->runAction(peppaMoveTo);
}
