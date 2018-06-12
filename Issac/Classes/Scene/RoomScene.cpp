#include "RoomScene.h"
#include "AppDelegate.h"
#include <iostream>
#include "Service/RoomService.h"

USING_NS_CC;
using namespace std;

Scene * RoomScene::createScene(int roomID)
{
	return create(roomID);
}

bool RoomScene::init(int roomID)
{
    if (!initWithPhysics())
    {
        return false;
    }

    //根据ViewMode渲染
    room_vm_ = RoomService::getInstance()->get_room(roomID);
    mini_map_vm_ = RoomService::getInstance()->get_mini_map(roomID);

    //画物理引擎框
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    const Size size = Director::getInstance()->getWinSize();
   // std::cout << size.width <<" "<< size.height << endl;
    /** zorder
     * 9 DeadScreen
     * 8 HUD, PauseMenu
     * 7 PauseScreen
     * 6 Overlay
     * 5 MiniMap
     * 3 Issac, Monster,Rock
     * 2 Room shading
     * 1 Controls, Door, Door Center,ivisiable bordor
     * 0 Room Background
     */
    //TODO 应该有更好的方法生成背景贴图，而不是暴力生成4个或多个碎片
    //TODO 动态加载贴图？如Issac的buff皮肤（在别的贴图上）如何更新
    Texture2D *texture_room = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/01_basement.png");
    //TODO 更小的地图切片和随机性支持
    Sprite * room_piece1 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece1->setAnchorPoint(Point(0,0));
    room_piece1->setPosition(0, 143);
    addChild(room_piece1,0);
    
    Sprite * room_piece2 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece2->setFlippedX(true);
    room_piece2->setAnchorPoint(Point(0,0));
    room_piece2->setPosition(221, 143);
    addChild(room_piece2,0);
    
    Sprite * room_piece3 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece3->setFlippedY(true);
    room_piece3->setAnchorPoint(Point(0,0));
    room_piece3->setPosition(0, 0);
    addChild(room_piece3,0);
    
    Sprite * room_piece4 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece4->setFlippedX(true);
    room_piece4->setFlippedY(true);
    room_piece4->setAnchorPoint(Point(0,0));
    room_piece4->setPosition(221, 0);
    addChild(room_piece4,0);
    
    Texture2D *texture_shading = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/shading_utero.png");
    Sprite * shading = Sprite::createWithTexture(texture_shading,Rect(0,0,442,286));
    shading->setPosition(221,143);
    addChild(shading,2);
    
    Texture2D *texture_controls = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/controls.png");
    Sprite * controls = Sprite::createWithTexture(texture_controls, Rect(0,0,325,85));
    controls->setPosition(221,143);
    addChild(controls,1);
    
    //TODO 弹幕Tear的生成、生命周期、碰撞过程、管理（多Tear对象共存）
    
    //TODO 2.光影遮罩       gfx\overlays res\backdrop（光）
    //光影遮罩，在整个Scene最顶部
    Texture2D *texture_overlay = Director::getInstance()->getTextureCache()->addImage("res/gfx/overlays/basement/1x1_overlay_1.png");
    Sprite * overlay = Sprite::createWithTexture(texture_overlay,Rect(0,0,442,286));
    overlay->setPosition(221,143);
    addChild(overlay,6);
    
    Texture2D *texture_rainbowpoop = Director::getInstance()->getTextureCache()->addImage("res/gfx/grid/grid_poop_rainbow.png");
    Sprite * rainbowpoop = Sprite::createWithTexture(texture_rainbowpoop,Rect(0,0,32,32));// TODO 地面物品都有着损坏状态，不应该在这里生成
    rainbowpoop->setPosition(300,150);// TODO 地面物品网格化，对齐
    addChild(rainbowpoop,3);
    
    build_frame_cache();

	//创建一个盒子，用来碰撞  
	Sprite* edgeSpace = Sprite::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setRestitution(1.0f);
	edgeSpace->setPhysicsBody(boundBody);
	edgeSpace->setPosition(Point(size.width / 2, size.height / 2));
	addChild(edgeSpace);
	edgeSpace->setTag(0);
	
	//门的生成
	//门0,1,2,3是左，上，右，下4门
	auto door_mask = room_vm_.getDoorEnable();
	auto door_style = room_vm_.getDoorStyle();
	for (int i = 0; i < 4; i++) {
		if (door_mask[i] > 0) {	//有门生成门（碰撞体积略小）
			doors_.pushBack(Door::createDoor(i, door_style[i], size));
			addChild(doors_.at(i), 1);
		}
		else {	//无门生成墙
			stones_.pushBack(Stone::createStone(0, Size(64, 48)));
			stones_.at(stones_.size() - 1)->setRotation(270 + i * 90);
			switch (i) {
			case(0): stones_.at(stones_.size() - 1)->setPosition(24, size.height / 2); break;
			case(1): stones_.at(stones_.size() - 1)->setPosition(size.width / 2, size.height - 24); break;
			case(2): stones_.at(stones_.size() - 1)->setPosition(size.width - 24, size.height / 2); break;
			case(3): stones_.at(stones_.size() - 1)->setPosition(size.width / 2, 24); break;
			}
			addChild(stones_.at(stones_.size() - 1), 1);
		}
	}

	//边界无形石头生成
	//竖着的4块
	stones_.pushBack(Stone::createStone(0, Size(48, size.height / 2-32)));
	stones_.at(stones_.size() - 1)->setPosition(24, size.height / 4 - 16);
	addChild(stones_.at(stones_.size() - 1), 1);
	stones_.pushBack(Stone::createStone(0, Size(48, size.height / 2 - 32)));
	stones_.at(stones_.size() - 1)->setPosition(24, size.height / 4*3 + 16);
	addChild(stones_.at(stones_.size() - 1), 1);
	stones_.pushBack(Stone::createStone(0, Size(48, size.height / 2 - 32)));
	stones_.at(stones_.size() - 1)->setPosition(size.width-24, size.height / 4 - 16);
	addChild(stones_.at(stones_.size() - 1), 1);
	stones_.pushBack(Stone::createStone(0, Size(48, size.height / 2 - 32)));
	stones_.at(stones_.size() - 1)->setPosition(size.width - 24, size.height / 4 * 3 + 16);
	addChild(stones_.at(stones_.size() - 1), 1);
	//横的4块
	stones_.pushBack(Stone::createStone(0, Size(size.width / 2 - 80,48)));
	stones_.at(stones_.size() - 1)->setPosition(8+size.width / 4, 24);
	addChild(stones_.at(stones_.size() - 1), 1);
	stones_.pushBack(Stone::createStone(0, Size(size.width / 2 - 80, 48)));
	stones_.at(stones_.size() - 1)->setPosition(-8 + size.width / 4*3, 24);
	addChild(stones_.at(stones_.size() - 1), 1);
	stones_.pushBack(Stone::createStone(0, Size(size.width / 2 - 80, 48)));
	stones_.at(stones_.size() - 1)->setPosition(8 + size.width / 4, size.height-24);
	addChild(stones_.at(stones_.size() - 1), 1);
	stones_.pushBack(Stone::createStone(0, Size(size.width / 2 - 80, 48)));
	stones_.at(stones_.size() - 1)->setPosition(-8 + size.width / 4 * 3, size.height - 24);
	addChild(stones_.at(stones_.size() - 1), 1);
	
	//遍历room的map，生成player，monster，stone
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 7; j++) {
			if (room_vm_.getRoomMap(i, j) == 3) { //3说明这个位置是player
				//player生成
				player = Issac::createIssac();
				player->createPhyBody();
				player->setPosition(48+i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2);
				addChild(player, 3);
			}
			if (room_vm_.getRoomMap(i, j) == 4) { //4说明这个位置是Fatty
				//Fatty生成
				monsters_.pushBack((Monster*)Fatty::createFatty());
				monsters_.at(monsters_.size()-1)->setPosition(Vec2(48 + i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2));
				addChild(monsters_.at(monsters_.size() - 1), 3, "fatty1");
			}
            if (room_vm_.getRoomMap(i, j) == 5) { //4说明这个位置是Fly
                //Fatty生成
                monsters_.pushBack((Monster*)Fly::createFly());
                monsters_.at(monsters_.size()-1)->setPosition(Vec2(48 + i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2));
                addChild(monsters_.at(monsters_.size() - 1), 3, "fly1");
            }
			if (room_vm_.getRoomMap(i, j) == 1) {  
				//小石头
				stones_.pushBack(Stone::createStone(1, Size(26, 26)));
				stones_.at(stones_.size() - 1)->setPosition(Vec2(48 + i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2));
				addChild(stones_.at(stones_.size() - 1), 3);
			}
			if (room_vm_.getRoomMap(i, j) == 2 
				&& i>=1 && j>=1 && room_vm_.getRoomMap(i-1, j-1) == 2) {
				//大石头
				stones_.pushBack(Stone::createStone(2, Size(52, 52)));
				stones_.at(stones_.size() - 1)->setPosition(Vec2(48 + i*RoomUnitSize.width, 48 + j*RoomUnitSize.height));
				addChild(stones_.at(stones_.size() - 1), 3);
			}
		}
	}
 
    //TODO 4.小地图和生命值，物品栏在z最大处（最顶层），（且随窗口大小自适应，如来不及就做成固定大小）
    //TODO 状态栏层应该独立于RoomScene，生命值和图案用状态reg统一管理
    Texture2D * texture_heart = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/ui_hearts.png");
    Sprite * heart = Sprite::createWithTexture(texture_heart, Rect(0,0,16,16));
    heart->setPosition(70,250);
    addChild(heart, 8);
    
    //TODO 物品栏层应该独立于RoomScene，物品用状态reg统一管理
    Texture2D * texture_hud = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/hudpickups.png");
    Sprite * hud_coin = Sprite::createWithTexture(texture_hud, Rect(0,0,16,16));
    hud_coin->setPosition(30,224);
    Sprite * hud_bomb = Sprite::createWithTexture(texture_hud, Rect(0,16,16,16));
    hud_bomb->setPosition(30,208);
    Sprite * hud_goldkey = Sprite::createWithTexture(texture_hud, Rect(16,16,16,16));
    hud_goldkey->setPosition(30,192);
    Sprite * hud_silverkey = Sprite::createWithTexture(texture_hud, Rect(16,0,16,16));
    hud_silverkey->setPosition(30,176);
    addChild(hud_coin, 8);
    addChild(hud_bomb, 8);
    addChild(hud_goldkey, 8);
    addChild(hud_silverkey, 8);
    
    //TODO 小地图应加载到缓存，并设置透明度，独立于RoomScene，元素都在texture_minimap中
    Texture2D * texture_minimap = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/minimap1.png");
    Sprite * minimap = Sprite::createWithTexture(texture_minimap, Rect(0,0,56,48));
    minimap->setPosition(370,240);
    addChild(minimap, 5);
    
    //TODO 数字缓存加载，需专门处理物品计数和字符显示，字符大小：18x31
    Texture2D * texture_font = Director::getInstance()->getTextureCache()->addImage("res/font/pftempestasevencondensed_0.png");
    Sprite * num0 = Sprite::createWithTexture(texture_font, Rect(18*14,21*3,18,21));
    num0->setPosition(46,224);
    addChild(num0, 8);
    
    //srand(static_cast<unsigned>(time(nullptr)));//初始化时种下种子，不能在update或fire方法里种，不然随机性消失
    //TODO 加载所有界面元素
    //TODO 1.石头生成，门生成和进入响应，需触发地图更新，怪没打完逃不出去！ gfx\grid
    
    //TODO 3.物品生成       gfx\items
    
    //TODO 4.1 计分板，原版好像没有这个东西，可以做成计时闯关，时间短分高（如果做不出难度更新）
    
    //TODO 5.生成怪物               gfx\monsters gfx\bosses
    //TODO 6.地面破坏效果，由物品生命周期控制，（随机纹理，来不及就不做，与贴图随机选择有关）gfx\effects
    //TODO 7.Issac 吃buff后状态的变化，如换了个皮肤，与类内皮肤成员有关
    //TODO 99. 联机模式，素材中有babyIssac
    //TODO 100. (Issac有宠物，它会自己攻击)   gfx\familiar
   
    //暂停菜单
    Texture2D * pausescreenTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/pausescreen.png");
    Texture2D * pausescreenBgTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/bgblack.png");
    pausescreen = Sprite::createWithTexture(pausescreenBgTexture, Rect(0,0,442,286));
    Sprite * pausecursor = Sprite::createWithTexture(pausescreenTexture, Rect(240,0,14,14));
    Sprite * pausemenu = Sprite::createWithTexture(pausescreenTexture, Rect(0,0,240,208));
    pausemenu->setPosition(-250,143);//初始在屏幕外
    pausecursor->setPosition(180,95);
    pausescreen->setOpacity(0x7f);
    pausemenu->addChild(pausecursor,1,"pausecursor");
    pausescreen->setPosition(221,143);
    pausescreen->addChild(pausemenu,0,"pausemenu");
    addChild(pausescreen,7);
    pausescreen->setVisible(false);
    
    //结束菜单
    Texture2D * deadportraitTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/death portraits.png");
    Texture2D * deadoptionTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/backselectwidget.png");
    Texture2D * deadscreenBgTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/bgblack.png");
    deadscreen = Sprite::createWithTexture(deadscreenBgTexture, Rect(0,0,442,286));
    Sprite * back = Sprite::createWithTexture(deadoptionTexture, Rect(0,128,96,128));
    back->setPosition(0+50,0);
    Sprite * restart = Sprite::createWithTexture(deadoptionTexture, Rect(96,128,112,128));
    restart->setPosition(442-50,0+30);
    Sprite * deadportrait = Sprite::createWithTexture(deadportraitTexture, Rect(192,0,224,256));
    deadportrait->setPosition(221,143);
    deadscreen->addChild(back,1,"back");
    deadscreen->addChild(restart,1,"restart");
    deadscreen->addChild(deadportrait,1,"deadportrait");
    deadscreen->setOpacity(0x7f);
    deadscreen->setPosition(221,143);
    addChild(deadscreen,9);
    deadscreen->setVisible(false);
    
    //TODO 因为一次放一个炸弹，因此炸弹预生成。如果同时放多个，需要改
    bomb = SimpleItem::createSimpleItem();
    bomb->setVisible(false);
    addChild(bomb,3);
    
    scheduleUpdate();
    return true;
}

