#include"Door.h"

Door* Door::createDoor(int doorType, const string& doorStyle, const Size& winSize) 
{
	Door *pRet = new(std::nothrow)  Door();
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

bool Door::init(int doorType, const string& doorStyle, const Size& winSize) 
{
	if (!Sprite::init())
	{
		return false;
	}
	auto phyBody = PhysicsBody::createBox(Size(64,40), PHYSICSBODY_MATERIAL_DEFAULT);
	//��̬  
	phyBody->setDynamic(false);
	//��������Ļָ���  
	phyBody->getShape(0)->setRestitution(0.0f);
	//���������Ħ����  
	phyBody->getShape(0)->setFriction(1.0f);
	//��ײɸѡ:����ʯͷ��ײ��ѡ���Լ���:��tear��ײ����
	phyBody->setCategoryBitmask(0x10);    // 0001_0000
	phyBody->setCollisionBitmask(0xEF);   // 1110_1111
	phyBody->setContactTestBitmask(0x04);	//0000_0100
	this->addComponent(phyBody);

	Texture2D *texture_door = Director::getInstance()->getTextureCache()->addImage(doorStyle);
	Sprite * door_ = Sprite::createWithTexture(texture_door, Rect(0, 0, 64, 48));
	Sprite * door_center = Sprite::createWithTexture(texture_door, Rect(64, 0, 64, 48));
	this->addChild(door_);
	this->addChild(door_center);
	
	switch (doorType) {
	case(0): {
		this->setRotation(270);
		this->getPhysicsBody()->setPositionOffset(Vec2(-16, 0));
		break;
	}
	}
	this->setPosition(36, winSize.height / 2);
	this->setTag(0); //��tag=0
	return true;
}