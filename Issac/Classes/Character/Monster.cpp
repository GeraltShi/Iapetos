#include "Monster.hpp"
#include "cocos2d.h"

using namespace cocos2d;



bool Monster::init()
{
    if (!Moveable::init())
    {
        return false;
    }

    moving = false;
    fireCoolTime = 3;
	colClog = 30;

    //tag=2是怪物
    this->setTag(2);

    const auto common_dead_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/effects/effect_002_bloodpoof.png");
    build_sprite_frame_cache(common_dead_texture_);
    build_animation_cache();

    return true;
}

Tear *Monster::Fire(Vec2 targetPos)
{
    //创建一个Tear
    Tear *myTear = Tear::createTear();
	Vec2 myasd = this->getPosition();
	
    //设定初始tear位置和速度
    double diffX = targetPos.x - this->getPosition().x;
    double diffY = targetPos.y - this->getPosition().y;
    double dis = sqrt(diffX * diffX + diffY * diffY);
    double tear_V = moveSpeed + tearSpeed;
    myTear->getPhysicsBody()->setVelocity(Vec2(tear_V * diffX / dis, tear_V * diffY / dis));
	//初始位置
    myTear->setPosition(Vec2(getPosition().x + MonTearOffset * diffX / dis, getPosition().y + MonTearOffset * diffY / dis));
    //存在时间,攻击
    myTear->setTearExistTime(tearExistTime);
    myTear->setAttack(attack);
    //是Monster发射的
    myTear->setTag(3);
    return myTear;
}

string Monster::getDeadAnimation()
{
    return "monster_dead_animation";
}

void Monster::build_sprite_frame_cache(Texture2D *dead_texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 0, 64 * 0, 64, 64)), "dead_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 1, 64 * 0, 64, 64)), "dead_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 2, 64 * 0, 64, 64)), "dead_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 3, 64 * 0, 64, 64)), "dead_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 0, 64 * 1, 64, 64)), "dead_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 1, 64 * 1, 64, 64)), "dead_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 2, 64 * 1, 64, 64)), "dead_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 3, 64 * 1, 64, 64)), "dead_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 0, 64 * 2, 64, 64)), "dead_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(dead_texture_, Rect(64 * 1, 64 * 2, 64, 64)), "dead_frame9");
}

void Monster::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

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
    Vector<SpriteFrame *> deadFrames;
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
    Animation *dead_animation = Animation::createWithSpriteFrames(deadFrames, 0.1f);
    dead_animation->setLoops(1);
    aniCache->addAnimation(dead_animation, "monster_dead_animation");
}

int Monster::ToPointDir(Vec2 PlayerPos)
{
    double diff_x = PlayerPos.x - getPositionX();
    double diff_y = PlayerPos.y - getPositionY();
    //将坐标差标准化
    double max_xy = max(abs(diff_x), abs(diff_y));
    diff_x /= max_xy;
    diff_y /= max_xy;
    if (diff_x == 1)
    {
        if (diff_y < -0.3)
            return 9;
        if (abs(diff_y) < 0.3)
            return 6;
        if (diff_y > 0.3)
            return 3;
    }
    if (diff_x == -1)
    {
        if (diff_y < -0.3)
            return 7;
        if (abs(diff_y) < 0.3)
            return 4;
        if (diff_y > 0.3)
            return 1;
    }
    if (diff_y == 1)
    {
        if (diff_x < -0.3)
            return 1;
        if (abs(diff_x) < 0.3)
            return 2;
        if (diff_x > 0.3)
            return 3;
    }
    if (diff_y == -1)
    {
        if (diff_x < -0.3)
            return 7;
        if (abs(diff_x) < 0.3)
            return 8;
        if (diff_x > 0.3)
            return 9;
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
    //碰撞\监听筛选
    phyBody->setCategoryBitmask(0x02);    // 0000_0010
    phyBody->setCollisionBitmask(0xFF);   // 1111_1111
    phyBody->setContactTestBitmask(0x09); //0000_1001(09)
    //添加物理躯体
    this->addComponent(phyBody);
}

//---------------------------------------------------------Fatty---------------------------------------------------------

void Fatty::move(int walk_direction)
{
    //移动
    //移动速度不是之前的情况，说明发生碰撞
    if (colClog == ColClogTime && walk_direction != 5
		&& this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation))
    {
        colClog = 0;
    }
    else
    {
        this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
    }

    //移动的图形显示
    //直接获取缓存，不要将SpriteFrame保存在类中
    auto aniCache = AnimationCache::getInstance();

    const auto vwalk_animation = aniCache->getAnimation("monster_vwalk_animation");
    const auto hwalk_animation = aniCache->getAnimation("monster_hwalk_animation");
    const auto head_animation = aniCache->getAnimation("head_animation");

    Animate *vwalk_animate = Animate::create(vwalk_animation);
    Animate *hwalk_animate = Animate::create(hwalk_animation);
    Animate *head_animate = Animate::create(head_animation);

    switch (walk_direction)
    {
        //123
        //456
        //789
    case 4: //左
        if (prev_walk_orientation != 4)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->setScaleX(-1); //翻转
            this->getChildByName("body")->runAction(hwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 4;
        break;

    case 6: //右
        if (prev_walk_orientation != 6)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->setScaleX(1); //翻转
            this->getChildByName("body")->runAction(hwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 6;
        break;

    case 2: //上
        if (prev_walk_orientation != 2)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate->reverse()); //向上走要倒放
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 2;
        break;

    case 8: //下
        if (prev_walk_orientation != 8)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 8;
        break;

    case 1: //左上
        if (prev_walk_orientation != 1)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate->reverse());
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 1;
        break;

    case 3: //右上
        if (prev_walk_orientation != 3)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate->reverse());
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 3;
        break;

    case 7: //左下
        if (prev_walk_orientation != 7)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 7;
        break;

    case 9: //右下
        if (prev_walk_orientation != 9)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate);
        }
        prev_walk_orientation = 9;
        break;

    case 5: //无，头要默认复位
        this->getChildByName("body")->stopAllActions();
        prev_walk_orientation = 5;
        break;

    default:
        break;
    }

    if (colClog == 0)
    {
        prev_walk_orientation = 5;
    }
}