void RoomScene::set_event_listener(IRoomSceneListener * listener)
{
    this->listener_ = listener;

    //TODO 事件监听
    auto _touchListener = EventListenerTouchOneByOne::create();

    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        this->listener_->on_touch_began(touch, event);
        return false;
    };

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = [this](Event * event)
    {
        this->listener_->on_mouse_down(event);
        return false;
    };
    
    auto _keyboard_listener = EventListenerKeyboard::create();
    _keyboard_listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        this->listener_->on_key_pressed(keyCode, event);
    };
    
    _keyboard_listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        this->listener_->on_key_released(keyCode, event);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboard_listener, this);

	//碰撞listener
	//添加监听器
	auto contactListener = EventListenerPhysicsContact::create();
	//设置监听器的碰撞开始函数  
	contactListener->onContactBegin = CC_CALLBACK_1(RoomScene::onContactBegin, this);
	//添加到事件分发器中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void RoomScene::update(float delta)
{
    if(model.game_stat == 0){
		//开始 
		if (Director::getInstance()->getRunningScene()->getPhysicsWorld()!=NULL) {
			Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0);
		}
        if(pausescreen->isVisible()){
            pausescreen->setVisible(false);
            auto pausescreenmovein = MoveTo::create(0.2,Vec2(-250, 143));
            pausescreen->getChildByName("pausemenu")->runAction(pausescreenmovein);
            model.paused_menu_generated_flag = 0;
        }
        if(model.bomb){
            cout << "bomb placed"<<endl;
            //TODO 炸弹爆炸动画，爆炸范围判定，销毁
            bomb->setPosition(player->getPositionX(),player->getPositionY());
            bomb->setVisible(true);
            model.bomb = false;
        }
		
		//tear倒计时和消失
		for (auto it = tears_.begin(); it!=tears_.end();) {
			if ((*it)->getTearExistTime() == 0) {
				(*it)->removeFromParent();
				it=tears_.erase(it);
			}
			else {
				(*it)->setTearExistTime((*it)->getTearExistTime() - 1);
				it++;
			}			
		}
        
		//monster移动和死亡
		for (auto it = monsters_.begin(); it != monsters_.end(); ) 
			if ((*it)->getHealth() <= 0) {
			//血量<0死亡了
				(*it)->removeFromParent();
				it = monsters_.erase(it);
			}
			else {
				if ((*it)->getColClog() != ColClogTime) {
					(*it)->setColClog((*it)->getColClog() + 1);
					if ((*it)->getColClog() == ColClogTime) {
						(*it)->getPhysicsBody()->setVelocity(Vec2(0, 0));
					}
				}
				else {
					(*it)->moveStrategy((*it)->ToPointDir(player->getPosition()));
				}
				//无敌时间的倒计时
				if ((*it)->getInvincibleTime() > 0) {
					(*it)->setInvincibleTime((*it)->getInvincibleTime() - 1);
				}
				it++;
			}
        
		//player移动	
		if (player->getHealth() > 0) {
			if (player->getColClog() != ColClogTime) {
				player->setColClog(player->getColClog() + 1);
				if (player->getColClog() == ColClogTime) {
					player->getPhysicsBody()->setVelocity(Vec2(0, 0));
				}
			}
			else {
				player->move(model.walk_direction, model.tear_direction);
			}
			//player无敌时间的倒计时
			if (player->getInvincibleTime() > 0) {
				player->setInvincibleTime(player->getInvincibleTime() - 1);
			}
		}
		else {
			//player血量为0，Issac死亡，添加动画和游戏结束界面？
			log("DEAD");
            //TODO播放死亡动画
            //设置 game status
            model.game_stat = 2;
		}

        
		if(model.tear_direction == 5){
			this->schedule(schedule_selector(RoomScene::fire), 0.4,65536,0.001);
		}
		//TODO Issac所有的状态更新：如碰撞掉血，被炸弹炸掉血，吃小邢邢回血，自身物品状态都由场景触发
		//TODO 碰撞方向判定，闪动效果（提醒玩家螳臂当车了）
		//TODO 碰撞效果，Issac固定掉半格血，怪物可能自爆，也可能还活着
		//std::cout << "Walking d: "<<model.walk_direction<<" Tear d: " << model.tear_direction << " PrevHead d: "<< player->getPrevHeadOrientation()<<endl;
	} 
	else if(model.game_stat == 1){
		//暂停 
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
        
		if (model.paused_menu_generated_flag == 0) {
            this->unschedule(schedule_selector(RoomScene::fire));//防止tear在暂停界面发射
            pausescreen->setVisible(true);
            auto pausescreenmovein = MoveTo::create(0.2, Vec2(250, 143));
            pausescreen->getChildByName("pausemenu")->runAction(pausescreenmovein);
            model.paused_menu_generated_flag = 1;
        }
        switch (model.paused_menu_cursor) {
        case 0:
            pausescreen->getChildByName("pausemenu")->getChildByName("pausecursor")->runAction(MoveTo::create(0, Vec2(60, 85)));
            break;
        case 1:
            pausescreen->getChildByName("pausemenu")->getChildByName("pausecursor")->runAction(MoveTo::create(0, Vec2(45, 60)));
            break;
        case 2:
            pausescreen->getChildByName("pausemenu")->getChildByName("pausecursor")->runAction(MoveTo::create(0, Vec2(65, 35)));
            break;
        default:
            break;
        }
	}
    else{
        if(model.dead_menu_generated_flag == 0) {
            this->unschedule(schedule_selector(RoomScene::fire));
            deadscreen->setVisible(true);
            model.dead_menu_generated_flag = 1;
        }
    }
	//   std::cout << "Test: "<<model.paused << " " << model.paused_menu_generated_flag << " " << model.paused_menu_cursor << endl;
}

