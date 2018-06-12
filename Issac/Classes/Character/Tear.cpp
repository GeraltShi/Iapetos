#include "Tear.h"

USING_NS_CC;
using namespace std;

Tear *Tear::createTear()
{
	return create();
}

void Tear::createPhyBody()
{
	auto phyBody = PhysicsBody::createCircle(radiusSize, PHYSICSBODY_MATERIAL_DEFAULT);
	//是否设置物体为静态
	phyBody->setDynamic(true);
	//设置物体的恢复力
	phyBody->getShape(0)->setRestitution(1.0f);
	//设置物体的摩擦力
	phyBody->getShape(0)->setFriction(0.0f);
	//设置物体密度
	phyBody->getShape(0)->setDensity(1.0f);
	//设置质量
	phyBody->getShape(0)->setMass(bodyMass);
	//设置物体是否受重力系数影响
	phyBody->setGravityEnable(false);
	//速度
	phyBody->setVelocity(Vec2(0, 0));
	//碰撞筛选:所有都碰撞，选择性监听:全部碰撞都会监听
	phyBody->setCategoryBitmask(0x04);	// 0000_0100
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111
	phyBody->setContactTestBitmask(0xFF); //1111_1111
	//添加物理躯体
	this->addComponent(phyBody);
}

bool Tear::init()
{
	if (!Moveable::init())
	{
		return false;
	}
	//Tear碰撞大小
	radiusSize = 3;
	//Tear重量
	bodyMass = 10;
	//Tear行走速度
	moveSpeed = 120;
	//Tear攻击1
	attack = 1;
	//生成物理身体
	this->createPhyBody();
	//tag=3
	this->setTag(3);

	auto fcache = SpriteFrameCache::getInstance();
	const auto frame0 = fcache->getSpriteFrameByName("t_frame0");
	const auto frame1 = fcache->getSpriteFrameByName("t_frame1");
	const auto frame2 = fcache->getSpriteFrameByName("t_frame2");
	const auto frame3 = fcache->getSpriteFrameByName("t_frame3");
	const auto frame4 = fcache->getSpriteFrameByName("t_frame4");
	const auto frame5 = fcache->getSpriteFrameByName("t_frame5");
	const auto frame6 = fcache->getSpriteFrameByName("t_frame6");
	const auto frame7 = fcache->getSpriteFrameByName("t_frame7");
	const auto frame8 = fcache->getSpriteFrameByName("t_frame8");
	const auto frame9 = fcache->getSpriteFrameByName("t_frame9");
	const auto frame10 = fcache->getSpriteFrameByName("t_frame10");
	const auto frame11 = fcache->getSpriteFrameByName("t_frame11");
	const auto frame12 = fcache->getSpriteFrameByName("t_frame12");
	const auto frame13 = fcache->getSpriteFrameByName("t_frame13");
	const auto frame14 = fcache->getSpriteFrameByName("t_frame14");
	const auto frame15 = fcache->getSpriteFrameByName("t_frame15");

	Vector<SpriteFrame *> array;
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
	array.pushBack(frame10);
	array.pushBack(frame11);
	array.pushBack(frame12);
	array.pushBack(frame13);
	array.pushBack(frame14);
	array.pushBack(frame15);

	poof_animation = Animation::createWithSpriteFrames(array, 0.05f);
    poof_animation->setLoops(1);
    AnimationCache::getInstance()->addAnimation(poof_animation, "poof_animation");

	Texture2D *tearTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/tears.png");
	SpriteFrame *tearFrame = SpriteFrame::createWithTexture(tearTexture, Rect(0, 32, 32, 32));
	auto temp_tearSprite = createWithSpriteFrame(tearFrame);
	this->addChild(temp_tearSprite);
	return true;
}