void Fatty::build_sprite_frame_cache(Texture2D *texture_) const
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
}

void Fatty::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto head_frame0 = spriteCache->getSpriteFrameByName("head_frame0");
    const auto head_frame1 = spriteCache->getSpriteFrameByName("head_frame1");
    const auto head_frame2 = spriteCache->getSpriteFrameByName("head_frame2");
    const auto head_frame3 = spriteCache->getSpriteFrameByName("head_frame3");
    const auto head_frame4 = spriteCache->getSpriteFrameByName("head_frame4");
    const auto head_frame5 = spriteCache->getSpriteFrameByName("head_frame5");
    Vector<SpriteFrame *> headFrames;
    headFrames.pushBack(head_frame0);
    headFrames.pushBack(head_frame1);
    headFrames.pushBack(head_frame2);
    headFrames.pushBack(head_frame3);
    headFrames.pushBack(head_frame4);
    headFrames.pushBack(head_frame5);
    Animation *head_animation = Animation::createWithSpriteFrames(headFrames, 0.1f);
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
    Vector<SpriteFrame *> vwalkFrames;
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
    Animation *vwalk_animation = Animation::createWithSpriteFrames(vwalkFrames, 0.1f);
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
    Vector<SpriteFrame *> hwalkFrames;
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
    Animation *hwalk_animation = Animation::createWithSpriteFrames(hwalkFrames, 0.1f);
    hwalk_animation->setLoops(-1);
    hwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(hwalk_animation, "monster_hwalk_animation");
}

Fatty *Fatty::createFatty()
{
    return create();
}

bool Fatty::init()
{
    if (!Monster::init())
    {
        return false;
    }

    radiusSize = 12;    //Fatty碰撞大小
    bodyMass = 500;     //Fatty重量
    moveSpeed = 80;     //Fatty行走速度
    health = 5;         //Fatty血量
    attack = 1;         //Fatty攻击
    tearSpeed = 60;     //Fatty泪速
	tearExistTime = 0;	//Fatty射程

    //不要将Texture保存在类,用的时候直接从TextureCache中获取
    const auto fatty_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/rebirth/monster_207_fatty.png");
    SpriteFrame *headFrame = SpriteFrame::createWithTexture(fatty_texture_, Rect(0, 0, 32, 32));
    Sprite *headSprite = createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(fatty_texture_, Rect(192, 224, 64, 64));
    Sprite *bodySprite = createWithSpriteFrame(bodyFrame);

    build_sprite_frame_cache(fatty_texture_);
    build_animation_cache();

    this->addChild(headSprite, 1, "head");
    this->addChild(bodySprite, 0, "body");
    headSprite->setPosition(Vec2(0, 10));
    this->setPosition(Vec2(221, 143));

    this->createPhyBody();
    return true;
}

