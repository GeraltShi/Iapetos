#include "MainScene.h"
#include <iostream>
USING_NS_CC;
using namespace std;

#define XOFFSET 51
#define XSTEP 2
#define YSTEP 32
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
    //TODO 菜单    gfx\ui
    size = Director::getInstance()->getWinSize();
    Texture2D *menutexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/gamemenu.png");
    auto mymenubg = Sprite::createWithTexture(menutexture,Rect(0,0,480,270));
    mymenubg->setAnchorPoint(Point(0,0));
    mymenubg->setPosition(0,0);
//    mymenubg->setScale(size.width/480);
    addChild(mymenubg,0);
    
    
    auto mymenulist1 = Sprite::createWithTexture(menutexture, Rect(32,288,128,48));
    mymenulist1->setAnchorPoint(Point(0,0));
    mymenulist1->setPosition(size.width/2-XOFFSET,size.height/2+YSTEP);
//    mymenulist1->setScale(size.width/480);
    addChild(mymenulist1,1);
    
    auto mymenulist2 = Sprite::createWithTexture(menutexture, Rect(32,288+48,128,48));
    mymenulist2->setAnchorPoint(Point(0,0));
    mymenulist2->setPosition(size.width/2-XOFFSET+XSTEP,size.height/2);
//    mymenulist2->setScale(size.width/480);
    addChild(mymenulist2,1);
    auto mymenulist3 = Sprite::createWithTexture(menutexture, Rect(32,288+96,128,48));
    mymenulist3->setAnchorPoint(Point(0,0));
    mymenulist3->setPosition(size.width/2-XOFFSET+XSTEP*2,size.height/2-YSTEP);
//    mymenulist3->setScale(size.width/480);
    addChild(mymenulist3,1);
    auto mymenulist4 = Sprite::createWithTexture(menutexture, Rect(32,288+144,128,48));
    mymenulist4->setAnchorPoint(Point(0,0));
    mymenulist4->setPosition(size.width/2-XOFFSET+XSTEP*3,size.height/2-YSTEP*2);
//    mymenulist4->setScale(size.width/480);
    addChild(mymenulist4,1);
    auto mymenulist5 = Sprite::createWithTexture(menutexture, Rect(32,288+196,128,48));
    mymenulist5->setAnchorPoint(Point(0,0));
    mymenulist5->setPosition(size.width/2-XOFFSET+XSTEP*4,size.height/2-YSTEP*3);
//    mymenulist5->setScale(size.width/480);
    addChild(mymenulist5,1);
    
    selector_init_x_ = size.width/2-XOFFSET-24;
    selector_init_y_ = size.height/2+YSTEP;
    selector = Sprite::createWithTexture(menutexture, Rect(0,302,32,32));
    selector->setAnchorPoint(Point(0,0));
    selector->setPosition(selector_init_x_,selector_init_y_);
//    selector->setScale(size.width/480);
    addChild(selector,1);

    auto l = Label::createWithTTF("","fonts/simhei.ttf",30);
    l->setPosition(640, 500);
    addChild(l,1);
    
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
    //std::cout << "MenuItem " << model.menun <<" Selected"<< endl;
    //std::cout << "SelectorInit " << selector_init_x <<" "<< selector_init_y << endl;
    menu_update(model.menun);
}

void MainScene::menu_update(int n) const{
    int new_posX = 0; int new_posY = 0;
    switch (n)
    {
        case 0:
            new_posX = selector_init_x_;
            new_posY = selector_init_y_;
            break;
        case 1:
            new_posX = selector_init_x_+XSTEP;
            new_posY = selector_init_y_-YSTEP;
            break;
        case 2:
            new_posX = selector_init_x_+XSTEP*2;
            new_posY = selector_init_y_-YSTEP*2;
            break;
        case 3:
            new_posX = selector_init_x_+XSTEP*3;
            new_posY = selector_init_y_-YSTEP*3;
            break;
        case 4:
            new_posX = selector_init_x_+XSTEP*4;
            new_posY = selector_init_y_-YSTEP*4;
            break;
        default:
            break;
    }
    const auto selectorMoveTo = MoveTo::create(0,Vec2(new_posX, new_posY));
    selector->runAction(selectorMoveTo);
}
