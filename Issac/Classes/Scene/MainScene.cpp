#include "MainScene.h"
#include <iostream>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
using namespace std;

#define XOFFSET 45
#define XSTEP 3
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
    // 主界面
    Texture2D *titlemenutexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/titlemenu.png");
    bg = Sprite::createWithTexture(titlemenutexture, Rect(0,0,480,270));
    auto title = Sprite::createWithTexture(titlemenutexture, Rect(0,270,480,108));
    bg->setAnchorPoint(Point(0,0));
    bg->setPosition(0,16); // TODO 这里为了填上黑边，y轴加了16
    title->setPosition(221,200);
    addChild(bg,0);
    bg->addChild(title,1);
    auto start = Sprite::createWithTexture(titlemenutexture, Rect(0,378,164,162));
    auto startplay0 = SpriteFrame::createWithTexture(titlemenutexture, Rect(0,378,162,162));
    auto startplay1 = SpriteFrame::createWithTexture(titlemenutexture, Rect(162,378,162,162));
    start->setPosition(221,100);
    bg->addChild(start,0);
    Vector<SpriteFrame*> startFrames;
    startFrames.pushBack(startplay0);
    startFrames.pushBack(startplay1);
    Animation * startAnimation = Animation::createWithSpriteFrames(startFrames, 0.3f);
    startAnimation->setLoops(-1);
    startAnimation->setRestoreOriginalFrame(true);
    Animate * startAnimate = Animate::create(startAnimation);
    start->runAction(startAnimate);
    
    Texture2D *gamemenutexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/gamemenu.png");
    auto gamemenubg = Sprite::createWithTexture(gamemenutexture,Rect(0,0,480,270));
    gamemenubg->setAnchorPoint(Point(0,0));
    gamemenubg->setPosition(0,-270);
    bg->addChild(gamemenubg,0);
    
    Texture2D *menuoverlaytexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/menuoverlay.png");
    Sprite * menuoverlay = Sprite::createWithTexture(menuoverlaytexture, Rect(0,0,480,270));
    menuoverlay->setScale(442.f/480.f, 286.f/270.f);
    menuoverlay->setPosition(221, 143);
    this->addChild(menuoverlay,2);
    Texture2D *menushadowtexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/menushadow.png");
    Sprite * menushadow = Sprite::createWithTexture(menushadowtexture, Rect(0,0,256,150));
    menushadow->setAnchorPoint(Vec2(0,0));
    menushadow->setPosition(0, 0);
    this->addChild(menushadow,2);
//    Texture2D *emptyscreentexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/emptyscreen.png");
//    auto emptyscreenbg = Sprite::createWithTexture(emptyscreentexture, Rect(0,0,480,270));
//    emptyscreenbg->setAnchorPoint(Point(0,0));
//    emptyscreenbg->setPosition(-480,270);
//    addChild(emptyscreenbg,0);
    
    
    // 菜单列表
    size = Director::getInstance()->getWinSize();
    auto gamemenulist1 = Sprite::createWithTexture(gamemenutexture, Rect(32,288,128,48));
    gamemenulist1->setAnchorPoint(Point(0,0));
    gamemenulist1->setPosition(size.width/2-XOFFSET,size.height/2+YSTEP);
    gamemenubg->addChild(gamemenulist1,1);
    
    auto gamemenulist2 = Sprite::createWithTexture(gamemenutexture, Rect(32,288+48,128,48));
    gamemenulist2->setAnchorPoint(Point(0,0));
    gamemenulist2->setPosition(size.width/2-XOFFSET+XSTEP,size.height/2);
    gamemenubg->addChild(gamemenulist2,1);
    auto gamemenulist3 = Sprite::createWithTexture(gamemenutexture, Rect(32,288+96,128,48));
    gamemenulist3->setAnchorPoint(Point(0,0));
    gamemenulist3->setPosition(size.width/2-XOFFSET+XSTEP*2,size.height/2-YSTEP);
    gamemenubg->addChild(gamemenulist3,1);
    auto gamemenulist4 = Sprite::createWithTexture(gamemenutexture, Rect(32,288+144,128,48));
    gamemenulist4->setAnchorPoint(Point(0,0));
    gamemenulist4->setPosition(size.width/2-XOFFSET+XSTEP*3,size.height/2-YSTEP*2);
    gamemenubg->addChild(gamemenulist4,1);
    auto gamemenulist5 = Sprite::createWithTexture(gamemenutexture, Rect(32,288+196,128,48));
    gamemenulist5->setAnchorPoint(Point(0,0));
    gamemenulist5->setPosition(size.width/2-XOFFSET+XSTEP*4,size.height/2-YSTEP*3);
    gamemenubg->addChild(gamemenulist5,1);
    
    //光标
    selector_init_x_ = size.width/2-XOFFSET-24;
    selector_init_y_ = size.height/2+YSTEP;
    selector = Sprite::createWithTexture(gamemenutexture, Rect(0,302,32,32));
    selector->setAnchorPoint(Point(0,0));
    selector->setPosition(selector_init_x_,selector_init_y_);
    gamemenubg->addChild(selector,1);
    
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
    view_update(model.view);
//    std::cout << model.menun << " " << model.view << " " << viewflag_ << endl;
}

void MainScene::menu_update(int n) const{
    int new_posX = 0; int new_posY = 0;
    if(model.view == 1){
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
}

void MainScene::view_update(int view) {
    if(view == 0){
        if(viewflag_!= 0){
            const auto BgMoveBack = MoveTo::create(0.3,Vec2(0, 16)); // TODO 这里为了填上黑边，y轴加了16
            bg->stopAllActions();
            bg->runAction(BgMoveBack);
            viewflag_ = 0;
        }
    }
    else{
        if(viewflag_!= 1){
            const auto BgMoveTo = MoveTo::create(0.3,Vec2(0, 270));
            bg->stopAllActions();
            bg->runAction(BgMoveTo);
            viewflag_ = 1;
        }
    }
    
}