void Fatty::moveStrategy(const RoomViewModel &roomMap)
{
	//追踪人的移动策略
    Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
    if (CalDistance(playerPos, this->getPosition()) < RoomUnitSize.height * 1.2)
    {
        //足够近，直接冲过去
        this->move(ToPointDir(playerPos));
    }
    else
    {
        //BFS找到最短路径
        GridPoint roomFlag[GRID_WIDTH][GRID_HEIGHT];
        vector<GridPoint> quary;
        int head = 0;
        GridPoint destination = CalGridPos(playerPos), startPos = CalGridPos(this->getPosition());
        quary.push_back(startPos);
        roomFlag[startPos.x][startPos.y] = GridPoint(99, 99);
        while (head < quary.size())
        {
            for (int i = 0; i < 4; i++)
            {
                GridPoint tempPos = GridPoint(quary[head].x + moveStep[i].x, quary[head].y + moveStep[i].y);
                if (tempPos.inRoom() && roomFlag[tempPos.x][tempPos.y].x == -1 && roomMap.getRoomMap(tempPos.x, tempPos.y) != 1 && roomMap.getRoomMap(tempPos.x, tempPos.y) != 2)
                {
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
        while (!(roomFlag[destination.x][destination.y] == startPos))
        {
            destination = roomFlag[destination.x][destination.y];
        }
        this->move(ToPointDir(Vec2(RoomUnitSize.width * destination.x + 61, RoomUnitSize.height * destination.y + 61)));
    }
}

//---------------------------------------------------------FattyFire----------------------------------------------------------
void FattyFire::moveStrategy(const RoomViewModel& roomMap) {
	//随机移动
	colClog = 5;
	this->move(rand() % 9 + 1);
}

//十字开火
void FattyFire::fireStrategy(Vector<Tear *> &tears_)
{
    //向4个方向（上下左右）射击的开火策略
    if (fireCoolTime > 0)
    {
        fireCoolTime--; //冷却不开火
    }
    else
    {
        //冷却
        fireCoolTime = fireSpeed;
        //向4个方向（上下左右）射击的开火策略
        tears_.pushBack(Fire(Vec2(this->getPosition().x - 10, this->getPosition().y)));
        tears_.pushBack(Fire(Vec2(this->getPosition().x + 10, this->getPosition().y)));
        tears_.pushBack(Fire(Vec2(this->getPosition().x, this->getPosition().y - 10)));
        tears_.pushBack(Fire(Vec2(this->getPosition().x, this->getPosition().y + 10)));
    }
}

//----------------------------------------------------------Fly----------------------------------------------------------

string Fly::getDeadAnimation()
{
    return "fly_dead_animation";
}

void Fly::build_sprite_frame_cache(Texture2D *texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32, 32, 32)), "fly_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32, 32, 32)), "fly_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 2, 32, 32, 32)), "fly_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 3, 32, 32, 32)), "fly_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 4, 32, 32, 32)), "fly_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 5, 32, 32, 32)), "fly_frame5");

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 64, 64, 64)), "fly_dead_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 64, 64, 64)), "fly_dead_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 64, 64, 64)), "fly_dead_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 64, 64, 64)), "fly_dead_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 128, 64, 64)), "fly_dead_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 128, 64, 64)), "fly_dead_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 128, 64, 64)), "fly_dead_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 128, 64, 64)), "fly_dead_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 0, 192, 64, 64)), "fly_dead_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 192, 64, 64)), "fly_dead_frame9");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 192, 64, 64)), "fly_dead_frame10");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 192, 64, 64)), "fly_dead_frame11");
}

void Fly::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto fly_frame0 = spriteCache->getSpriteFrameByName("fly_frame0");
    const auto fly_frame1 = spriteCache->getSpriteFrameByName("fly_frame1");
    const auto fly_frame2 = spriteCache->getSpriteFrameByName("fly_frame2");
    const auto fly_frame3 = spriteCache->getSpriteFrameByName("fly_frame3");
    const auto fly_frame4 = spriteCache->getSpriteFrameByName("fly_frame4");
    const auto fly_frame5 = spriteCache->getSpriteFrameByName("fly_frame5");
    Vector<SpriteFrame *> flyFrames;
    flyFrames.pushBack(fly_frame0);
    flyFrames.pushBack(fly_frame1);
    flyFrames.pushBack(fly_frame2);
    flyFrames.pushBack(fly_frame3);
    flyFrames.pushBack(fly_frame4);
    flyFrames.pushBack(fly_frame5);
    Animation *fly_animation = Animation::createWithSpriteFrames(flyFrames, 0.1f);
    fly_animation->setLoops(-1);
    fly_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(fly_animation, "fly_animation");

    const auto dead_frame0 = spriteCache->getSpriteFrameByName("fly_dead_frame0");
    const auto dead_frame1 = spriteCache->getSpriteFrameByName("fly_dead_frame1");
    const auto dead_frame2 = spriteCache->getSpriteFrameByName("fly_dead_frame2");
    const auto dead_frame3 = spriteCache->getSpriteFrameByName("fly_dead_frame3");
    const auto dead_frame4 = spriteCache->getSpriteFrameByName("fly_dead_frame4");
    const auto dead_frame5 = spriteCache->getSpriteFrameByName("fly_dead_frame5");
    const auto dead_frame6 = spriteCache->getSpriteFrameByName("fly_dead_frame6");
    const auto dead_frame7 = spriteCache->getSpriteFrameByName("fly_dead_frame7");
    const auto dead_frame8 = spriteCache->getSpriteFrameByName("fly_dead_frame8");
    const auto dead_frame9 = spriteCache->getSpriteFrameByName("fly_dead_frame9");
    const auto dead_frame10 = spriteCache->getSpriteFrameByName("fly_dead_frame10");
    const auto dead_frame11 = spriteCache->getSpriteFrameByName("fly_dead_frame11");
    Vector<SpriteFrame *> deadFrames;
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
    deadFrames.pushBack(dead_frame10);
    deadFrames.pushBack(dead_frame11);
    Animation *dead_animation = Animation::createWithSpriteFrames(deadFrames, 0.1f);
    dead_animation->setLoops(1);
    aniCache->addAnimation(dead_animation, "fly_dead_animation");
}

