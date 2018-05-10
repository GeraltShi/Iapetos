#include "RoomScene.h"
#include <sstream>

USING_NS_CC;
using namespace std;

Scene *RoomScene::createScene()
{
    return create();
}

bool RoomScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto s = Sprite::create("Peppa.png");
    s->setPosition(640, 360);

    addChild(s);

    auto l = Label::createWithTTF("游戏界面/房间", "fonts/simhei.ttf", 30);
    l->setPosition(640, 500);
    addChild(l);

    auto cl = Label::createWithTTF("点击次数: 0", "fonts/simhei.ttf", 30);
    cl->setPosition(640, 200);
    addChild(cl,1,"c_label");

    //TODO 加载所有界面元素

    return true;
}

void RoomScene::set_event_listener(IRoomSceneListener * listener)
{
    this->listener_ = listener;

    //TODO 事件监听
    auto _touchListener = EventListenerTouchOneByOne::create();

    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        this->listener_->on_touch_began(touch, event);
        return false;
    };

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = [this](Event * event)
    {
        this->listener_->on_mouse_down(event);
        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

void RoomScene::change_count(int c)
{
    auto cl = dynamic_cast<Label *>(getChildByName("c_label"));
    stringstream ss;
    ss << "点击次数: " << c;
    cl->setString(ss.str());
}
