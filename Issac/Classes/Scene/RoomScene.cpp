#include "RoomScene.h"
#include "AppDelegate.h"
#include <iostream>
#include "Service/RoomService.h"
#include "Controller/RoomSceneController.h"
#include "Service/PlayerService.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

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
    room_vm_ = RoomService::getInstance()->enter_room(roomID);
    mini_map_vm_ = RoomService::getInstance()->get_mini_map(roomID);

    //画物理引擎框
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    const Size size = Director::getInstance()->getWinSize();
   // std::cout << size.width <<" "<< size.height << endl;
    /** zorder
     * 9 DeadScreen
     * 8 HUD, PauseMenu
     * 7 PauseScreen,OptionScreen
     * 6 Overlay, BossHealthBar
     * 5 MiniMap
     * 4 Tear
     * 3 Issac, Monster, Rock, Pickup
     * 2 Room shading
     * 1 Controls, Door, Door Center,ivisiable bordor
     * 0 Room Background
     */

    //房间墙面贴图
    const auto ground_s = room_vm_.getGroundStyle();

    Texture2D *texture_room = Director::getInstance()->getTextureCache()->addImage(ground_s);//res/gfx/backdrop/01_basement.png
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
    
    //光线阴影贴图
    Texture2D *texture_shading = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/shading_utero.png");
    Sprite * shading = Sprite::createWithTexture(texture_shading,Rect(0,0,442,286));
    shading->setPosition(221,143);
    addChild(shading,2);
    
    //初始界面的提示贴图
    if (RoomService::getInstance()->is_init_room())
    {
        Texture2D *texture_controls = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/controls.png");
        Sprite * controls = Sprite::createWithTexture(texture_controls, Rect(0, 0, 325, 85));
        controls->setPosition(221, 143);
        addChild(controls, 1);
    }

    //光影遮罩，在整个Scene最顶部
    Texture2D *texture_overlay = Director::getInstance()->getTextureCache()->addImage("res/gfx/overlays/basement/1x1_overlay_1.png");
    Sprite * overlay = Sprite::createWithTexture(texture_overlay,Rect(0,0,442,286));
    overlay->setPosition(221,143);
    addChild(overlay,6);
    
    
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
			//door tag:5,6,7,8是左、上、右、下4个门
			doors_.at(doors_.size() - 1)->setTag(5 + i);
			addChild(doors_.at(doors_.size() - 1), 1);
		}
		else {	//无门生成墙
			stones_.pushBack(Stone::createStone(0, Size(64, 48)));
			stones_.at(stones_.size() - 1)->setRotation(270 + i * 90);
			switch (i) {
			case(0): stones_.at(stones_.size() - 1)->setPosition(24, size.height / 2); break;
			case(1): stones_.at(stones_.size() - 1)->setPosition(size.width / 2, size.height - 24); break;
			case(2): stones_.at(stones_.size() - 1)->setPosition(size.width - 24, size.height / 2); break;
			case(3): stones_.at(stones_.size() - 1)->setPosition(size.width / 2, 24); break;
            default: break;
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
            if (room_vm_.getRoomMap(i, j) == 5) { //5说明这个位置是Fly
                //Fly生成
                monsters_.pushBack((Monster*)Fly::createFly());
                monsters_.at(monsters_.size()-1)->setPosition(Vec2(48 + i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2));
                addChild(monsters_.at(monsters_.size() - 1), 3, "fly1");
            }
            if (room_vm_.getRoomMap(i, j) == 6) { //6说明这个位置是Gaper
                //Gaper生成
                monsters_.pushBack((Monster*)Gaper::createGaper());
                monsters_.at(monsters_.size()-1)->setPosition(Vec2(48 + i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2));
                addChild(monsters_.at(monsters_.size() - 1), 3, "gaper1");
            }
            if (room_vm_.getRoomMap(i, j) == 7) { //7说明这个位置是Spider
                //Spider生成
                monsters_.pushBack((Monster*)Spider::createSpider());
                monsters_.at(monsters_.size()-1)->setPosition(Vec2(48 + i*RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j*RoomUnitSize.height + RoomUnitSize.height / 2));
                addChild(monsters_.at(monsters_.size() - 1), 3, "spider1");
            }
			if (room_vm_.getRoomMap(i, j) == 8) { //8说明这个位置是FattyFire
												  //FattyFire生成
				monsters_.pushBack((Monster*)FattyFire::createFattyFire());
				monsters_.at(monsters_.size() - 1)->setPosition(Vec2(48 + i * RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j * RoomUnitSize.height + RoomUnitSize.height / 2));
				addChild(monsters_.at(monsters_.size() - 1), 3, "fatty1");
			}
			if (room_vm_.getRoomMap(i, j) == 9) { //9说明这个位置是FlyFire
												  //FlyFire生成
				monsters_.pushBack((Monster*)FlyFire::createFlyFire());
				monsters_.at(monsters_.size() - 1)->setPosition(Vec2(48 + i * RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j * RoomUnitSize.height + RoomUnitSize.height / 2));
				addChild(monsters_.at(monsters_.size() - 1), 3, "fly1");
			}
			if (room_vm_.getRoomMap(i, j) == 10) { //10说明这个位置是GaperFire
												  //GaperFire生成
				monsters_.pushBack((Monster*)GaperFire::createGaperFire());
				monsters_.at(monsters_.size() - 1)->setPosition(Vec2(48 + i * RoomUnitSize.width + RoomUnitSize.width / 2, 48 + j * RoomUnitSize.height + RoomUnitSize.height / 2));
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
    Texture2D * texture_hud = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/hudpickups.png");
    healthbar = Sprite::createWithTexture(texture_hud, Rect(0,0,1,1));//用 HUD 贴图的角落生成一个1x1透明贴图
    healthbar->setPosition(70,250);
    addChild(healthbar, 8);
    
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
    
    //小地图生成
    //mini_map_vm_
    Texture2D * texture_minimap = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/minimap1.png");
    Sprite * minimap = Sprite::createWithTexture(texture_minimap, Rect(0, 0, 56, 48));
    minimap->setPosition(370, 240);
    addChild(minimap, 5);

    const auto msks = mini_map_vm_.getMiniMask();

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            const auto msk = msks[i][j];

            if (msk == -2)//中间位置
            {
                Sprite * current_room = Sprite::createWithTexture(texture_minimap, Rect(112, 80, 16, 16));//当前房间
                current_room->setPosition(28, 24);
                minimap->addChild(current_room, 1);
            }
            else if (msk >= 0 && msk <8)//普通房间
            {
                Sprite * available_room = Sprite::createWithTexture(texture_minimap, Rect(64, 16, 16, 16));//非当前房间
                available_room->setPosition(12+j*8, 40-i*8);
                minimap->addChild(available_room, 1);

            }
            else if (msk >= 8 && msk < 15)//宝藏房间
            {
                Sprite * available_room = Sprite::createWithTexture(texture_minimap, Rect(64, 16, 16, 16));//非当前房间
                available_room->setPosition(12 + j * 8, 40 - i * 8);
                minimap->addChild(available_room, 1);
                Sprite * treasure_room_icon = Sprite::createWithTexture(texture_minimap, Rect(64, 64, 16, 16));//buff房间标志
                treasure_room_icon->setPosition(12 + j * 8, 40 - i * 8);
                minimap->addChild(treasure_room_icon, 1);

            }
            else if (msk >= 15 && msk < 20)//Boss房间
            {
                Sprite * available_room = Sprite::createWithTexture(texture_minimap, Rect(64, 16, 16, 16));//非当前房间
                available_room->setPosition(12 + j * 8, 40 - i * 8);
                minimap->addChild(available_room, 1);
                Sprite * boss_room_icon = Sprite::createWithTexture(texture_minimap, Rect(32, 80, 16, 16));//boss房间标志
                boss_room_icon->setPosition(12 + j * 8, 40 - i * 8);
                minimap->addChild(boss_room_icon, 1);
            }
        }
    }
    
    //TODO 数字缓存加载，需专门处理物品计数和字符显示，字符大小：18x31
    Texture2D * texture_font = Director::getInstance()->getTextureCache()->addImage("res/font/pftempestasevencondensed_0.png");
    Sprite * num0 = Sprite::createWithTexture(texture_font, Rect(18*14,21*3,18,21));
    num0->setPosition(46,224);
    addChild(num0, 8);
    
    //TODO 1.石头生成，门生成和进入响应，需触发地图更新，怪没打完逃不出去！ gfx\grid
    
    //TODO 3.物品生成       gfx\items
    
    //TODO 4.1 计分板，原版好像没有这个东西，可以做成计时闯关，时间短分高（如果做不出难度更新）
    
    //TODO 5.生成怪物               gfx\monsters gfx\bosses
    //TODO 6.地面破坏效果，由物品生命周期控制，（随机纹理，来不及就不做，与贴图随机选择有关）gfx\effects
    //TODO 7.Issac 吃buff后状态的变化，如换了个皮肤，与类内皮肤成员有关
    //TODO 99. 联机模式，素材中有babyIssac
    //TODO 100. (Issac有宠物，它会自己攻击)   gfx\familiar
   
    //暂停菜单
    //暂停界面
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
    
    //设置菜单
    Texture2D * optionscreenTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/optionsmenudark.png");
    Texture2D * optionscreenBgTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/bgblack.png");
    optionscreen = Sprite::createWithTexture(optionscreenBgTexture, Rect(0,0,442,286));
    Sprite * optioncursor = Sprite::createWithTexture(optionscreenTexture, Rect(234,24,16,24));
    Sprite * optionmenu = Sprite::createWithTexture(optionscreenTexture, Rect(0,0,234,234));
    Sprite * optionitem = Sprite::createWithTexture(optionscreenTexture, Rect(0,304,128,64));
    Sprite * option_sfx_bar = Sprite::createWithTexture(optionscreenTexture, Rect(192,400,64,16));
    Sprite * option_music_bar = Sprite::createWithTexture(optionscreenTexture, Rect(64,480,64,16));
    Sprite * option_mp_opacity_bar = Sprite::createWithTexture(optionscreenTexture, Rect(192,400,64,16));
    optionmenu->setPosition(221,143);
    optionitem->setPosition(85,100);
    optioncursor->setPosition(25,100);
    optionscreen->setOpacity(0x7f);
    option_sfx_bar->setPosition(175,124);
    option_music_bar->setPosition(175,100);
    option_mp_opacity_bar->setPosition(175,76);
    optionmenu->addChild(optioncursor,1,"optioncursor");
    optionmenu->addChild(optionitem,1);
    optionmenu->addChild(option_sfx_bar,1,"option_sfx_bar");
    optionmenu->addChild(option_music_bar,1,"option_music_bar");
    optionmenu->addChild(option_mp_opacity_bar,1,"option_mapopacity_bar");
    optionscreen->setPosition(221,143);
    optionscreen->addChild(optionmenu,0,"optionmenu");
    addChild(optionscreen,7);
    optionscreen->setVisible(false);
    
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
    
    SimpleAudioEngine::getInstance()->setEffectsVolume((float)model.sfx_volume/25.0);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)model.music_volume/25.0);
    
    Texture2D * pickup_heart_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png");
    Sprite * pickup_heart_plusfull = Sprite::createWithTexture(pickup_heart_texture, Rect(0,0,32,32));
    Sprite * pickup_heart_plushalf = Sprite::createWithTexture(pickup_heart_texture, Rect(32,0,32,32));
    Sprite * pickup_heart_maxplusfull = Sprite::createWithTexture(pickup_heart_texture, Rect(0,32,32,32));
    Sprite * pickup_heart_maxplushalf = Sprite::createWithTexture(pickup_heart_texture, Rect(32,32,32,32));
    pickup_heart_plusfull -> setPosition(221,143);
    pickup_heart_plushalf -> setPosition(241,143);
    pickup_heart_maxplusfull -> setPosition(261,143);
    pickup_heart_maxplushalf -> setPosition(281,143);
    this->addChild(pickup_heart_plusfull,3);
    this->addChild(pickup_heart_plushalf,3);
    this->addChild(pickup_heart_maxplusfull,3);
    this->addChild(pickup_heart_maxplushalf,3);
    Texture2D * pickup_speedup_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/items/collectibles/collectibles_012_magicmushroom.png");
    Sprite * pickup_speedup = Sprite::createWithTexture(pickup_speedup_texture, Rect(0,0,32,32));
    pickup_speedup-> setPosition(301,143);
    this->addChild(pickup_speedup,3);
    
    //Boss血条贴图，zorder 为7，两张以一定比例横向拼接，注意 boss 死亡后销毁血条
    Texture2D * bosshealthbar = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/ui_bosshealthbar.png");
    Sprite * bosshealthbarfull = Sprite::createWithTexture(bosshealthbar, Rect(0,0,150,32));
    Sprite * bosshealthbarempty = Sprite::createWithTexture(bosshealthbar, Rect(0,32,150,32));
    bosshealthbarfull -> setPosition(221,223);
    bosshealthbarempty -> setPosition(221,183);
    this->addChild(bosshealthbarfull,7);
    this->addChild(bosshealthbarempty,7);
    
    scheduleUpdate();
    return true;
}