Fly *Fly::createFly()
{
    return create();
}

void Fly::move(int walk_direction)
{
    //移动
    //移动速度不是之前的情况，说明发生碰撞
    if (colClog == 0 && walk_direction!=5 
		&& this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation))
    {
        colClog = ColClogTime;
    }
    else
    {
        this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
    }

    if (!moving)
    {
        //移动的图形显示
        //直接获取缓存，不要将SpriteFrame保存在类中
        auto aniCache = AnimationCache::getInstance();
        const auto fly_animation = aniCache->getAnimation("fly_animation");
        Animate *fly_animate = Animate::create(fly_animation);
        this->getChildByName("body")->runAction(fly_animate);

        moving = true;
    }

    if (colClog == ColClogTime)
    {
        prev_walk_orientation = 5;
    }
}

bool Fly::init()
{
    if (!Monster::init())
    {
        return false;
    }
    const auto fly_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/classic/monster_010_fly.png");
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(fly_texture_, Rect(0, 0, 32, 32));
    Sprite *bodySprite = createWithSpriteFrame(bodyFrame);

    build_sprite_frame_cache(fly_texture_);
    build_animation_cache();

    this->addChild(bodySprite, 0, "body");
	radiusSize = 6;    //Fly碰撞大小
	bodyMass = 5;     //Fly重量
	moveSpeed = 50;     //Fly行走速度
	health = 3;         //Fly血量
	attack = 1;         //Fly攻击
	tearSpeed = 60;     //Fly泪速
	tearExistTime = 0; //Fly射程

    this->createPhyBody();
	this->getPhysicsBody()->setCategoryBitmask(0x04);	// 0000_0100(04)
	this->getPhysicsBody()->setCollisionBitmask(0xDF);	// 1101_1111(DF)
	this->getPhysicsBody()->setContactTestBitmask(0x09);//0000_1001(09)
    return true;
}

void Fly::moveStrategy(const RoomViewModel & roomMap)
{
    Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
    this->move(this->ToPointDir(playerPos));
}

//--------------------------------------------------------FlyFire----------------------------------------------------------

void FlyFire::fireStrategy(Vector<Tear*>& tears_)
{
	//向player位置射击的开火策略
	if (fireCoolTime > 0) {
		fireCoolTime--; //冷却不开火
	}
	else {
		//冷却
		fireCoolTime = fireSpeed;
		//向人物方向发射子弹
		tears_.pushBack(Fire(this->getParent()->getChildByTag(1)->getPosition()));
	}
}

//---------------------------------------------------------Gaper----------------------------------------------------------

void Gaper::build_sprite_frame_cache(Texture2D *head_texture_, Texture2D *body_texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(head_texture_, Rect(0, 0, 32, 32)), "gaper_head_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(head_texture_, Rect(32, 0, 32, 32)), "gaper_head_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(head_texture_, Rect(0, 32, 32, 32)), "gaper_head_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(head_texture_, Rect(32, 32, 32, 32)), "gaper_head_frame3");

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 0, 32, 32, 32)), "gaper_hwalk_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 1, 32, 32, 32)), "gaper_hwalk_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 2, 32, 32, 32)), "gaper_hwalk_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 3, 32, 32, 32)), "gaper_hwalk_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 0, 64, 32, 32)), "gaper_hwalk_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 1, 64, 32, 32)), "gaper_hwalk_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 2, 64, 32, 32)), "gaper_hwalk_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 3, 64, 32, 32)), "gaper_hwalk_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 0, 96, 32, 32)), "gaper_hwalk_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 1, 96, 32, 32)), "gaper_hwalk_frame9");

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 2, 96, 32, 32)), "gaper_vwalk_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 3, 96, 32, 32)), "gaper_vwalk_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 0, 128, 32, 32)), "gaper_vwalk_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 1, 128, 32, 32)), "gaper_vwalk_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 2, 128, 32, 32)), "gaper_vwalk_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 3, 128, 32, 32)), "gaper_vwalk_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 0, 160, 32, 32)), "gaper_vwalk_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 1, 160, 32, 32)), "gaper_vwalk_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 2, 160, 32, 32)), "gaper_vwalk_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(body_texture_, Rect(32 * 3, 160, 32, 32)), "gaper_vwalk_frame9");
}

