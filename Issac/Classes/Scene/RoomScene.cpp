#include "RoomScene.h"
#include <sstream>
#include <iostream>

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

    Size size = Director::getInstance()->getWinSize();
    std::cout << size.width <<" "<< size.height << endl;
    //TODO 应该有更好的方法生成背景贴图，而不是暴力生成4个或多个碎片
    //TODO 动态加载贴图？如Issac的buff皮肤（在别的贴图上）如何更新
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/01_basement.png");
    //TODO 更小的地图切片和随机性支持
    Sprite * room_piece1 = Sprite::createWithTexture(texture,Rect(0,0,221,143));
    room_piece1->setAnchorPoint(Point(0,0));
    room_piece1->setScale(2, 2);
    room_piece1->setPosition(0, 286);
    addChild(room_piece1,0);
    
    Sprite * room_piece2 = Sprite::createWithTexture(texture,Rect(0,0,221,143));
    room_piece2->setFlippedX(true);
    room_piece2->setAnchorPoint(Point(0,0));
    room_piece2->setScale(2, 2);
    room_piece2->setPosition(442, 286);
    addChild(room_piece2,0);
    
    Sprite * room_piece3 = Sprite::createWithTexture(texture,Rect(0,0,221,143));
    room_piece3->setFlippedY(true);
    room_piece3->setAnchorPoint(Point(0,0));
    room_piece3->setScale(2, 2);
    room_piece3->setPosition(0, 0);
    addChild(room_piece3,0);
    
    Sprite * room_piece4 = Sprite::createWithTexture(texture,Rect(0,0,221,143));
    room_piece4->setFlippedX(true);
    room_piece4->setFlippedY(true);
    room_piece4->setAnchorPoint(Point(0,0));
    room_piece4->setScale(2, 2);
    room_piece4->setPosition(442, 0);
    addChild(room_piece4,0);
    
    //TODO peppa把房子卖给了Issac的身体
    //TODO Issac不能只有身体，还要有头，头要跟着身体动
    //TODO Issac比peppa灵活，他动的时候全身都在跳舞，不动的时候也会眨眼睛，SpriteFrame
    //TODO 弹幕Tear的生成、生命周期、碰撞过程、管理（多Tear对象共存），Tear生成时头会抖
    
    issac = Sprite::create("Peppa.png");
    issac->setPosition(640, 360);

    addChild(issac);

    //TODO 加载所有界面元素
    //TODO 1.石头生成，门生成和进入响应，需触发地图更新，怪没打完逃不出去！ gfx\grid
    //TODO 2.光影遮罩       gfx\overlays res\backdrop（光）
    //TODO 3.物品生成       gfx\items
    
    //TODO 4.小地图和生命值，物品栏在z最大处（最顶层），（且随窗口大小自适应，如来不及就做成固定大小）
    //TODO 4.1 计分板，原版好像没有这个东西，可以做成计时闯关，时间短分高（如果做不出难度更新）
    
    //TODO 5.生成怪物               gfx\monsters gfx\bosses
    //TODO 6.地面破坏效果，由物品生命周期控制，（随机纹理，来不及就不做，与贴图随机选择有关）gfx\effects
    //TODO 7.Issac 吃buff后状态的变化，如换了个皮肤，与类内皮肤成员有关
    //TODO 99. 联机模式，素材中有babyIssac
    //TODO 100. (Issac有宠物，它会自己攻击)   gfx\familiar
    
    auto l = Label::createWithTTF("游戏界面/房间", "fonts/simhei.ttf", 30);
    l->setPosition(640, 500);
    addChild(l);

    auto cl = Label::createWithTTF("点击次数: 0", "fonts/simhei.ttf", 30);
    cl->setPosition(640, 200);
    addChild(cl,1,"c_label");

    //TODO 加载所有界面元素

    scheduleUpdate();
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

void RoomScene::set_model(RoomSceneModel model)
{
    this->model = model;
}

void RoomScene::update(float delta)
{
    if (model.walking_direction != -1)
    {    peppa_move(model.walking_direction);
    }
    //TODO Issac所有的状态更新：如碰撞掉血，被炸弹炸掉血，吃小邢邢回血，自身物品状态都由场景触发
    //TODO 碰撞方向判定，闪动效果（提醒玩家螳臂当车了）
    //TODO 碰撞效果，Issac固定掉半格血，怪物可能自爆，也可能还活着
    std::cout << "Walking direction: "<<model.walking_direction<< endl;
    //std::cout << "Peppa Position: " << issac->getPositionX() << " " << issac->getPositionY()<<endl;
}

void RoomScene::change_count(int c)
{
    auto cl = dynamic_cast<Label *>(getChildByName("c_label"));
    stringstream ss;
    ss << "点击次数: " << c;
    cl->setString(ss.str());
}

void RoomScene::peppa_move(int direction) const
{
    const int moveSpeed = 6.5;
    int offsetX = 0, offsetY = 0;
    //Todo 以身体作为Position计算，如有需要可重新定义锚点，头只是跟着身体动
    switch (direction)
    {
        //012
        //345
        //678
        case 0:if(issac->getPositionX() > 135)
            offsetX = -moveSpeed;
        else offsetX = 0;
            break;
        case 1:if(issac->getPositionX() < 749)
            offsetX = moveSpeed;
        else offsetX = 0;
            break;
        case 2:if(issac->getPositionY() < 500)
            offsetY = moveSpeed;
        else offsetY = 0;
            break;
        case 3:if(issac->getPositionY() > 190)
            offsetY = -moveSpeed;
        else offsetY = 0;
            break;
        default:break;
    }
    auto new_posX = issac->getPositionX() + offsetX;
    auto new_posY = issac->getPositionY() + offsetY;
    const auto peppaMoveTo = MoveTo::create(0.3, Vec2(new_posX, new_posY));
    issac->runAction(peppaMoveTo);
}