void RoomScene::set_event_listener(IRoomSceneListener * listener)
{
    this->listener_ = listener;

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
    if (model.game_stat == 0) {
        //开始
        if (Director::getInstance()->getRunningScene()->getPhysicsWorld() != nullptr) {
            Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0);
        }
        if (pausescreen->isVisible()) {
            pausescreen->setVisible(false);
            auto pausescreenmovein = MoveTo::create(0.2, Vec2(-250, 143));
            pausescreen->getChildByName("pausemenu")->runAction(pausescreenmovein);
            model.paused_menu_generated_flag = 0;
        }
        if (model.bomb) {
            cout << "bomb placed" << endl;
            //TODO 炸弹爆炸动画，爆炸范围判定，销毁
            bomb->setPosition(player->getPositionX(), player->getPositionY());
            bomb->setVisible(true);
            model.bomb = false;
        }

        //tear倒计时和消失
        for (auto it = tears_.begin(); it != tears_.end();) {
            if ((*it)->getTearExistTime() == 0) {
                Texture2D *temp_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/tears.png");
                SpriteFrame *temp_frame = SpriteFrame::createWithTexture(temp_texture, Rect(0, 32, 32, 32));
                auto temp_sprite = Sprite::createWithSpriteFrame(temp_frame);
                temp_sprite->setPosition((*it)->getPosition());
                addChild(temp_sprite, 3);
                SimpleAudioEngine::getInstance()->playEffect("res/sfx/splatter 0.wav",false);
                (*it)->removeFromParent();
                //
                const auto poof_ani = AnimationCache::getInstance()->getAnimation((*it)->getPoofAnimation());
                const auto poof_anim = Animate::create(poof_ani);
                const auto poof_animate = Sequence::create(poof_anim, RemoveSelf::create(true), NULL);
                temp_sprite->runAction(poof_animate);
                //SimpleAudioEngine::end();
                it = tears_.erase(it);
            }
            else {
                (*it)->setTearExistTime((*it)->getTearExistTime() - 1);
                ++it;
            }
        }

        //monster移动和死亡
        for (auto it = monsters_.begin(); it != monsters_.end(); )
        {
            if ((*it)->getHealth() <= 0) {
                //血量<0死亡了
                Texture2D *temp_texture = Director::getInstance()->getTextureCache()->addImage("res/gfx/tears.png");
                SpriteFrame *temp_frame = SpriteFrame::createWithTexture(temp_texture, Rect(0, 32, 32, 32));
                auto temp_sprite = Sprite::createWithSpriteFrame(temp_frame);
                temp_sprite->setPosition((*it)->getPosition());
                addChild(temp_sprite, 3);

                (*it)->removeFromParent();

                const auto dead_ani = AnimationCache::getInstance()->getAnimation((*it)->getDeadAnimation());
                const auto dead_anim = Animate::create(dead_ani);
                const auto dead_animate = Sequence::create(dead_anim, RemoveSelf::create(true), NULL);
                temp_sprite->runAction(dead_animate);
                it = monsters_.erase(it);
            }
            else {
                //移动
                if ((*it)->getColClog() != 0) {
                    (*it)->setColClog((*it)->getColClog() - 1);
                    if ((*it)->getColClog() == 0) {
                        (*it)->move(5);
                    }
                }
                else {
                    (*it)->moveStrategy(room_vm_);
                }
                //开火
                int nowtears_Size = tears_.size();
                (*it)->fireStrategy(tears_);
                for (int i = nowtears_Size; i < tears_.size(); i++) {
                    addChild(tears_.at(i));
                }
				it++;
            }
        }

        //player移动	
        const auto he = PlayerService::getInstance()->getHealth();
		//测试是否能够解决体位问题
		player->setRotation(0);
        if (he > 0) {
            if (player->getColClog() != 0) {
                player->setColClog(player->getColClog() - 1);
                if (player->getColClog() == 0) {
                    player->getPhysicsBody()->setVelocity(Vec2(0, 0));
                }
            }
            else {
                player->move(model.walk_direction, model.tear_direction);
            }
            //player无敌时间的倒计时
            if (player->getInvincibleTime() > 0) {
				player->getPhysicsBody()->setCollisionBitmask(0xF9); //1111_1001(F9)
				player->getPhysicsBody()->setContactTestBitmask(0xC0); //1100_0000(C0)
                player->setInvincibleTime(player->getInvincibleTime() - 1);
            }
			else {
				player->getPhysicsBody()->setCollisionBitmask(0xFF); //1111_1111(FF)
				player->getPhysicsBody()->setContactTestBitmask(0xCE); //1100_1110(CE)
			}
        }
        else {
            //player血量为0，Issac死亡，添加动画和游戏结束界面？
            log("DEAD");
            //TODO播放死亡动画，放完再将 model 设为结束
            //设置 game status
            player->dead();
            model.game_stat = 2;
        }

        //添加player的射击监听
        if (model.tear_direction == 5) {
            this->schedule(schedule_selector(RoomScene::fire), 0.4, 65536, 0.001);
        }

        //玩家血量显示
        auto spriteCache = SpriteFrameCache::getInstance();
        //每次刷新
        healthbar->removeAllChildren();

        int heart_x = 0;
        for (int i = 0; i< he / 2; ++i) {
            Sprite * heart = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("fullheartcache"));
            heart->setPosition(heart_x, 0);
            healthbar->addChild(heart, 1);
            heart_x += 16;
        }
        if (he % 2 != 0) {
            Sprite * hfheart = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("halfheartcache"));
            hfheart->setPosition(heart_x, 0);
            healthbar->addChild(hfheart, 1);
        }
        
        if(monsters_.size() == 0 && !door_removed && doors_.size()!= 0){
            for(int i = 0; i < doors_.size(); i++){
                doors_.at(i)->getChildByName("door_piece_left")->runAction(Sequence::create(FadeOut::create(0.5),NULL));
                doors_.at(i)->getChildByName("door_piece_right")->runAction(Sequence::create(FadeOut::create(0.5),NULL));
            }
            door_removed = true;
        }
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
        if(model.option_display == 1){
            optionscreen->setVisible(true);
            switch (model.option_menu_cursor) {
                case 0:
                    optionscreen->getChildByName("optionmenu")->getChildByName("optioncursor")->runAction(MoveTo::create(0, Vec2(25, 124)));
                    break;
                case 1:
                    optionscreen->getChildByName("optionmenu")->getChildByName("optioncursor")->runAction(MoveTo::create(0, Vec2(25, 100)));
                    break;
                case 2:
                    optionscreen->getChildByName("optionmenu")->getChildByName("optioncursor")->runAction(MoveTo::create(0, Vec2(25, 76)));
                    break;
                default:
                    break;
            }
            //根据 option 值更新 bar
            SimpleAudioEngine::getInstance()->setEffectsVolume((float)model.sfx_volume/25.0);
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)model.music_volume/25.0);
            string sfx_volume_string = "sfx" + to_string(model.sfx_volume);
            optionscreen->getChildByName("optionmenu")->removeChildByName("option_sfx_bar");
            Sprite * option_sfx_bar = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfx_volume_string));
            option_sfx_bar->setPosition(175,124);
            optionscreen->getChildByName("optionmenu")->addChild(option_sfx_bar,1,"option_sfx_bar");
            
            string music_volume_string = "music" + to_string(model.music_volume);
            optionscreen->getChildByName("optionmenu")->removeChildByName("option_music_bar");
            Sprite * option_music_bar = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(music_volume_string));
            option_music_bar->setPosition(175,100);
            optionscreen->getChildByName("optionmenu")->addChild(option_music_bar,1,"option_music_bar");
            
            string mapopacity_string = "mapopacity" + to_string(model.map_opacity);
            optionscreen->getChildByName("optionmenu")->removeChildByName("option_mapopacity_bar");
            Sprite * option_mapopacity_bar = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(mapopacity_string));
            option_mapopacity_bar->setPosition(175,76);
            optionscreen->getChildByName("optionmenu")->addChild(option_mapopacity_bar,1,"option_mapopacity_bar");
        } else {
            optionscreen->setVisible(false);
        }
	}
    else{
        Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
        if(model.dead_menu_generated_flag == 0) {
            this->unschedule(schedule_selector(RoomScene::fire));
            deadscreen->setVisible(true);
            model.dead_menu_generated_flag = 1;
            SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
            SimpleAudioEngine::getInstance()->playEffect("res/sfx/isaac dies new.wav",false);
            SimpleAudioEngine::getInstance()->playBackgroundMusic("res/music/you died.wav",true);
        }
        this->stopAllActions();
        
    }
	//   std::cout << "Test: "<<model.paused << " " << model.paused_menu_generated_flag << " " << model.paused_menu_cursor << endl;
}