void Gaper::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto gaper_head_frame0 = spriteCache->getSpriteFrameByName("gaper_head_frame0");
    const auto gaper_head_frame1 = spriteCache->getSpriteFrameByName("gaper_head_frame1");
    const auto gaper_head_frame2 = spriteCache->getSpriteFrameByName("gaper_head_frame2");
    const auto gaper_head_frame3 = spriteCache->getSpriteFrameByName("gaper_head_frame3");

    Vector<SpriteFrame *> gaperheadFrames;
    gaperheadFrames.pushBack(gaper_head_frame0);
    gaperheadFrames.pushBack(gaper_head_frame1);
    gaperheadFrames.pushBack(gaper_head_frame2);
    gaperheadFrames.pushBack(gaper_head_frame3);
    Animation *gaper_head_animation = Animation::createWithSpriteFrames(gaperheadFrames, 3.0f);
    gaper_head_animation->setLoops(-1);
    gaper_head_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(gaper_head_animation, "gaper_head_animation");

    const auto vwalk_frame0 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame0");
    const auto vwalk_frame1 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame1");
    const auto vwalk_frame2 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame2");
    const auto vwalk_frame3 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame3");
    const auto vwalk_frame4 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame4");
    const auto vwalk_frame5 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame5");
    const auto vwalk_frame6 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame6");
    const auto vwalk_frame7 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame7");
    const auto vwalk_frame8 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame8");
    const auto vwalk_frame9 = spriteCache->getSpriteFrameByName("gaper_vwalk_frame9");
    Vector<SpriteFrame *> vwalkFrames;
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
    Animation *vwalk_animation = Animation::createWithSpriteFrames(vwalkFrames, 0.1f);
    vwalk_animation->setLoops(-1);
    vwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(vwalk_animation, "gaper_vwalk_animation");

    const auto hwalk_frame0 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame0");
    const auto hwalk_frame1 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame1");
    const auto hwalk_frame2 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame2");
    const auto hwalk_frame3 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame3");
    const auto hwalk_frame4 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame4");
    const auto hwalk_frame5 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame5");
    const auto hwalk_frame6 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame6");
    const auto hwalk_frame7 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame7");
    const auto hwalk_frame8 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame8");
    const auto hwalk_frame9 = spriteCache->getSpriteFrameByName("gaper_hwalk_frame9");
    Vector<SpriteFrame *> hwalkFrames;
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
    Animation *hwalk_animation = Animation::createWithSpriteFrames(hwalkFrames, 0.1f);
    hwalk_animation->setLoops(-1);
    hwalk_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(hwalk_animation, "gaper_hwalk_animation");
}

Gaper *Gaper::createGaper()
{
    return create();
}

void Gaper::move(int walk_direction)
{
    //移动
    //移动速度不是之前的情况，说明发生碰撞
    if (colClog == ColClogTime && walk_direction != 5
		&& this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation))
    {
        colClog = 0;
    }
    else
    {
        this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
    }

    //移动的图形显示
    //直接获取缓存，不要将SpriteFrame保存在类中
    auto aniCache = AnimationCache::getInstance();

    const auto vwalk_animation = aniCache->getAnimation("gaper_vwalk_animation");
    const auto hwalk_animation = aniCache->getAnimation("gaper_hwalk_animation");
    const auto head_animation = aniCache->getAnimation("gaper_head_animation");

    Animate *vwalk_animate = Animate::create(vwalk_animation);
    Animate *hwalk_animate = Animate::create(hwalk_animation);
    Animate *head_animate = Animate::create(head_animation);

    switch (walk_direction)
    {
        //123
        //456
        //789
    case 4: //左
        if (prev_walk_orientation != 4)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->setScaleX(-1); //翻转
            this->getChildByName("body")->runAction(hwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 4;
        break;

    case 6: //右
        if (prev_walk_orientation != 6)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->setScaleX(1); //翻转
            this->getChildByName("body")->runAction(hwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 6;
        break;

    case 2: //上
        if (prev_walk_orientation != 2)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate->reverse()); //向上走要倒放
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 2;
        break;

    case 8: //下
        if (prev_walk_orientation != 8)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 8;
        break;

    case 1: //左上
        if (prev_walk_orientation != 1)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate->reverse());
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 1;
        break;

    case 3: //右上
        if (prev_walk_orientation != 3)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate->reverse());
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 3;
        break;

    case 7: //左下
        if (prev_walk_orientation != 7)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate);
            this->getChildByName("head")->runAction(head_animate);
        }
        prev_walk_orientation = 7;
        break;

    case 9: //右下
        if (prev_walk_orientation != 9)
        {
            this->getChildByName("body")->stopAllActions();
            this->getChildByName("body")->runAction(vwalk_animate);
        }
        prev_walk_orientation = 9;
        break;

    case 5: //无，头要默认复位
        this->getChildByName("body")->stopAllActions();
        prev_walk_orientation = 5;
        break;

    default:
        break;
    }

    if (colClog == 0)
    {
        prev_walk_orientation = 5;
    }
}

