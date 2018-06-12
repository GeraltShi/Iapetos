#include "Monster.hpp"
#include "cocos2d.h"

using namespace cocos2d;

# define ROOT2 1.41421356

bool Monster::init()
{
	if (!Moveable::init())
	{
		return false;
	}

	moving = false;
	fireCoolTime = 3;
	//tag=2是怪物
	this->setTag(2);

	//不要将Texture保存在类,用的时候直接从TextureCache中获取
	const auto monster_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/rebirth/monster_207_fatty.png");
    const auto monster_dead_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/effects/effect_002_bloodpoof.png");
	SpriteFrame *headFrame = SpriteFrame::createWithTexture(monster_texture_, Rect(0, 0, 32, 32));
	Sprite * headSprite = createWithSpriteFrame(headFrame);
	SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(monster_texture_, Rect(192, 224, 64, 64));
	Sprite * bodySprite = createWithSpriteFrame(bodyFrame);

	build_sprite_frame_cache(monster_texture_, monster_dead_texture_);
	build_animation_cache();

	this->addChild(headSprite, 1, "head");
	this->addChild(bodySprite, 0, "body");
	headSprite->setPosition(Vec2(0, 10));
	this->setPosition(Vec2(221, 143));


	return true;
}

Tear* Monster::Fire(Vec2 targetPos)
{
	//创建一个Tear
	Tear* myTear = Tear::createTear();
	//设定初始tear位置和速度
	double diffX = abs(targetPos.x - this->getPosition().x); 
	double diffY = abs(targetPos.y - this->getPosition().y);
	double dis = sqrt(diffX*diffX + diffY * diffY);
	double tear_V = moveSpeed + tearSpeed;		
	myTear->getPhysicsBody()->setVelocity(Vec2(tear_V*diffX/dis, tear_V*diffY/dis ));
	//初始位置
	myTear->setPosition(Vec2(getPosition().x + MonTearOffset * diffX / dis, getPosition().y + MonTearOffset * diffY / dis));
	//存在时间,攻击
	myTear->setTearExistTime(tearExistTime);
	myTear->setAttack(attack);
	//是Monster发射的
	myTear->setTag(3);
	return myTear;
}

void Monster::build_sprite_frame_cache(Texture2D *texture_, Texture2D *dead_texture_) const
{
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0, 0, 32, 32)), "head_frame0");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32, 0, 32, 32)), "head_frame1");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64, 0, 32, 32)), "head_frame2");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(96, 0, 32, 32)), "head_frame3");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(128, 0, 32, 32)), "head_frame4");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(160, 0, 32, 32)), "head_frame5");

	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 32, 64, 64)), "monster_hwalk_frame0");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 32, 64, 64)), "monster_hwalk_frame1");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 32, 64, 64)), "monster_hwalk_frame2");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 32, 64, 64)), "monster_hwalk_frame3");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 32, 64, 64)), "monster_hwalk_frame4");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 5, 32, 64, 64)), "monster_hwalk_frame5");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 6, 32, 64, 64)), "monster_hwalk_frame6");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 7, 32, 64, 64)), "monster_hwalk_frame7");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 32, 64, 64)), "monster_hwalk_frame8");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 96, 64, 64)), "monster_hwalk_frame9");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 96, 64, 64)), "monster_hwalk_frame10");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 96, 64, 64)), "monster_hwalk_frame11");

	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 160, 64, 64)), "monster_vwalk_frame0");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 160, 64, 64)), "monster_vwalk_frame1");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 160, 64, 64)), "monster_vwalk_frame2");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 160, 64, 64)), "monster_vwalk_frame3");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 160, 64, 64)), "monster_vwalk_frame4");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 5, 160, 64, 64)), "monster_vwalk_frame5");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 6, 160, 64, 64)), "monster_vwalk_frame6");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 7, 160, 64, 64)), "monster_vwalk_frame7");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 160, 64, 64)), "monster_vwalk_frame8");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 224, 64, 64)), "monster_vwalk_frame9");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 224, 64, 64)), "monster_vwalk_frame10");
	spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 224, 64, 64)), "monster_vwalk_frame11");
    
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 0, 64 * 0,64,64)), "dead_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 1, 64 * 0,64,64)), "dead_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 2, 64 * 0,64,64)), "dead_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 3, 64 * 0,64,64)), "dead_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 0, 64 * 1,64,64)), "dead_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 1, 64 * 1,64,64)), "dead_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 2, 64 * 1,64,64)), "dead_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 3, 64 * 1,64,64)), "dead_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 0, 64 * 2,64,64)), "dead_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 1, 64 * 2,64,64)), "dead_frame9");
    
}

