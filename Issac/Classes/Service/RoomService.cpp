#include "RoomService.h"
#include "cocos2d.h"
#include <string>
#include <vector>

using namespace std;
USING_NS_CC;

/**
 * \brief 单线程
 * \return
 */
RoomService *RoomService::getInstance()
{
    if (inst_ == nullptr)
    {
        inst_ = new (std::nothrow) RoomService();
        CCASSERT(inst_, "FATAL: Not enough memory");
    }

    return inst_;
}

/**
 * \brief 获取房间信息
 * \param room_id 房间ID，必须要大于0
 * \return 渲染房间所需要的全部信息
 */
RoomViewModel RoomService::enter_room(const int room_id)
{
    if (room_id <= 0)
    {
        throw runtime_error("Room Not Found");
    }

    auto room_view_model = store_[room_id];
    //访问enter函数一次，就表示这个房间已经进入过
    room_map_[room_id].visited = true;

    if (room_id == 1 && current_room_id_ == 0) //第一个房间，Issac位置在中间
    {
        room_view_model.setPlayerPos(GRID_WIDTH_HALF, GRID_HEIGHT_HALF);
        current_room_id_ = 1;
    }
    else
    {
        const auto prev_id = current_room_id_;

        const auto r_map = room_map_[room_id];

        if (r_map.left_room_id == prev_id) //从左门进入
        {
            room_view_model.setPlayerPos(0, GRID_HEIGHT_HALF);
        }
        else if (r_map.up_room_id == prev_id) //从上门进入
        {
            room_view_model.setPlayerPos(GRID_WIDTH_HALF, GRID_HEIGHT - 1);
        }
        else if (r_map.right_room_id == prev_id) //从右门进入
        {
            room_view_model.setPlayerPos(GRID_WIDTH - 1, GRID_HEIGHT_HALF);
        }
        else if (r_map.down_room_id == prev_id) //从下门进入
        {
            room_view_model.setPlayerPos(GRID_WIDTH_HALF, 0);
        }

        current_room_id_ = room_id;
        build_vm_from_room(r_map);
    }

    return room_view_model;
}

MiniMapViewModel RoomService::get_mini_map(int room_id)
{
    if (room_id <= 0)
    {
        throw runtime_error("Room Not Found");
    }

    //初始化5×5的小地图
    vector<vector<int>> masks;
    for (size_t i = 0; i < 5; i++)
    {
        vector<int> row;

        for (size_t j = 0; j < 5; j++)
        {
            row.push_back(-1);
        }
        masks.push_back(row);
    }

    //-1表示空
    //其余数字和room_type定义一致
    //-1 -1 -1 -1 -1
    //-1 -1 -1 -1 -1
    //-1  2 -2  2 -1
    //-1 -1 -1 -1 -1
    //-1 -1 -1 -1 -1
    //中间的房间永远是“亮”记为-2

    //获取当前房间的四周
    const auto m = room_map_[room_id];
    const auto l = m.left_room_id;
    const auto r = m.right_room_id;
    const auto u = m.up_room_id;
    const auto d = m.down_room_id;

    masks[2][2] = -2;

    if (l > 0) //左边有房间
    {
        const auto ll = room_map_[l];
        const auto l_type = ll.current_room_type;
        masks[2][1] = l_type;

        //两层遍历
        if (ll.left_room_id > 0) //左边有房间
        {
            const auto ll_l = room_map_[ll.left_room_id];
            if (ll_l.visited)
            {
                masks[2][0] = ll_l.current_room_type;
            }
        }

        if (ll.up_room_id > 0) //上边有房间
        {
            const auto ll_l = room_map_[ll.up_room_id];
            if (ll_l.visited)
            {
                masks[1][1] = ll_l.current_room_type;
            }
        }

        if (ll.down_room_id > 0) //下边有房间
        {
            const auto ll_l = room_map_[ll.down_room_id];
            if (ll_l.visited)
            {
                masks[3][1] = ll_l.current_room_type;
            }
        }
    }

    if (u > 0) //上边有房间
    {
        const auto ll = room_map_[u];
        const auto l_type = ll.current_room_type;
        masks[1][2] = l_type;

        //两层遍历
        if (ll.left_room_id > 0) //左边有房间
        {
            const auto ll_l = room_map_[ll.left_room_id];
            if (ll_l.visited)
            {
                masks[1][1] = ll_l.current_room_type;
            }
        }

        if (ll.up_room_id > 0) //上边有房间
        {
            const auto ll_l = room_map_[ll.up_room_id];
            if (ll_l.visited)
            {
                masks[0][2] = ll_l.current_room_type;
            }
        }

        if (ll.right_room_id > 0) //右边有房间
        {
            const auto ll_l = room_map_[ll.right_room_id];
            if (ll_l.visited)
            {
                masks[1][3] = ll_l.current_room_type;
            }
        }
    }

    if (r > 0) //右边有房间
    {
        const auto ll = room_map_[r];
        const auto l_type = ll.current_room_type;
        masks[2][3] = l_type;

        //两层遍历
        if (ll.right_room_id > 0) //右边有房间
        {
            const auto ll_l = room_map_[ll.right_room_id];
            if (ll_l.visited)
            {
                masks[2][4] = ll_l.current_room_type;
            }
        }

        if (ll.up_room_id > 0) //上边有房间
        {
            const auto ll_l = room_map_[ll.up_room_id];
            if (ll_l.visited)
            {
                masks[1][3] = ll_l.current_room_type;
            }
        }

        if (ll.down_room_id > 0) //下边有房间
        {
            const auto ll_l = room_map_[ll.down_room_id];
            if (ll_l.visited)
            {
                masks[3][3] = ll_l.current_room_type;
            }
        }
    }

    if (d > 0) //下边有房间
    {
        const auto ll = room_map_[d];
        const auto l_type = ll.current_room_type;
        masks[3][2] = l_type;

        //两层遍历
        if (ll.left_room_id > 0) //左边有房间
        {
            const auto ll_l = room_map_[ll.left_room_id];
            if (ll_l.visited)
            {
                masks[3][1] = ll_l.current_room_type;
            }
        }

        if (ll.right_room_id > 0) //右边有房间
        {
            const auto ll_l = room_map_[ll.right_room_id];
            if (ll_l.visited)
            {
                masks[3][3] = ll_l.current_room_type;
            }
        }

        if (ll.down_room_id > 0) //下边有房间
        {
            const auto ll_l = room_map_[ll.down_room_id];
            if (ll_l.visited)
            {
                masks[4][2] = ll_l.current_room_type;
            }
        }
    }

    auto mini = MiniMapViewModel();
    mini.setMiniMask(masks);
    return mini;
}

