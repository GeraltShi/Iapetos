#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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
    
    // import the texture for character
    auto texture = Director::getInstance()->getTextureCache()->addImage("character_001_isaac.png");
    SpriteFrame *spFrame = SpriteFrame::createWithTexture(texture, Rect(16,256,48,48));
    sprite = Sprite::createWithSpriteFrame(spFrame);

    // add "HelloWorld" splash screen"
    if (sprite == nullptr)
    {
        problemLoading("'character_001_isaac.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
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
        bullet->setPosition(Vec2(sprite->getPositionX(),sprite->getPositionY()));
        
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
    } else if(isKeyPressed(walkRight)) {
        keyPressedDuration(walkRight);
    }
    
    if(isKeyPressed(walkUp)) {
        keyPressedDuration(walkUp);
    } else if(isKeyPressed(walkDown)) {
        keyPressedDuration(walkDown);
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
    bullet->setPosition(Vec2(sprite->getPositionX() + bulletOffsetX, sprite->getPositionY() + bulletOffsetY));
}

void HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code) {
    int offsetX = 0, offsetY = 0;
    bulletOffsetX = 0, bulletOffsetY = 0;
    switch (code) {
        // character response
        case EventKeyboard::KeyCode::KEY_A:
            offsetX = -7;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            offsetX = 7;
            break;
        case EventKeyboard::KeyCode::KEY_W:
            offsetY = 7;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            offsetY = -7;
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
    auto moveTo = MoveTo::create(0.3, Vec2(sprite->getPositionX() + offsetX, sprite->getPositionY() + offsetY));
    sprite->runAction(moveTo);
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
