#include "Door.h"

Door *Door::createDoor(int doorType, const string &doorStyle, const Size &winSize)
{
	Door *pRet = new (std::nothrow) Door();
	if (pRet && pRet->init(doorType, doorStyle, winSize))
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

bool Door::init(int doorType, const string &doorStyle, const Size &winSize)
{
	if (!Sprite::init())
	{
		return false;
	}
	auto phyBody = PhysicsBody::createBox(Size(64, 40), PHYSICSBODY_MATERIAL_DEFAULT);
	//静态
	phyBody->setDynamic(false);
	//设置物体的恢复力
	phyBody->getShape(0)->setRestitution(0.5f);
	//设置物体的摩擦力
	phyBody->getShape(0)->setFriction(0.0f);
	//碰撞、监听筛选
	phyBody->setCategoryBitmask(0x050);	// 0000_0101_0000(050)
	phyBody->setCollisionBitmask(0x18F);   // 0001_1000_1111(18F)
	phyBody->setContactTestBitmask(0x109); //0001_0000_1001(109)
	this->addComponent(phyBody);

	Texture2D *texture_door = Director::getInstance()->getTextureCache()->addImage(doorStyle);
	Sprite *door_ = createWithTexture(texture_door, Rect(0, 0, 64, 48));
	Sprite *door_center = createWithTexture(texture_door, Rect(64, 0, 64, 48));
    Sprite * door_piece_left = createWithTexture(texture_door, Rect(0, 48, 64, 48));
    Sprite * door_piece_right = createWithTexture(texture_door, Rect(64, 48, 64, 48));
	this->addChild(door_,0);
	this->addChild(door_center,0);
    this->addChild(door_piece_left,1,"door_piece_left");
    this->addChild(door_piece_right,1,"door_piece_right");
	this->setRotation(270 + doorType * 90);
	//设置位置
	switch (doorType)
	{
	case (0):
	{
		this->setPosition(36, winSize.height / 2);
		this->getPhysicsBody()->setPositionOffset(Vec2(-16, 0));
		break;
	}
	case (1):
	{
		this->setPosition(winSize.width / 2, winSize.height - 36);
		this->getPhysicsBody()->setPositionOffset(Vec2(0, 16));
		break;
	}
	case (2):
	{
		this->setPosition(winSize.width - 36, winSize.height / 2);
		this->getPhysicsBody()->setPositionOffset(Vec2(16, 0));
		break;
	}
	case (3):
	{
		this->setPosition(winSize.width / 2, 36);
		this->getPhysicsBody()->setPositionOffset(Vec2(0, -16));
		break;
	}
	}

	this->setTag(0); //门tag=0
	return true;
}