void Monster::build_animation_cache()
{
	auto spriteCache = SpriteFrameCache::getInstance();
	auto aniCache = AnimationCache::getInstance();

	const auto head_frame0 = spriteCache->getSpriteFrameByName("head_frame0");
	const auto head_frame1 = spriteCache->getSpriteFrameByName("head_frame1");
	const auto head_frame2 = spriteCache->getSpriteFrameByName("head_frame2");
	const auto head_frame3 = spriteCache->getSpriteFrameByName("head_frame3");
	const auto head_frame4 = spriteCache->getSpriteFrameByName("head_frame4");
	const auto head_frame5 = spriteCache->getSpriteFrameByName("head_frame5");
	Vector<SpriteFrame*> headFrames;
	headFrames.pushBack(head_frame0);
	headFrames.pushBack(head_frame1);
	headFrames.pushBack(head_frame2);
	headFrames.pushBack(head_frame3);
	headFrames.pushBack(head_frame4);
	headFrames.pushBack(head_frame5);
	Animation * head_animation = Animation::createWithSpriteFrames(headFrames, 0.1f);
	head_animation->setLoops(-1);
	head_animation->setRestoreOriginalFrame(true);
	aniCache->addAnimation(head_animation, "head_animation");

	const auto vwalk_frame0 = spriteCache->getSpriteFrameByName("monster_vwalk_frame0");
	const auto vwalk_frame1 = spriteCache->getSpriteFrameByName("monster_vwalk_frame1");
	const auto vwalk_frame2 = spriteCache->getSpriteFrameByName("monster_vwalk_frame2");
	const auto vwalk_frame3 = spriteCache->getSpriteFrameByName("monster_vwalk_frame3");
	const auto vwalk_frame4 = spriteCache->getSpriteFrameByName("monster_vwalk_frame4");
	const auto vwalk_frame5 = spriteCache->getSpriteFrameByName("monster_vwalk_frame5");
	const auto vwalk_frame6 = spriteCache->getSpriteFrameByName("monster_vwalk_frame6");
	const auto vwalk_frame7 = spriteCache->getSpriteFrameByName("monster_vwalk_frame7");
	const auto vwalk_frame8 = spriteCache->getSpriteFrameByName("monster_vwalk_frame8");
	const auto vwalk_frame9 = spriteCache->getSpriteFrameByName("monster_vwalk_frame9");
	const auto vwalk_frame10 = spriteCache->getSpriteFrameByName("monster_vwalk_frame10");
	const auto vwalk_frame11 = spriteCache->getSpriteFrameByName("monster_vwalk_frame11");
	Vector<SpriteFrame*> vwalkFrames;
	vwalkFrames.pushBack(vwalk_frame0);
	vwalkFrames.pushBack(vwalk_frame1);
	vwalkFrames.pushBack(vwalk_frame2);
	vwalkFrames.pushBack(vwalk_frame3);
	vwalkFrames.pushBack(vwalk_frame4);
	vwalkFrames.pushBack(vwalk_frame5);
	vwalkFrames.pushBack(vwalk_frame6);
	vwalkFrames.pushBack(vwalk_frame7);
	vwalkFrames.pushBack(vwalk_frame8);
	vwalkFrames.pushBack(vwalk_frame9);
	vwalkFrames.pushBack(vwalk_frame10);
	vwalkFrames.pushBack(vwalk_frame11);
	Animation * vwalk_animation = Animation::createWithSpriteFrames(vwalkFrames, 0.1f);
	vwalk_animation->setLoops(-1);
	vwalk_animation->setRestoreOriginalFrame(true);
	aniCache->addAnimation(vwalk_animation, "monster_vwalk_animation");


	const auto hwalk_frame0 = spriteCache->getSpriteFrameByName("monster_hwalk_frame0");
	const auto hwalk_frame1 = spriteCache->getSpriteFrameByName("monster_hwalk_frame1");
	const auto hwalk_frame2 = spriteCache->getSpriteFrameByName("monster_hwalk_frame2");
	const auto hwalk_frame3 = spriteCache->getSpriteFrameByName("monster_hwalk_frame3");
	const auto hwalk_frame4 = spriteCache->getSpriteFrameByName("monster_hwalk_frame4");
	const auto hwalk_frame5 = spriteCache->getSpriteFrameByName("monster_hwalk_frame5");
	const auto hwalk_frame6 = spriteCache->getSpriteFrameByName("monster_hwalk_frame6");
	const auto hwalk_frame7 = spriteCache->getSpriteFrameByName("monster_hwalk_frame7");
	const auto hwalk_frame8 = spriteCache->getSpriteFrameByName("monster_hwalk_frame8");
	const auto hwalk_frame9 = spriteCache->getSpriteFrameByName("monster_hwalk_frame9");
	const auto hwalk_frame10 = spriteCache->getSpriteFrameByName("monster_hwalk_frame10");
	const auto hwalk_frame11 = spriteCache->getSpriteFrameByName("monster_hwalk_frame11");
	Vector<SpriteFrame*> hwalkFrames;
	hwalkFrames.pushBack(hwalk_frame0);
	hwalkFrames.pushBack(hwalk_frame1);
	hwalkFrames.pushBack(hwalk_frame2);
	hwalkFrames.pushBack(hwalk_frame3);
	hwalkFrames.pushBack(hwalk_frame4);
	hwalkFrames.pushBack(hwalk_frame5);
	hwalkFrames.pushBack(hwalk_frame6);
	hwalkFrames.pushBack(hwalk_frame7);
	hwalkFrames.pushBack(hwalk_frame8);
	hwalkFrames.pushBack(hwalk_frame9);
	hwalkFrames.pushBack(hwalk_frame10);
	hwalkFrames.pushBack(hwalk_frame11);
	Animation * hwalk_animation = Animation::createWithSpriteFrames(hwalkFrames, 0.1f);
	hwalk_animation->setLoops(-1);
	hwalk_animation->setRestoreOriginalFrame(true);
	aniCache->addAnimation(hwalk_animation, "monster_hwalk_animation");
    
    const auto dead_frame0 = spriteCache->getSpriteFrameByName("dead_frame0");
    const auto dead_frame1 = spriteCache->getSpriteFrameByName("dead_frame1");
    const auto dead_frame2 = spriteCache->getSpriteFrameByName("dead_frame2");
    const auto dead_frame3 = spriteCache->getSpriteFrameByName("dead_frame3");
    const auto dead_frame4 = spriteCache->getSpriteFrameByName("dead_frame4");
    const auto dead_frame5 = spriteCache->getSpriteFrameByName("dead_frame5");
    const auto dead_frame6 = spriteCache->getSpriteFrameByName("dead_frame6");
    const auto dead_frame7 = spriteCache->getSpriteFrameByName("dead_frame7");
    const auto dead_frame8 = spriteCache->getSpriteFrameByName("dead_frame8");
    const auto dead_frame9 = spriteCache->getSpriteFrameByName("dead_frame9");
    Vector<SpriteFrame*> deadFrames;
    deadFrames.pushBack(dead_frame0);
    deadFrames.pushBack(dead_frame1);
    deadFrames.pushBack(dead_frame2);
    deadFrames.pushBack(dead_frame3);
    deadFrames.pushBack(dead_frame4);
    deadFrames.pushBack(dead_frame5);
    deadFrames.pushBack(dead_frame6);
    deadFrames.pushBack(dead_frame7);
    deadFrames.pushBack(dead_frame8);
    deadFrames.pushBack(dead_frame9);
    Animation * dead_animation = Animation::createWithSpriteFrames(deadFrames,0.1f);
    dead_animation->setLoops(0);
    aniCache->addAnimation(dead_animation, "dead_animation");
}


