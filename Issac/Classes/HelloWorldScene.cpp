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
    
    // add bullet
    auto texture_bullet = Director::getInstance()->getTextureCache()->addImage("tears.png");
    SpriteFrame *btFrame = SpriteFrame::createWithTexture(texture_bullet, Rect(0,96,32,32));
    bullet = Sprite::createWithSpriteFrame(btFrame);
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
    Node::update(delta);
    auto walkLeft = EventKeyboard::KeyCode::KEY_A, walkRight = EventKeyboard::KeyCode::KEY_D,
    walkUp = EventKeyboard::KeyCode::KEY_W, walkDown = EventKeyboard::KeyCode::KEY_S,
    bulletLeft = EventKeyboard::KeyCode::KEY_LEFT_ARROW,
    bulletRight = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
    bulletUp = EventKeyboard::KeyCode::KEY_UP_ARROW,
    bulletDown = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    if(isKeyPressed(walkLeft)) {
        keyPressedDuration(walkLeft);
        swapTexture(headSprite, texture, cocos2d::Rect(64,0,32,32));
        headSprite->setFlippedX(true);
    } else if(isKeyPressed(walkRight)) {
        keyPressedDuration(walkRight);
        swapTexture(headSprite, texture, cocos2d::Rect(64,0,32,32));
        headSprite->setFlippedX(false);
    }
    
    if(isKeyPressed(walkUp)) {
        keyPressedDuration(walkUp);
        swapTexture(headSprite, texture, cocos2d::Rect(128,0,32,32));
    } else if(isKeyPressed(walkDown)) {
        keyPressedDuration(walkDown);
        swapTexture(headSprite, texture, cocos2d::Rect(0,0,32,32));
        walkThread();
    }
    
    if(isKeyPressed(bulletLeft)) {
        keyPressedDuration(bulletLeft);
        bullet->setVisible(true);
    } else if (isKeyPressed(bulletRight)) {
        keyPressedDuration(bulletRight);
        bullet->setVisible(true);
    } else if (isKeyPressed(bulletUp)) {
        keyPressedDuration(bulletUp);
        bullet->setVisible(true);
    } else if (isKeyPressed(bulletDown)) {
        keyPressedDuration(bulletDown);
        bullet->setVisible(true);
    } else {
        bullet->setVisible(false);
    }
    bullet->setPosition(Vec2(headSprite->getPositionX() + bulletOffsetX, headSprite->getPositionY() + bulletOffsetY));
}

void HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code) {
    int offsetX = 0, offsetY = 0;
    int moveSpeed = 5;
    bulletOffsetX = 0, bulletOffsetY = 0;
    switch (code) {
        // character response
        case EventKeyboard::KeyCode::KEY_A:
            offsetX = -moveSpeed;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            offsetX = moveSpeed;
            break;
        case EventKeyboard::KeyCode::KEY_W:
            offsetY = moveSpeed;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            offsetY = -moveSpeed;
            walkThread();
            break;
        // bullet response
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

void HelloWorld::walkThread(){
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
    Vector<cocos2d::SpriteFrame *> array;
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
    auto animation = Animation::createWithSpriteFrames(array, 0.2f);
    bodySprite->runAction(RepeatForever::create(Animate::create(animation)));
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