void RoomScene::set_model(RoomSceneModel model)
{
    this->model = model;
}

void RoomScene::fire(float dt){
	//创建一个Tear
	tears_.pushBack(Tear::createTear());
	//设定初始tear位置和速度
    const int advance = 15;
    int x_advance;
    int y_advance;
	double tear_V = player->getMoveSpeed() + player->getTearSpeed();
    switch (model.tear_direction) {
        case 2:
            x_advance = 0;
            y_advance = advance+random(-10,10);
			tears_.at(tears_.size() - 1)->getPhysicsBody()->setVelocity(Vec2(0,tear_V));
            break;
        case 4:
            x_advance = -advance+random(-10,10);
            y_advance = 0;
			tears_.at(tears_.size() - 1)->getPhysicsBody()->setVelocity(Vec2(-tear_V, 0));
            break;
        case 6:
            x_advance = advance+random(-10,10);
            y_advance = 0;
			tears_.at(tears_.size() - 1)->getPhysicsBody()->setVelocity(Vec2(tear_V, 0));
            break;
        case 8:
            x_advance = 0;
            y_advance = -advance+random(-10,10);
			tears_.at(tears_.size() - 1)->getPhysicsBody()->setVelocity(Vec2(0, -tear_V));
            break;
        default:
            x_advance = 0;
            y_advance = 0;
    }
	//初始位置
	tears_.at(tears_.size() - 1)->setPosition(Vec2(player->getPosition().x+x_advance, player->getPosition().y+y_advance+5));
	//存在时间,攻击
	tears_.at(tears_.size() - 1)->setTearExistTime(player->getTearExistTime());
	tears_.at(tears_.size() - 1)->setAttack(player->getAttack());
	//是谁发射的
	tears_.at(tears_.size() - 1)->setTag(4);
	addChild(tears_.at(tears_.size() - 1),3);
}

