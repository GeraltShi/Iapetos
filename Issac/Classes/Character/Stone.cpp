#include "Stone.h"

Stone *Stone::createStone(int type_, Size stoneSize_)
{
	Stone *pRet = new (std::nothrow) Stone();
	if (pRet && pRet->init(type_, stoneSize_))
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

bool Stone::init(int stoneType, Size stoneSize)
{
	if (!Sprite::init())
	{
		return false;
	}

	Texture2D *texture_stone = Director::getInstance()->getTextureCache()->addImage("res/gfx/grid/rocks_basement.png");
	Sprite *temp_stone;
	//stoneType=0透明边界，stoneType=1小石头，stoneType=2大石头
	switch (stoneType)
	{
	case (0):
		break;
	case (1):
		temp_stone = Sprite::createWithTexture(texture_stone, Rect(0, 0, 32, 32));
		break;
	case (2):
		temp_stone = Sprite::createWithTexture(texture_stone, Rect(0, 96, 64, 64));
		break;
	}
	if (stoneType > 0)
		this->addChild(temp_stone);
	auto phyBody = PhysicsBody::createBox(stoneSize, PHYSICSBODY_MATERIAL_DEFAULT);
	//静态
	phyBody->setDynamic(false);
	//设置物体的恢复力
	phyBody->getShape(0)->setRestitution(0.5f);
	//设置物体的摩擦力
	phyBody->getShape(0)->setFriction(0.0f);
	//碰撞筛选:不和石头碰撞，选择性监听:和tear碰撞监听
	phyBody->setCategoryBitmask(0x10);	// 0001_0000
	phyBody->setCollisionBitmask(0xEF);   // 1110_1111
	phyBody->setContactTestBitmask(0x04); //0000_0100
	//添加物理躯体
	this->addComponent(phyBody);
	this->setTag(0); //tag=0石头
	return true;
}