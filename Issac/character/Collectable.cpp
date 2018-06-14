#include "Collectable.h"

Collectable *Collectable::createCollectable(int collectableType)
{
	Collectable *pRet = new (std::nothrow) Collectable();
	if (pRet && pRet->init(collectableType))
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

bool Collectable::init(int collectableType)
{
	if (!Sprite::init())
	{
		return false;
	}

	addmoveSpeed = 0;
	addradiusSize = 0;
	addtearSpeed = 0;
	addtearExistTime = 0;
	addhealth = 0;
	addattack = 0;
	enFly = false;

	Sprite* temp_collectableType;
	switch (collectableType)
	{
	case (0):
		break;
	case (1):
		break;
	case (2):
		break;
	}
	this->addChild(temp_collectableType);
	auto phyBody = PhysicsBody::createCircle(12, PHYSICSBODY_MATERIAL_DEFAULT);
	//静态
	phyBody->setDynamic(false);
	//设置物体的恢复力
	phyBody->getShape(0)->setRestitution(0.0f);
	//设置物体的摩擦力
	phyBody->getShape(0)->setFriction(0.0f);
	//碰撞、监听筛选
	phyBody->setCategoryBitmask(0x80);	// 1000_0000(80)
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111(FF)
	phyBody->setContactTestBitmask(0x09); //0000_1001(09)
	//添加物理躯体
	this->addComponent(phyBody);

	this->setTag(9); 
	return true;
}