bool Gaper::init()
{
    if (!Monster::init())
    {
        return false;
    }
    //不要将Texture保存在类,用的时候直接从TextureCache中获取
    const auto gaper_head_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/classic/monster_017_gaper.png");
    const auto gaper_body_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/classic/monster_000_bodies01.png");
    SpriteFrame *headFrame = SpriteFrame::createWithTexture(gaper_head_texture_, Rect(0, 0, 32, 32));
    Sprite *headSprite = createWithSpriteFrame(headFrame);
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(gaper_body_texture_, Rect(0, 0, 32, 32));
    Sprite *bodySprite = createWithSpriteFrame(bodyFrame);

    build_sprite_frame_cache(gaper_head_texture_, gaper_body_texture_);
    build_animation_cache();

    this->addChild(headSprite, 1, "head");
    this->addChild(bodySprite, 0, "body");
    headSprite->setPosition(Vec2(0, 10));
    this->setPosition(Vec2(221, 143));

	radiusSize = 9;    //Gaper碰撞大小
	bodyMass = 100;     //Gaper重量
	moveSpeed = 30;     //Gaper行走速度
	health = 5;         //Gaper血量
	attack = 1;         //Gaper攻击
	tearSpeed = 60;     //Gaper泪速
	tearExistTime = 80; //Fly射程
    this->createPhyBody();
    return true;
}

void Gaper::moveStrategy(const RoomViewModel & roomMap)
{
	//追踪人的移动策略
	Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
	if (CalDistance(playerPos, this->getPosition()) < RoomUnitSize.height * 4) {
		//足够近 冲刺
		moveSpeed = 100;
	}
	else {
		moveSpeed = 30;
	}
	if (CalDistance(playerPos, this->getPosition()) < RoomUnitSize.height * 1.2)
	{
	    //足够近，直接冲过去
	    this->move(ToPointDir(playerPos));
	}
	else
	{
	    //BFS找到最短路径
	    GridPoint roomFlag[GRID_WIDTH][GRID_HEIGHT];
	    vector<GridPoint> quary;
	    int head = 0;
	    GridPoint destination = CalGridPos(playerPos), startPos = CalGridPos(this->getPosition());
	    quary.push_back(startPos);
	    roomFlag[startPos.x][startPos.y] = GridPoint(99, 99);
	    while (head < quary.size())
	    {
	        for (int i = 0; i < 4; i++)
	        {
	            GridPoint tempPos = GridPoint(quary[head].x + moveStep[i].x, quary[head].y + moveStep[i].y);
	            if (tempPos.inRoom() && roomFlag[tempPos.x][tempPos.y].x == -1 && roomMap.getRoomMap(tempPos.x, tempPos.y) != 1 && roomMap.getRoomMap(tempPos.x, tempPos.y) != 2)
	            {
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
	    while (!(roomFlag[destination.x][destination.y] == startPos))
	    {
	        destination = roomFlag[destination.x][destination.y];
	    }
	    this->move(ToPointDir(Vec2(RoomUnitSize.width * destination.x + 61, RoomUnitSize.height * destination.y + 61)));
	}
}

//------------------------------------------------------GaperFire----------------------------------------------------------
void GaperFire::fireStrategy(Vector<Tear *> &tears_)
{
	//X字开火
    if (fireCoolTime > 0)
    {
        fireCoolTime--; //冷却不开火
    }
    else
    {
        fireCoolTime = fireSpeed; //冷却
		//开火
		double fireOffsetX=this->getPhysicsBody()->getVelocity().x /moveSpeed;
		double fireOffsetY=this->getPhysicsBody()->getVelocity().y /moveSpeed;

		tears_.pushBack(Fire(Vec2(this->getPosition().x - 10 , this->getPosition().y-10 )));
		tears_.pushBack(Fire(Vec2(this->getPosition().x + 10 , this->getPosition().y+10 )));
		tears_.pushBack(Fire(Vec2(this->getPosition().x + 10 , this->getPosition().y - 10 )));
		tears_.pushBack(Fire(Vec2(this->getPosition().x - 10 , this->getPosition().y + 10 )));
    }
}

//---------------------------------------------------------Spider---------------------------------------------------------

string Spider::getDeadAnimation()
{
    return "spider_dead_animation";
}

void Spider::build_sprite_frame_cache(Texture2D *texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 0, 32, 16)), "spider_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 0, 32, 16)), "spider_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 16, 32, 16)), "spider_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 16, 32, 16)), "spider_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 32, 32, 16)), "spider_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 32, 32, 16)), "spider_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 0, 64, 32, 16)), "spider_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(32 * 1, 64, 32, 16)), "spider_frame7");

    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 0, 64, 64)), "spider_dead_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 0, 64, 64)), "spider_dead_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 0, 64, 64)), "spider_dead_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 0, 64, 64)), "spider_dead_frame3");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 64, 64, 64)), "spider_dead_frame4");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 64, 64, 64)), "spider_dead_frame5");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 64, 64, 64)), "spider_dead_frame6");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 64, 64, 64)), "spider_dead_frame7");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 1, 128, 64, 64)), "spider_dead_frame8");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 2, 128, 64, 64)), "spider_dead_frame9");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 3, 128, 64, 64)), "spider_dead_frame10");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(64 * 4, 128, 64, 64)), "spider_dead_frame11");
}

