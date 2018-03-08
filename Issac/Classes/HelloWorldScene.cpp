#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <thread>

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    
    // import the head_texture for character
    texture = Director::getInstance()->getTextureCache()->addImage("character_001_isaac.png");
    SpriteFrame *headFrame = SpriteFrame::createWithTexture(texture, Rect(0,0,32,32));
    headSprite = Sprite::createWithSpriteFrame(headFrame);
    
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(texture, Rect(0,32,32,32));
    bodySprite = Sprite::createWithSpriteFrame(bodyFrame);
    

    // add "HelloWorld" splash screen"
    if (headSprite == nullptr)
    {
        problemLoading("'character_001_isaac.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        headSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        bodySprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 12));

        // add the sprite as a child to this layer
        this->addChild(headSprite, 1);
        // add to a sublayer
        this->addChild(bodySprite, 0);
    }
    
    // support multiple bullets
    // TODO: need to add direction property of the bullet, to support flying
    texture_bullet = Director::getInstance()->getTextureCache()->addImage("tears.png");
    // add bullet
    
    SpriteFrame *btFrame = SpriteFrame::createWithTexture(texture_bullet, Rect(0,96,32,32));
    Sprite *bullet = Sprite::createWithSpriteFrame(btFrame);
    bulletQueue.push_back(bullet);
    if (bullet == nullptr)
    {
        problemLoading("'tears.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        bullet->setPosition(Vec2(headSprite->getPositionX(),headSprite->getPositionY()));
        
        // add the sprite as a child to this layer
        this->addChild(bullet, 0);
    }
    
    player = Player::create();
    player->setPosition(Vec2(origin.x + visibleSize.width / 2
                             , origin.y + visibleSize.height / 2));
    this->addChild(player, 5);
    
    // add Keyboard Listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        keys[keyCode] = true;
        log("%d Pressed", keyCode);
    };
    
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        keys[keyCode] = false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    this->scheduleUpdate();
    return true;
}

bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode keyCode) {
    if(keys[keyCode]) {
        return true;
    } else {
        return false;
    }
}

void HelloWorld::update(float delta) {
    player->update();
    Node::update(delta);
    auto walkLeft = EventKeyboard::KeyCode::KEY_A, walkRight = EventKeyboard::KeyCode::KEY_D,
    walkUp = EventKeyboard::KeyCode::KEY_W, walkDown = EventKeyboard::KeyCode::KEY_S,
    bulletLeft = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
    bulletRight = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
    bulletUp = EventKeyboard::KeyCode::KEY_UP_ARROW,
    bulletDown = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    if(isKeyPressed(walkLeft)) {
        keyPressedDuration(walkLeft);
        bodySprite->setFlippedX(true);
        player->move(0);
    } else if(isKeyPressed(walkRight)) {
        keyPressedDuration(walkRight);
        bodySprite->setFlippedX(false);
        player->move(1);
    }
    
    if(isKeyPressed(walkUp)) {
        keyPressedDuration(walkUp);
        player->move(2);
    } else if(isKeyPressed(walkDown)) {
        keyPressedDuration(walkDown);
        player->move(3); 
    }
    
    if(isKeyPressed(bulletLeft)) {
        swapTexture(headSprite, texture, cocos2d::Rect(64,0,32,32));
        headSprite->setFlippedX(true);
        keyPressedDuration(bulletLeft);
        bulletQueue[0]->setVisible(true);
    } else if (isKeyPressed(bulletRight)) {
        swapTexture(headSprite, texture, cocos2d::Rect(64,0,32,32));
        headSprite->setFlippedX(false);
        keyPressedDuration(bulletRight);
        bulletQueue[0]->setVisible(true);
        bulletFlyX = 1;
        bulletFlyY = 0;
    } else if (isKeyPressed(bulletUp)) {
        swapTexture(headSprite, texture, cocos2d::Rect(128,0,32,32));
        keyPressedDuration(bulletUp);
        bulletQueue[0]->setVisible(true);
    } else if (isKeyPressed(bulletDown)) {
        swapTexture(headSprite, texture, cocos2d::Rect(0,0,32,32));
        keyPressedDuration(bulletDown);
        bulletQueue[0]->setVisible(true);
    } else {
        bulletQueue[0]->setVisible(false);
    }
    bulletQueue[0]->setPosition(Vec2(headSprite->getPositionX() + bulletOffsetX, headSprite->getPositionY() + bulletOffsetY));
    auto bulletAction = MoveTo::create(0, Vec2(headSprite->getPositionX() + bulletFlyX, headSprite->getPositionY() + bulletFlyY));
    bulletQueue[0]->runAction(bulletAction);
    if(keys[EventKeyboard::KeyCode::KEY_A]){
        walkThread(EventKeyboard::KeyCode::KEY_A);
    } else if (!keys[EventKeyboard::KeyCode::KEY_A]){
        
    }
    
    if(keys[EventKeyboard::KeyCode::KEY_D]){
        walkThread(EventKeyboard::KeyCode::KEY_D);
    } else if (!keys[EventKeyboard::KeyCode::KEY_D]){
        
    }
    
    if(keys[EventKeyboard::KeyCode::KEY_W]){
        walkThread(EventKeyboard::KeyCode::KEY_W);
    } else if (!keys[EventKeyboard::KeyCode::KEY_W]){
        
    }
    
    if(keys[EventKeyboard::KeyCode::KEY_S]){
        walkThread(EventKeyboard::KeyCode::KEY_S);
    } else if (!keys[EventKeyboard::KeyCode::KEY_S]){
        
    }
    
}

void HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code) {
    int offsetX = 0, offsetY = 0;
    int moveSpeed = 5;
    bulletOffsetX = 0, bulletOffsetY = 0;
    switch (code) {
        // character response
        case EventKeyboard::KeyCode::KEY_A:
            offsetX = -moveSpeed;
            //walkThread(code);
            break;
        case EventKeyboard::KeyCode::KEY_D:
            offsetX = moveSpeed;
            //walkThread(code);
            break;
        case EventKeyboard::KeyCode::KEY_W:
            offsetY = moveSpeed;
            //walkThread(code);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            offsetY = -moveSpeed;
            //walkThread(code);
            break;
        // bullet listening
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            bulletOffsetX = -16;
            bulletOffsetY = 0;
            bulletEnable = true;
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            bulletOffsetX = 16;
            bulletOffsetY = 0;
            bulletEnable = true;
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            bulletOffsetX = 0;
            bulletOffsetY = 16;
            bulletEnable = true;
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            bulletOffsetX = 0;
            bulletOffsetY = -16;
            bulletEnable = true;
            break;
        default:
            offsetY = offsetX = 0;
            bulletOffsetX = bulletOffsetY = 0;
            bulletEnable = false;
            break;
    }
    // 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
    auto headMoveTo = MoveTo::create(0.3, Vec2(headSprite->getPositionX() + offsetX, headSprite->getPositionY() + offsetY));
    headSprite->runAction(headMoveTo);
    auto bodyMoveTo = MoveTo::create(0.3, Vec2(bodySprite->getPositionX() + offsetX, bodySprite->getPositionY() + offsetY));
    bodySprite->runAction(bodyMoveTo);
}


void HelloWorld::swapTexture(cocos2d::Sprite *sprite, cocos2d::Texture2D *texture, const cocos2d::Rect &rect){
    //Define a new Frame and set
    SpriteFrame *newFrame = SpriteFrame::createWithTexture(texture, rect);
    sprite->setSpriteFrame(newFrame);
}