int RoomService::get_init_room_id() const
{
    return init_room_id_;
}

int RoomService::get_current_room_id() const
{
    return current_room_id_;
}

int RoomService::get_left_room_id()
{
    const auto r = room_map_[current_room_id_];
    return r.left_room_id;
}

int RoomService::get_up_room_id()
{
    const auto r = room_map_[current_room_id_];
    return r.up_room_id;
}

int RoomService::get_right_room_id()
{
    const auto r = room_map_[current_room_id_];
    return r.right_room_id;
}

int RoomService::get_down_room_id()
{
    const auto r = room_map_[current_room_id_];
    return r.down_room_id;
}

bool RoomService::is_init_room() const
{
    return current_room_id_ == init_room_id_;
}

/**
 * \brief 必须在使用Service前调用Init()方法
 */
void RoomService::init()
{
    init_room_id_ = 1;
    current_room_id_ = 0;
    room_map_.clear();
    store_.clear();

    //初始房间
    auto room__ = Room();
    room__.current_room_id = 1;
    room__.left_room_id = 2;
    room__.up_room_id = 0;
    room__.right_room_id = 3;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 0;
    room__.current_barrier_type = 0;
    room_map_[1] = room__;

    //怪物房间
    room__ = Room();
    room__.current_room_id = 2;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 1;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 15;
    room__.current_barrier_type = 0;
    room_map_[2] = room__;

    room__ = Room();
    room__.current_room_id = 3;
    room__.left_room_id = 1;
    room__.up_room_id = 4;
    room__.right_room_id = 0;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 6;
    room__.current_barrier_type = 1;
    room_map_[3] = room__;

    room__ = Room();
    room__.current_room_id = 4;
    room__.left_room_id = 0;
    room__.up_room_id = 5;
    room__.right_room_id = 0;
    room__.down_room_id = 3;
    room__.visited = false;
    room__.current_room_type = 1;
    room__.current_barrier_type = 0;
    room_map_[4] = room__;

    room__ = Room();
    room__.current_room_id = 5;
    room__.left_room_id = 6;
    room__.up_room_id = 0;
    room__.right_room_id = 10;
    room__.down_room_id = 4;
    room__.visited = false;
    room__.current_room_type = 2;
    room__.current_barrier_type = 0;
    room_map_[5] = room__;

    room__ = Room();
    room__.current_room_id = 6;
    room__.left_room_id = 0;
    room__.up_room_id = 7;
    room__.right_room_id = 5;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 3;
    room__.current_barrier_type = 0;
    room_map_[6] = room__;

    room__ = Room();
    room__.current_room_id = 7;
    room__.left_room_id = 9;
    room__.up_room_id = 8;
    room__.right_room_id = 0;
    room__.down_room_id = 6;
    room__.visited = false;
    room__.current_room_type = 2;
    room__.current_barrier_type = 0;
    room_map_[7] = room__;

    room__ = Room();
    room__.current_room_id = 8;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 0;
    room__.down_room_id = 7;
    room__.visited = false;
    room__.current_room_type = 5;
    room__.current_barrier_type = 0;
    room_map_[8] = room__;

    room__ = Room();
    room__.current_room_id = 9;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 7;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 8;
    room__.current_barrier_type = 0;
    room_map_[9] = room__;

    room__ = Room();
    room__.current_room_id = 10;
    room__.left_room_id = 5;
    room__.up_room_id = 0;
    room__.right_room_id = 11;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 6;
    room__.current_barrier_type = 0;
    room_map_[10] = room__;

    room__ = Room();
    room__.current_room_id = 11;
    room__.left_room_id = 10;
    room__.up_room_id = 12;
    room__.right_room_id = 13;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 7;
    room__.current_barrier_type = 0;
    room_map_[11] = room__;

    room__ = Room();
    room__.current_room_id = 12;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 0;
    room__.down_room_id = 11;
    room__.visited = false;
    room__.current_room_type = 2;
    room__.current_barrier_type = 0;
    room_map_[12] = room__;

    //Boss
    room__ = Room();
    room__.current_room_id = 13;
    room__.left_room_id = 11;
    room__.up_room_id = 0;
    room__.right_room_id = 0;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 15;
    room__.current_barrier_type = 0;
    room_map_[13] = room__;

    build_vm_from_room_map();
}