void RoomScene::updatehealth(float dt){
    
}

void RoomScene::set_model(RoomSceneModel model)
{
    this->model = model;
}

void RoomScene::fire(float dt){

	//Issac发射tear
    SimpleAudioEngine::getInstance()->playEffect("res/sfx/tear fire 4.wav",false);
//    SimpleAudioEngine::getInstance()->playEffect("res/sfx/isaac dies new.wav",false);//注意：这句话有鬼畜效果
	tears_.pushBack(player->Fire(model.tear_direction));
	addChild(tears_.at(tears_.size() - 1),4);
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
    
    Texture2D * mtpoofTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/effects/effect_003_bloodtear.png");
    const auto mtframe0 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(0, 0, 64, 64));
    const auto mtframe1 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(64, 0, 64, 64));
    const auto mtframe2 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(128, 0, 64, 64));
    const auto mtframe3 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(192, 0, 64, 64));
    const auto mtframe4 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(0, 64, 64, 64));
    const auto mtframe5 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(64, 64, 64, 64));
    const auto mtframe6 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(128, 64, 64, 64));
    const auto mtframe7 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(192, 64, 64, 64));
    const auto mtframe8 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(0, 128, 64, 64));
    const auto mtframe9 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(64, 128, 64, 64));
    const auto mtframe10 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(128, 128, 64, 64));
    const auto mtframe11 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(192, 128, 64, 64));
    const auto mtframe12 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(0, 192, 64, 64));
    const auto mtframe13 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(64, 192, 64, 64));
    const auto mtframe14 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(128, 192, 64, 64));
    const auto mtframe15 = SpriteFrame::createWithTexture(mtpoofTexture, Rect(192, 192, 64, 64));
    
    fcache->addSpriteFrame(mtframe0, "mt_frame0");
    fcache->addSpriteFrame(mtframe1, "mt_frame1");
    fcache->addSpriteFrame(mtframe2, "mt_frame2");
    fcache->addSpriteFrame(mtframe3, "mt_frame3");
    fcache->addSpriteFrame(mtframe4, "mt_frame4");
    fcache->addSpriteFrame(mtframe5, "mt_frame5");
    fcache->addSpriteFrame(mtframe6, "mt_frame6");
    fcache->addSpriteFrame(mtframe7, "mt_frame7");
    fcache->addSpriteFrame(mtframe8, "mt_frame8");
    fcache->addSpriteFrame(mtframe9, "mt_frame9");
    fcache->addSpriteFrame(mtframe10, "mt_frame10");
    fcache->addSpriteFrame(mtframe11, "mt_frame11");
    fcache->addSpriteFrame(mtframe12, "mt_frame12");
    fcache->addSpriteFrame(mtframe13, "mt_frame13");
    fcache->addSpriteFrame(mtframe14, "mt_frame14");
    fcache->addSpriteFrame(mtframe15, "mt_frame15");
    
    Texture2D * texture_heart = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/ui_hearts.png");
    const auto fullheartcache = SpriteFrame::createWithTexture(texture_heart, Rect(0,0,16,16));
    const auto halfheartcache = SpriteFrame::createWithTexture(texture_heart, Rect(16,0,16,16));
    fcache->addSpriteFrame(fullheartcache, "fullheartcache");
    fcache->addSpriteFrame(halfheartcache, "halfheartcache");
    
    Texture2D * optionscreenTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/main menu/optionsmenudark.png");
    const auto sfx0 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,400,64,16));
    const auto sfx1 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,384,64,16));
    const auto sfx2 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,368,64,16));
    const auto sfx3 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,352,64,16));
    const auto sfx4 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,336,64,16));
    const auto sfx5 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,320,64,16));
    const auto sfx6 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,304,64,16));
    const auto sfx7 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,288,64,16));
    const auto sfx8 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,272,64,16));
    const auto sfx9 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,256,64,16));
    const auto sfx10 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,240,64,16));
    fcache->addSpriteFrame(sfx0, "sfx0");
    fcache->addSpriteFrame(sfx1, "sfx1");
    fcache->addSpriteFrame(sfx2, "sfx2");
    fcache->addSpriteFrame(sfx3, "sfx3");
    fcache->addSpriteFrame(sfx4, "sfx4");
    fcache->addSpriteFrame(sfx5, "sfx5");
    fcache->addSpriteFrame(sfx6, "sfx6");
    fcache->addSpriteFrame(sfx7, "sfx7");
    fcache->addSpriteFrame(sfx8, "sfx8");
    fcache->addSpriteFrame(sfx9, "sfx9");
    fcache->addSpriteFrame(sfx10, "sfx10");
    
    const auto music0 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,400,64,16));
    const auto music1 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,384,64,16));
    const auto music2 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,368,64,16));
    const auto music3 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,352,64,16));
    const auto music4 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,336,64,16));
    const auto music5 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,320,64,16));
    const auto music6 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,304,64,16));
    const auto music7 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,288,64,16));
    const auto music8 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,272,64,16));
    const auto music9 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,256,64,16));
    const auto music10 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,240,64,16));
    fcache->addSpriteFrame(music0, "music0");
    fcache->addSpriteFrame(music1, "music1");
    fcache->addSpriteFrame(music2, "music2");
    fcache->addSpriteFrame(music3, "music3");
    fcache->addSpriteFrame(music4, "music4");
    fcache->addSpriteFrame(music5, "music5");
    fcache->addSpriteFrame(music6, "music6");
    fcache->addSpriteFrame(music7, "music7");
    fcache->addSpriteFrame(music8, "music8");
    fcache->addSpriteFrame(music9, "music9");
    fcache->addSpriteFrame(music10, "music10");
    
    const auto mapopacity0 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,400,64,16));
    const auto mapopacity1 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,384,64,16));
    const auto mapopacity2 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,368,64,16));
    const auto mapopacity3 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,352,64,16));
    const auto mapopacity4 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,336,64,16));
    const auto mapopacity5 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,320,64,16));
    const auto mapopacity6 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,304,64,16));
    const auto mapopacity7 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,288,64,16));
    const auto mapopacity8 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,272,64,16));
    const auto mapopacity9 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,256,64,16));
    const auto mapopacity10 = SpriteFrame::createWithTexture(optionscreenTexture, Rect(192,240,64,16));
    fcache->addSpriteFrame(mapopacity0, "mapopacity0");
    fcache->addSpriteFrame(mapopacity1, "mapopacity1");
    fcache->addSpriteFrame(mapopacity2, "mapopacity2");
    fcache->addSpriteFrame(mapopacity3, "mapopacity3");
    fcache->addSpriteFrame(mapopacity4, "mapopacity4");
    fcache->addSpriteFrame(mapopacity5, "mapopacity5");
    fcache->addSpriteFrame(mapopacity6, "mapopacity6");
    fcache->addSpriteFrame(mapopacity7, "mapopacity7");
    fcache->addSpriteFrame(mapopacity8, "mapopacity8");
    fcache->addSpriteFrame(mapopacity9, "mapopacity9");
    fcache->addSpriteFrame(mapopacity10, "mapopacity10");
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
	//tag=5,6,7,8是左、上、右、下4个门
	//tag=9物品collectable
	if (nodeA && nodeB)
	{
        //if (tagA == 1 && tagB == 2 && nodeA->getInvincibleTime() == 0)
		if (tagA == 1 && tagB == 2)
		{
            //Issac被monster碰到，受伤
            nodeA->setHealth(nodeA->getHealth() - nodeB->getAttack());
            //Service更新血量
            PlayerService::getInstance()->decreaseHealth(nodeB->getAttack());
            //Issac进入短暂无敌状态
            nodeA->setInvincibleTime(20);
            //受伤动画
            log("Issac Health:%d", nodeA->getHealth());
            player->hurt();
        }
        //怪物和眼泪碰撞
        if (tagA == 2 && (tagB == 3 || tagB == 4)) {
            nodeA->setHealth(nodeA->getHealth() - nodeB->getAttack());
        }
        //Issac和怪物眼泪碰撞
        if (tagA == 1 && tagB == 3 && nodeA->getInvincibleTime() == 0) {
            nodeA->setHealth(nodeA->getHealth() - nodeB->getAttack());
            PlayerService::getInstance()->decreaseHealth(nodeB->getAttack());
            //Issac进入短暂无敌状态
            if (tagA == 1) nodeA->setInvincibleTime(20);
            //添加受伤动画
            player->hurt();
        }
		//Issac和门的碰撞
		if (tagA == 1 && (tagB>=5 && tagB<=8) && monsters_.empty()) {
			//出门了！
			switch (tagB)
			{
            case(5):
                {
                    log("left go out!"); 
                    const auto room = RoomSceneController::createScene(RoomService::getInstance()->get_left_room_id());
                    TransitionScene* tx = TransitionSlideInL::create(0.1, room);

                    Director::getInstance()->replaceScene(tx);
                    break;
                }
            case(6):
                {
                    log("up go out!"); 
                    const auto room = RoomSceneController::createScene(RoomService::getInstance()->get_up_room_id());
                    TransitionScene* tx = TransitionSlideInT::create(0.1, room);
                    Director::getInstance()->replaceScene(tx);
                    break;
                }
            case(7):
                {
                    log("right go out?!"); 
                    const auto room = RoomSceneController::createScene(RoomService::getInstance()->get_right_room_id());
                    TransitionScene* tx = TransitionSlideInR::create(0.1, room);
                    Director::getInstance()->replaceScene(tx);
                    break;
                }
            case(8):
                {
                    log("down go out!"); 
                    const auto room = RoomSceneController::createScene(RoomService::getInstance()->get_down_room_id());
                    TransitionScene* tx = TransitionSlideInB::create(0.1, room);
                    Director::getInstance()->replaceScene(tx);
                    break;
                }
			default: break;
			}
			
		}

		//眼泪碰撞后消失
		if (tagA == 3 || tagA==4) nodeA->setTearExistTime(0);
		if (tagB == 3 || tagB==4) nodeB->setTearExistTime(0);
	}

	//bodies can collide
	return true;
}