void Spider::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();

    const auto spider_frame0 = spriteCache->getSpriteFrameByName("spider_frame0");
    const auto spider_frame1 = spriteCache->getSpriteFrameByName("spider_frame1");
    const auto spider_frame2 = spriteCache->getSpriteFrameByName("spider_frame2");
    const auto spider_frame3 = spriteCache->getSpriteFrameByName("spider_frame3");
    const auto spider_frame4 = spriteCache->getSpriteFrameByName("spider_frame4");
    const auto spider_frame5 = spriteCache->getSpriteFrameByName("spider_frame5");
    const auto spider_frame6 = spriteCache->getSpriteFrameByName("spider_frame6");
    const auto spider_frame7 = spriteCache->getSpriteFrameByName("spider_frame7");
    Vector<SpriteFrame *> spiderFrames;
    spiderFrames.pushBack(spider_frame0);
    spiderFrames.pushBack(spider_frame1);
    spiderFrames.pushBack(spider_frame2);
    spiderFrames.pushBack(spider_frame3);
    spiderFrames.pushBack(spider_frame4);
    spiderFrames.pushBack(spider_frame5);
    spiderFrames.pushBack(spider_frame6);
    spiderFrames.pushBack(spider_frame7);
    Animation *spider_animation = Animation::createWithSpriteFrames(spiderFrames, 0.1f);
    spider_animation->setLoops(-1);
    spider_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(spider_animation, "spider_animation");

    const auto dead_frame0 = spriteCache->getSpriteFrameByName("spider_dead_frame0");
    const auto dead_frame1 = spriteCache->getSpriteFrameByName("spider_dead_frame1");
    const auto dead_frame2 = spriteCache->getSpriteFrameByName("spider_dead_frame2");
    const auto dead_frame3 = spriteCache->getSpriteFrameByName("spider_dead_frame3");
    const auto dead_frame4 = spriteCache->getSpriteFrameByName("spider_dead_frame4");
    const auto dead_frame5 = spriteCache->getSpriteFrameByName("spider_dead_frame5");
    const auto dead_frame6 = spriteCache->getSpriteFrameByName("spider_dead_frame6");
    const auto dead_frame7 = spriteCache->getSpriteFrameByName("spider_dead_frame7");
    const auto dead_frame8 = spriteCache->getSpriteFrameByName("spider_dead_frame8");
    const auto dead_frame9 = spriteCache->getSpriteFrameByName("spider_dead_frame9");
    const auto dead_frame10 = spriteCache->getSpriteFrameByName("spider_dead_frame10");
    const auto dead_frame11 = spriteCache->getSpriteFrameByName("spider_dead_frame11");
    Vector<SpriteFrame *> deadFrames;
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
    deadFrames.pushBack(dead_frame10);
    deadFrames.pushBack(dead_frame11);
    Animation *dead_animation = Animation::createWithSpriteFrames(deadFrames, 0.1f);
    dead_animation->setLoops(1);
    aniCache->addAnimation(dead_animation, "spider_dead_animation");
}

Spider *Spider::createSpider()
{
    return create();
}

void Spider::move(int walk_direction)
{
    //移动
    //移动速度不是之前的情况，说明发生碰撞
    if (colClog == ColClogTime && this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation))
    {
        colClog = 0;
    }
    else
    {
        this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
    }

    if (!moving)
    {
        //移动的图形显示
        //直接获取缓存，不要将SpriteFrame保存在类中
        auto aniCache = AnimationCache::getInstance();
        const auto spider_animation = aniCache->getAnimation("spider_animation");
        Animate *spider_animate = Animate::create(spider_animation);
        this->getChildByName("body")->runAction(spider_animate);
        moving = true;
    }

    if (colClog == 0)
    {
        prev_walk_orientation = 5;
    }
}

bool Spider::init()
{
    if (!Monster::init())
    {
        return false;
    }
    const auto spider_texture_ = Director::getInstance()->getTextureCache()->addImage("res/gfx/monsters/classic/monster_080_spider.png");
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(spider_texture_, Rect(0, 0, 32, 32));
    Sprite *bodySprite = createWithSpriteFrame(bodyFrame);

    build_sprite_frame_cache(spider_texture_);
    build_animation_cache();

    this->addChild(bodySprite, 0, "body");

	radiusSize = 6;    //Spider碰撞大小
	bodyMass = 5;     //Spider重量
	moveSpeed = 100;     //Spider行走速度
	health = 3;         //Spider血量
	attack = 1;         //Spider攻击
	tearSpeed = 60;     //Spider泪速
	tearExistTime = 0; //Spider射程
    this->createPhyBody();
    return true;
}