void Monster::move(int walk_direction)
{
	//移动
	//移动速度不是之前的情况，说明发生碰撞
	if (colClog == ColClogTime
		&& this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation)) {
		colClog = 0;
	}
	else {
		this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
	}

	//移动的图形显示
	//直接获取缓存，不要将SpriteFrame保存在类中
	auto aniCache = AnimationCache::getInstance();

	const auto vwalk_animation = aniCache->getAnimation("monster_vwalk_animation");
	const auto hwalk_animation = aniCache->getAnimation("monster_hwalk_animation");
	const auto head_animation = aniCache->getAnimation("head_animation");

	Animate * vwalk_animate = Animate::create(vwalk_animation);
	Animate * hwalk_animate = Animate::create(hwalk_animation);
	Animate * head_animate = Animate::create(head_animation);

	switch (walk_direction)
	{
		//123
		//456
		//789
	case 4://左
		if (prev_walk_orientation != 4) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->setScaleX(-1);//翻转
			this->getChildByName("body")->runAction(hwalk_animate);
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 4;
		break;

	case 6://右
		if (prev_walk_orientation != 6) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->setScaleX(1);//翻转
			this->getChildByName("body")->runAction(hwalk_animate);
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 6;
		break;

	case 2://上
		if (prev_walk_orientation != 2) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->runAction(vwalk_animate->reverse());//向上走要倒放
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 2;
		break;

	case 8://下
		if (prev_walk_orientation != 8) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->runAction(vwalk_animate);
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 8;
		break;

	case 1://左上
		if (prev_walk_orientation != 1) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->runAction(vwalk_animate->reverse());
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 1;
		break;

	case 3://右上
		if (prev_walk_orientation != 3) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->runAction(vwalk_animate->reverse());
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 3;
		break;

	case 7://左下
		if (prev_walk_orientation != 7) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->runAction(vwalk_animate);
			this->getChildByName("head")->runAction(head_animate);
		}
		prev_walk_orientation = 7;
		break;

	case 9://右下
		if (prev_walk_orientation != 9) {
			this->getChildByName("body")->stopAllActions();
			this->getChildByName("body")->runAction(vwalk_animate);
		}
		prev_walk_orientation = 9;
		break;

	case 5://无，头要默认复位
		this->getChildByName("body")->stopAllActions();
		prev_walk_orientation = 5;
		break;

	default:
		break;
	}

	if (colClog == 0) {
		prev_walk_orientation = 5;
	}
}