void RoomScene::build_frame_cache() const
{
    Texture2D * poofTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/effects/effect_015_tearpoofa.png");
    const auto frame0 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 0, 64, 64));
    const auto frame1 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 0, 64, 64));
    const auto frame2 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 0, 64, 64));
    const auto frame3 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 0, 64, 64));
    const auto frame4 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 64, 64, 64));
    const auto frame5 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 64, 64, 64));
    const auto frame6 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 64, 64, 64));
    const auto frame7 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 64, 64, 64));
    const auto frame8 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 128, 64, 64));
    const auto frame9 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 128, 64, 64));
    const auto frame10 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 128, 64, 64));
    const auto frame11 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 128, 64, 64));
    const auto frame12 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 192, 64, 64));
    const auto frame13 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 192, 64, 64));
    const auto frame14 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 192, 64, 64));
    const auto frame15 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 192, 64, 64));

    auto fcache = SpriteFrameCache::getInstance();
    fcache->addSpriteFrame(frame0, "t_frame0");
    fcache->addSpriteFrame(frame1, "t_frame1");
    fcache->addSpriteFrame(frame2, "t_frame2");
    fcache->addSpriteFrame(frame3, "t_frame3");
    fcache->addSpriteFrame(frame4, "t_frame4");
    fcache->addSpriteFrame(frame5, "t_frame5");
    fcache->addSpriteFrame(frame6, "t_frame6");
    fcache->addSpriteFrame(frame7, "t_frame7");
    fcache->addSpriteFrame(frame8, "t_frame8");
    fcache->addSpriteFrame(frame9, "t_frame9");
    fcache->addSpriteFrame(frame10, "t_frame10");
    fcache->addSpriteFrame(frame11, "t_frame11");
    fcache->addSpriteFrame(frame12, "t_frame12");
    fcache->addSpriteFrame(frame13, "t_frame13");
    fcache->addSpriteFrame(frame14, "t_frame14");
    fcache->addSpriteFrame(frame15, "t_frame15");
    
    
}