void HelloWorld::walkThread(EventKeyboard::KeyCode code){
    auto frame0 = SpriteFrame::createWithTexture(texture, Rect(32*6,32*0,32,32));
    auto frame1 = SpriteFrame::createWithTexture(texture, Rect(32*7,32*0,32,32));
    auto frame2 = SpriteFrame::createWithTexture(texture, Rect(32*0,32*1,32,32));
    auto frame3 = SpriteFrame::createWithTexture(texture, Rect(32*1,32*1,32,32));
    auto frame4 = SpriteFrame::createWithTexture(texture, Rect(32*2,32*1,32,32));
    auto frame5 = SpriteFrame::createWithTexture(texture, Rect(32*3,32*1,32,32));
    auto frame6 = SpriteFrame::createWithTexture(texture, Rect(32*4,32*1,32,32));
    auto frame7 = SpriteFrame::createWithTexture(texture, Rect(32*5,32*1,32,32));
    auto frame8 = SpriteFrame::createWithTexture(texture, Rect(32*6,32*1,32,32));
    auto frame9 = SpriteFrame::createWithTexture(texture, Rect(32*7,32*1,32,32));
    
    auto frame10 = SpriteFrame::createWithTexture(texture, Rect(32*0,32*2,32,32));
    auto frame11 = SpriteFrame::createWithTexture(texture, Rect(32*1,32*2,32,32));
    auto frame12 = SpriteFrame::createWithTexture(texture, Rect(32*2,32*2,32,32));
    auto frame13 = SpriteFrame::createWithTexture(texture, Rect(32*3,32*2,32,32));
    auto frame14 = SpriteFrame::createWithTexture(texture, Rect(32*4,32*2,32,32));
    auto frame15 = SpriteFrame::createWithTexture(texture, Rect(32*5,32*2,32,32));
    auto frame16 = SpriteFrame::createWithTexture(texture, Rect(32*6,32*2,32,32));
    auto frame17 = SpriteFrame::createWithTexture(texture, Rect(32*7,32*2,32,32));
    auto frame18 = SpriteFrame::createWithTexture(texture, Rect(32*0,32*3,32,32));
    auto frame19 = SpriteFrame::createWithTexture(texture, Rect(32*1,32*3,32,32));
    
    Vector<cocos2d::SpriteFrame *> array;
    switch (code) {
        case EventKeyboard::KeyCode::KEY_W:
            array.clear(); // just backplay
            array.pushBack(frame9);
            array.pushBack(frame8);
            array.pushBack(frame7);
            array.pushBack(frame6);
            array.pushBack(frame5);
            array.pushBack(frame4);
            array.pushBack(frame3);
            array.pushBack(frame2);
            array.pushBack(frame1);
            array.pushBack(frame0);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            array.clear();
            array.pushBack(frame0);
            array.pushBack(frame1);
            array.pushBack(frame2);
            array.pushBack(frame3);
            array.pushBack(frame4);
            array.pushBack(frame5);
            array.pushBack(frame6);
            array.pushBack(frame7);
            array.pushBack(frame8);
            array.pushBack(frame9);
            break;
        case EventKeyboard::KeyCode::KEY_A:
            array.clear(); //set flip x true
            array.pushBack(frame10);
            array.pushBack(frame11);
            array.pushBack(frame12);
            array.pushBack(frame13);
            array.pushBack(frame14);
            array.pushBack(frame15);
            array.pushBack(frame16);
            array.pushBack(frame17);
            array.pushBack(frame18);
            array.pushBack(frame19);
        case EventKeyboard::KeyCode::KEY_D:
            array.clear();
            array.pushBack(frame10);
            array.pushBack(frame11);
            array.pushBack(frame12);
            array.pushBack(frame13);
            array.pushBack(frame14);
            array.pushBack(frame15);
            array.pushBack(frame16);
            array.pushBack(frame17);
            array.pushBack(frame18);
            array.pushBack(frame19);
        default:
            break;
    }
    auto animation = Animation::createWithSpriteFrames(array, 0.1f);
    bodyAction = RepeatForever::create(Animate::create(animation));
    bodySprite->runAction(bodyAction);
    //TODO: need to solve the repeating issue after altering the direction, flashing bug remains
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