int Monster::ToPointDir(Vec2 PlayerPos)
{
	double diff_x = PlayerPos.x - getPositionX();
	double diff_y = PlayerPos.y - getPositionY();
	//将坐标差标准化
	double max_xy = max(abs(diff_x), abs(diff_y));
	diff_x /= max_xy;
	diff_y /= max_xy;
	if (diff_x == 1) {
		if (diff_y < -0.3) return 9;
		if (abs(diff_y) < 0.3)	return 6;
		if (diff_y > 0.3) return 3;
	}
	if (diff_x == -1) {
		if (diff_y < -0.3) return 7;
		if (abs(diff_y) < 0.3)	return 4;
		if (diff_y > 0.3) return 1;
	}
	if (diff_y == 1) {
		if (diff_x < -0.3) return 1;
		if (abs(diff_x) < 0.3)	return 2;
		if (diff_x > 0.3) return 3;
	}
	if (diff_y == -1) {
		if (diff_x < -0.3) return 7;
		if (abs(diff_x) < 0.3)	return 8;
		if (diff_x > 0.3) return 9;
	}
	return 5;
}

void Monster::createPhyBody()
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
	//碰撞筛选:所有都碰撞，选择性监听:和tear，issac，monster碰撞监听，石头不监听
	phyBody->setCategoryBitmask(0x02);    // 0000_0010
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111
	phyBody->setContactTestBitmask(0x07);	//0000_0111
	//添加物理躯体
	this->addComponent(phyBody);
}


Fatty *Fatty::createFatty()
{
	return create();
}

bool Fatty::init() {
	if (!Monster::init())
	{
		return false;
	}

	
	radiusSize = 12;	//Fatty碰撞大小	
	bodyMass = 500;		//Fatty重量
	moveSpeed = 80;		//Fatty行走速度
	health = 5;			//Fatty血量
	attack = 1;			//Fatty攻击
	tearSpeed = 60;		//Fatty泪速
	tearExistTime = 80; //Fatty射程

	this->createPhyBody();
	return true;
}

////傻子移动
//void Fatty::moveStrategy(const RoomViewModel& roomMap) {
//	Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
//	int walk_direction = ToPointDir(playerPos);
//	this->move(walk_direction);
//}


//脑子移动
void Fatty::moveStrategy(const RoomViewModel& roomMap) {
	Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
	if (CalDistance(playerPos, this->getPosition()) < RoomUnitSize.height*1.2) {
		//足够近，直接冲过去
		this->move(ToPointDir(playerPos));
	}
	else {
		//BFS找到最短路径
		GridPoint roomFlag[GRID_WIDTH][GRID_HEIGHT];
		vector<GridPoint> quary;
		int head=0;
		GridPoint destination = CalGridPos(playerPos),startPos= CalGridPos(this->getPosition());
		quary.push_back(startPos);
		roomFlag[startPos.x][startPos.y] = GridPoint(99, 99);
		while (head < quary.size()) {
			for (int i = 0; i < 4; i++) {
				GridPoint tempPos = GridPoint(quary[head].x + moveStep[i].x, quary[head].y + moveStep[i].y);	
				if (tempPos.inRoom() && roomFlag[tempPos.x][tempPos.y].x == -1
					&& roomMap.getRoomMap(tempPos.x, tempPos.y) != 1
					&& roomMap.getRoomMap(tempPos.x, tempPos.y) != 2) {
					roomFlag[tempPos.x][tempPos.y] = quary[head];
					quary.push_back(tempPos);
					if (tempPos == destination)
						goto mark;
				}
			}
			head++;
		}
	mark:
		GridPoint des1 = destination;
		while (!(roomFlag[destination.x][destination.y] == startPos)) {
			destination = roomFlag[destination.x][destination.y];
		}
		this->move(ToPointDir(Vec2(RoomUnitSize.width*destination.x+61, RoomUnitSize.height*destination.y + 61)));
	}
}
void Fatty::fireStrategy(Vector<Tear*>& tears_)
{
	if (fireCoolTime > 0) {
		fireCoolTime--; //冷却不开火
	}
	else {
		//冷却
		fireCoolTime = 20;
		//向人物方向发射子弹
		tears_.pushBack(Fire(this->getParent()->getChildByTag(1)->getPosition()));
	}
}