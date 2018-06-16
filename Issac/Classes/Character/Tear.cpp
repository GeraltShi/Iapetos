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
	//碰撞、监听筛选
	phyBody->setCategoryBitmask(0x008);	// 0000_0000_1000(008)
	phyBody->setCollisionBitmask(0xFFF);   // 1111_1111_1111(FFF)
	phyBody->setContactTestBitmask(0xFFF); //1111_1111_1111(FFF)
	//添加物理躯体
	this->addComponent(phyBody);
}

string Tear::getPoofAnimation()
{
    return "poof_animation";
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
	bodyMass = 5;
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
	SpriteFrame *tearFrame = SpriteFrame::createWithTexture(tearTexture, Rect(160, 0, 32, 32));
	auto temp_tearSprite = createWithSpriteFrame(tearFrame);
	this->addChild(temp_tearSprite);
	return true;
}

MonsterTear *MonsterTear::createMonsterTear()
{
    return create();
}

void MonsterTear::createPhyBody()
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
    //碰撞、监听筛选
    phyBody->setCategoryBitmask(0x08);    // 0000_1000
    phyBody->setCollisionBitmask(0xFF);   // 1111_1111
    phyBody->setContactTestBitmask(0xFF); //1111_1111
    //添加物理躯体
    this->addComponent(phyBody);
}

string MonsterTear::getPoofAnimation()
{
    return "mt_poof_animation";
}

bool MonsterTear::init()
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
    const auto mtframe0 = fcache->getSpriteFrameByName("mt_frame0");
    const auto mtframe1 = fcache->getSpriteFrameByName("mt_frame1");
    const auto mtframe2 = fcache->getSpriteFrameByName("mt_frame2");
    const auto mtframe3 = fcache->getSpriteFrameByName("mt_frame3");
    const auto mtframe4 = fcache->getSpriteFrameByName("mt_frame4");
    const auto mtframe5 = fcache->getSpriteFrameByName("mt_frame5");
    const auto mtframe6 = fcache->getSpriteFrameByName("mt_frame6");
    const auto mtframe7 = fcache->getSpriteFrameByName("mt_frame7");
    const auto mtframe8 = fcache->getSpriteFrameByName("mt_frame8");
    const auto mtframe9 = fcache->getSpriteFrameByName("mt_frame9");
    const auto mtframe10 = fcache->getSpriteFrameByName("mt_frame10");
    const auto mtframe11 = fcache->getSpriteFrameByName("mt_frame11");
    const auto mtframe12 = fcache->getSpriteFrameByName("mt_frame12");
    const auto mtframe13 = fcache->getSpriteFrameByName("mt_frame13");
    const auto mtframe14 = fcache->getSpriteFrameByName("mt_frame14");
    const auto mtframe15 = fcache->getSpriteFrameByName("mt_frame15");
    
    Vector<SpriteFrame *> mtarray;
    mtarray.pushBack(mtframe0);
    mtarray.pushBack(mtframe1);
    mtarray.pushBack(mtframe2);
    mtarray.pushBack(mtframe3);
    mtarray.pushBack(mtframe4);
    mtarray.pushBack(mtframe5);
    mtarray.pushBack(mtframe6);
    mtarray.pushBack(mtframe7);
    mtarray.pushBack(mtframe8);
    mtarray.pushBack(mtframe9);
    mtarray.pushBack(mtframe10);
    mtarray.pushBack(mtframe11);
    mtarray.pushBack(mtframe12);
    mtarray.pushBack(mtframe13);
    mtarray.pushBack(mtframe14);
    mtarray.pushBack(mtframe15);
    
    mt_poof_animation = Animation::createWithSpriteFrames(mtarray, 0.05f);
    mt_poof_animation->setLoops(1);
    AnimationCache::getInstance()->addAnimation(mt_poof_animation, "mt_poof_animation");
    
    Texture2D *mtearTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/enemybullets.png");
    SpriteFrame *mtearFrame = SpriteFrame::createWithTexture(mtearTexture, Rect(160, 0, 32, 32));
    auto mtemp_tearSprite = createWithSpriteFrame(mtearFrame);
    this->addChild(mtemp_tearSprite);
    return true;
}