bool RoomScene::onContactBegin(PhysicsContact& contact)
{
	Moveable* nodeA = (Moveable*)contact.getShapeA()->getBody()->getNode();
	Moveable* nodeB = (Moveable*)contact.getShapeB()->getBody()->getNode();
	int tagA = contact.getShapeA()->getBody()->getNode()->getTag();
	int tagB = contact.getShapeB()->getBody()->getNode()->getTag();
	//tag小的为A
	if (tagA > tagB) {
		Moveable* tempnode = nodeA;
		nodeA = nodeB;
		nodeB = tempnode;
		int temp_tag = tagA;
		tagA = tagB;
		tagB = temp_tag;
	}
	//tag=0 静止障碍物; tag=1:player; tag=2:monster; tag=3:tearbyMonster; tag=4:tearbyIssac
	if (nodeA && nodeB)
	{
		if (tagA==1 && tagB==2 && nodeA->getInvincibleTime()==0 )
		{
			//Issac被monster碰到，受伤
			nodeA->setHealth(nodeA->getHealth() - nodeB->getAttack());
			//Issac进入短暂无敌状态
			nodeA->setInvincibleTime(20);
			//TO DO添加受伤动画？
			log("Issac Health:%lf",nodeA->getHealth());
		}
		//怪物和眼泪碰撞
		if (tagA == 2 && (tagB == 3 || tagB == 4)) {
			nodeA->setHealth(nodeA->getHealth() - nodeB->getAttack());
		}
		//Issac和怪物眼泪碰撞
		if (tagA == 1 && tagB == 3 && nodeA->getInvincibleTime() == 0) {
			nodeA->setHealth(nodeA->getHealth() - nodeB->getAttack());
			//Issac进入短暂无敌状态
			if (tagA == 1) nodeA->setInvincibleTime(20);
			//TO DO添加受伤动画？
		}
		//Issac和门的碰撞
		if (tagA == 0 && tagB == 1 && monsters_.size() == 0) {
			//出门了！
			log("go out!");
		}

		//眼泪碰撞后消失
		if (tagA == 3 || tagA==4) nodeA->setTearExistTime(0);
		if (tagB == 3 || tagB==4) nodeB->setTearExistTime(0);
	}

	//bodies can collide
	return true;
}