void Spider::moveStrategy(const RoomViewModel & roomMap)
{
	colClog = 40;
	if (rand() % 2 ==0) {
		//冲向player方向，并且有一个碰撞阻塞（暂时无法对其进行操作）
		Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
		int walk_direction = ToPointDir(playerPos);
		
		this->move(walk_direction);
	}
	else {
		//暂停不动
		this->move(5);
	}
}
//---------------------------------------------------------FlyDaddy---------------------------------------------------------

string FlyDaddy::getDeadAnimation()
{
    return "monster_dead_animation";
}

void FlyDaddy::build_sprite_frame_cache(Texture2D *texture_) const
{
    auto spriteCache = SpriteFrameCache::getInstance();
    
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0,0,80,64)),"flydaddy_frame0");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(80,0,80,64)),"flydaddy_frame1");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(0,64,80,64)),"flydaddy_frame2");
    spriteCache->addSpriteFrame(SpriteFrame::createWithTexture(texture_, Rect(80,64,80,64)),"flydaddy_frame3");

}

void FlyDaddy::build_animation_cache()
{
    auto spriteCache = SpriteFrameCache::getInstance();
    auto aniCache = AnimationCache::getInstance();
    //注意 flydaddy 不是一直有动画，只有在发射 baby 苍蝇的时候才会产生动画
    const auto flydaddy_frame0 = spriteCache->getSpriteFrameByName("flydaddy_frame0");
    const auto flydaddy_frame1 = spriteCache->getSpriteFrameByName("flydaddy_frame1");
    const auto flydaddy_frame2 = spriteCache->getSpriteFrameByName("flydaddy_frame2");
    const auto flydaddy_frame3 = spriteCache->getSpriteFrameByName("flydaddy_frame3");
    Vector<SpriteFrame *> flydaddyFrames;
    flydaddyFrames.pushBack(flydaddy_frame0);
    flydaddyFrames.pushBack(flydaddy_frame1);
    flydaddyFrames.pushBack(flydaddy_frame2);
    flydaddyFrames.pushBack(flydaddy_frame3);
    Animation *flydaddy_animation = Animation::createWithSpriteFrames(flydaddyFrames, 0.4f);
    flydaddy_animation->setLoops(-1);
    flydaddy_animation->setRestoreOriginalFrame(true);
    aniCache->addAnimation(flydaddy_animation, "flydaddy_animation");
}

FlyDaddy *FlyDaddy::createFlyDaddy()
{
    return create();
}

void FlyDaddy::move(int walk_direction)
{
    //移动
    //移动速度不是之前的情况，说明发生碰撞
    if (colClog == ColClogTime && this->getPhysicsBody()->getVelocity() != calSpeed(prev_walk_orientation))
    {
        colClog = 0;
    }
    else
    {
        this->getPhysicsBody()->setVelocity(calSpeed(walk_direction));
    }
    
    if (!moving)
    {
        //移动的图形显示
        //直接获取缓存，不要将SpriteFrame保存在类中
        auto aniCache = AnimationCache::getInstance();
        const auto flydaddy_animation = aniCache->getAnimation("flydaddy_animation");
        Animate *flydaddy_animate = Animate::create(flydaddy_animation);
        this->getChildByName("body")->runAction(flydaddy_animate);
        moving = true;
    }
    
    if (colClog == 0)
    {
        prev_walk_orientation = 5;
    }
}

bool FlyDaddy::init()
{
    if (!Monster::init())
    {
        return false;
    }
    const auto flydaddy_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/bosses/classic/boss_007_dukeofflies.png");
    SpriteFrame *bodyFrame = SpriteFrame::createWithTexture(flydaddy_texture, Rect(0, 0, 80, 64));
    Sprite *bodySprite = createWithSpriteFrame(bodyFrame);
    
    build_sprite_frame_cache(flydaddy_texture);
    build_animation_cache();
    
    this->addChild(bodySprite, 0, "body");
    
    radiusSize = 15;    //Spider碰撞大小
    bodyMass = 100;     //Spider重量
    moveSpeed = 30;     //Spider行走速度
    health = 300;         //Spider血量
    attack = 2;         //Spider攻击
    tearSpeed = 60;     //Spider泪速
    tearExistTime = 0; //Spider射程
    this->createPhyBody();
    return true;
}

void FlyDaddy::moveStrategy(const RoomViewModel & roomMap)
{
    if (rand() % 2 == 0) {
        //冲向player方向，并且有一个碰撞阻塞（暂时无法对其进行操作）
        Vec2 playerPos = this->getParent()->getChildByTag(1)->getPosition();
        int walk_direction = ToPointDir(playerPos);
        colClog = 40;
        this->move(walk_direction);
    }
    else {
        //暂停不动
        this->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}