void RoomService::save_room_scene_state(RoomSceneModel room)
{
    saved_room_ = room;
}

RoomSceneModel RoomService::get_prev_room_scene() const
{
    return saved_room_;
}

void RoomService::increase_mini_opacity()
{
    if (mini_opacity != 10)
    {
        mini_opacity++;
    }
}

void RoomService::decrease_mini_opacity()
{
    if (mini_opacity != 0)
    {
        mini_opacity--;
    }
}

char RoomService::get_real_mini_opacity() const
{
    return mini_opacity * 25 + 5;
}

float RoomService::get_real_sfx_volume() const
{
    return static_cast<float>(sfx_volume) / 25.0;
}

float RoomService::get_real_music_volume() const
{
    return static_cast<float>(music_volume) / 25.0;
}

/**
 * \brief 初始化所有房间信息,创建Service后必须调用init()方法
 */
RoomService::RoomService()
{
    init_room_id_ = 1;
    current_room_id_ = 0;

    music_volume = 3;  //0~10
    sfx_volume = 5;    //0~10
    mini_opacity = 10; //0~10

    win_ = false;
    //init();
}

string RoomService::get_doorstyle_from_room_type(int room_type)
{
    if (room_type >= 0 && room_type < 8) //普通门
    {
        return "res/gfx/grid/door_01_normaldoor.png";
    }
    if (room_type >= 8 && room_type < 15) //宝藏门
    {
        return "res/gfx/grid/door_02_treasureroomdoor.png";
    }
    if (room_type >= 15 && room_type < 18) //Boss门
    {
        return "res/gfx/grid/door_09_bossambushroomdoor.png";
    }
    if (room_type >= 18 && room_type < 20) //Boss门
    {
        return "res/gfx/grid/door_10_bossroomdoor.png";
    }

    //其他门
    return "res/gfx/grid/door_04_selfsacrificeroomdoor.png";
}

string RoomService::get_groundstyle_from_room_type(int room_type)
{
    const int m = room_type % 5;
    switch (m)
    {
    case 0:
        return "res/gfx/backdrop/01_basement.png";
    case 1:
        return "res/gfx/backdrop/02_cellar.png";
    case 2:
        return "res/gfx/backdrop/03_caves.png";
    case 3:
        return "res/gfx/backdrop/04_catacombs.png";
    case 4:
        return "res/gfx/backdrop/05_depths.png";
    default:
        return "res/gfx/backdrop/01_basement.png";
        ;
    }
}

void RoomService::build_vm_from_room_map()
{
    for (auto it = room_map_.begin(); it != room_map_.end(); ++it)
    {
        const auto room_m = (*it).second;
        build_vm_from_room(room_m);
    }
}

void RoomService::build_vm_from_room(Room room_m)
{
    const auto room_id = room_m.current_room_id;
    const auto room_type = room_m.current_room_type;
    const auto barrier_type = room_m.current_barrier_type;

    auto room_ = RoomViewModel::createRoomViewModel(room_type, room_m.visited, barrier_type);

    int doors_id[] = {room_m.left_room_id, room_m.up_room_id, room_m.right_room_id, room_m.down_room_id};

    auto door_ = vector<int>();
    auto door_style = vector<string>();

    for (int door_id : doors_id)
    {
        door_.push_back(door_id);
        door_style.emplace_back(get_doorstyle_from_room_type(room_map_[door_id].current_room_type));
    }
    room_.setDoorEnable(door_);
    room_.setDoorStyle(door_style);
    room_.setGroundStyle(get_groundstyle_from_room_type(room_type));

    store_[room_id] = room_;
}

RoomService *RoomService::inst_ = nullptr;
