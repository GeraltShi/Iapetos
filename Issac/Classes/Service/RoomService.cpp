#include "RoomService.h"
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
        current_room_id_ = room_id;
        build_vm_from_room(r_map);//构建下一次进入的房间

        if (room_map_[room_id].item_taken)//修复捡过的房间要第二次进入才消失的bug
        {
            room_view_model = store_[room_id];//取出刚生成的房间
        }

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

void RoomService::set_item_taken(int room_id)
{
    room_map_[room_id].item_taken = true;
}

bool RoomService::is_init_room() const
{
    return current_room_id_ == init_room_id_;
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
    if (room_type >= 8 && room_type <= 20) //宝藏门
    {
        return "res/gfx/grid/door_02_treasureroomdoor.png";
    }
    //if (room_type >= 15 && room_type < 18) //Boss门
    //{
    //    return "res/gfx/grid/door_09_bossambushroomdoor.png";
    //}
    if (room_type >= 21) //Boss门
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
    const auto taken = room_m.item_taken;

    auto room_ = RoomViewModel::createRoomViewModel(room_type, room_m.visited, barrier_type,taken);

    int doors_id[] = { room_m.left_room_id, room_m.up_room_id, room_m.right_room_id, room_m.down_room_id };

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
    room_.setRoomId(room_id);

    store_[room_id] = room_;
}

RoomService *RoomService::inst_ = nullptr;



//roomType:0：初始房间
//roomType:1~7怪物房间。1:全Fatty,2:全Fly ,3:全Gaper ,4:全Spider,5:Spider+FattyFire,6:Fly+FlyFire,7:Fly+GaperFire
//roomType:8~20宝藏房间,宝藏房号20是测试用，会将所有宝藏放在房间里
//roomType:21+代表Boss房,21:Boss-flyDaddy
int randomRoom() {
    if (rand() % 20 == 0) {
        return rand() % 9 + 8;
    }
    else {
        return rand() % 7 + 1;
    }
}

void RoomService::createMaze()
{
    //产生地图,墙是MAZEWALL,不是墙的格子为roomID
    vector <int> block_row;
    vector <int> block_column;
    vector <int> block_direct;
    for (int i = 0; i < maze_size; i++)
        for (int j = 0; j < maze_size; j++)
            m[i][j] = MAZEWALL;
    int MyRoomID = 1;
    //加入起点
    int x_num = 0;
    int y_num = 0;
    m[0][0] = MyRoomID;
    MyRoomID++;
    if (x_num + 1 < maze_size) {
        block_row.push_back(x_num + 1);
        block_column.push_back(y_num);
        block_direct.push_back(MYDOWN);
    } //MYDOWN
    if (y_num + 1 < maze_size) {
        block_row.push_back(x_num);
        block_column.push_back(y_num + 1);
        block_direct.push_back(MYRIGHT);
    } //MYRIGHT
    if (x_num - 1 >= 0) {
        block_row.push_back(x_num - 1);
        block_column.push_back(y_num);
        block_direct.push_back(MYUP);
    } //MYUP
    if (y_num - 1 >= 0) {
        block_row.push_back(x_num);
        block_column.push_back(y_num - 1);
        block_direct.push_back(MYLEFT);
    } //MYLEFT

    while (block_row.size()) {//第一步压入两堵墙（起点右边和起点下面）进入循环
        int num = block_row.size();
        int randnum = rand() % num;//生成0-num-1之间的随机数，同时也是vector里的下标
        switch (block_direct[randnum]) {//选择一个方向进行后续操作，起始点 邻块 目标块 三块区域在同一直线上 随后移动到目标块的位置
        case MYDOWN: {
            x_num = block_row[randnum] + 1;
            y_num = block_column[randnum];
            break;
        }
        case MYRIGHT: {
            x_num = block_row[randnum];
            y_num = block_column[randnum] + 1;
            break;
        }
        case MYLEFT: {
            x_num = block_row[randnum];
            y_num = block_column[randnum] - 1;
            break;
        }
        case MYUP: {
            x_num = block_row[randnum] - 1;
            y_num = block_column[randnum];
            break;
        }
        }
        if (m[x_num][y_num] == MAZEWALL) {//目标块如果是墙
            if (m[block_row[randnum]][block_column[randnum]] == MAZEWALL) {
                m[block_row[randnum]][block_column[randnum]] = MyRoomID;//打通墙
                MyRoomID++;
            }
            if (m[x_num][y_num] == MAZEWALL) {
                m[x_num][y_num] = MyRoomID;//打通目标块
                MyRoomID++;
            }

            if (x_num + 1 < maze_size) {
                block_row.push_back(x_num + 1);
                block_column.push_back(y_num);
                block_direct.push_back(MYDOWN);
            } //MYDOWN
            if (y_num + 1 < maze_size) {
                block_row.push_back(x_num);
                block_column.push_back(y_num + 1);
                block_direct.push_back(MYRIGHT);
            } //MYRIGHT
            if (x_num - 1 >= 0) {
                block_row.push_back(x_num - 1);
                block_column.push_back(y_num);
                block_direct.push_back(MYUP);
            } //MYUP
            if (y_num - 1 >= 0) {
                block_row.push_back(x_num);
                block_column.push_back(y_num - 1);
                block_direct.push_back(MYLEFT);
            } //MYLEFT
        }
        block_row.erase(block_row.begin() + randnum);//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
        block_column.erase(block_column.begin() + randnum);
        block_direct.erase(block_direct.begin() + randnum);
    }
    if (rand() % 2) {
        if (m[maze_size - 2][maze_size - 1] == MAZEWALL) {
            m[maze_size - 2][maze_size - 1] = MyRoomID;
            MyRoomID++;
        }
    }
    else if (m[maze_size - 1][maze_size - 2] == MAZEWALL) {
        m[maze_size - 1][maze_size - 2] = MyRoomID;
        MyRoomID++;
    }
    if (m[maze_size - 1][maze_size - 1] == MAZEWALL) {
        m[maze_size - 1][maze_size - 1] = MyRoomID;
    }
}


void RoomService::init()
{
    createMaze();

    init_room_id_ = 1;
    current_room_id_ = 0;
    room_map_.clear();
    store_.clear();
    win_ = false;

    for (int i = 0; i < maze_size; i++) {
        for (int j = 0; j < maze_size; j++)
            if (m[i][j] != MAZEWALL)
            {
                auto room__ = Room();
                room__.current_room_id = m[i][j];
                if (inmaze(i - 1, j))
                    room__.left_room_id = m[i - 1][j];
                else
                    room__.left_room_id = 0;
                if (inmaze(i + 1, j))
                    room__.right_room_id = m[i + 1][j];
                else
                    room__.right_room_id = 0;
                if (inmaze(i, j + 1))
                    room__.up_room_id = m[i][j + 1];
                else
                    room__.up_room_id = 0;
                if (inmaze(i, j - 1))
                    room__.down_room_id = m[i][j - 1];
                else
                    room__.down_room_id = 0;
                room__.visited = false;
                room__.item_taken = false;
                if (i == 0 && j == 0) {
                    //初始房
                    room__.current_room_type = 0;
                    room__.current_barrier_type = 0;
                }
                else if (i == maze_size - 1 && j == maze_size - 1) {
                    room__.current_room_type = 21;
                    room__.current_barrier_type = 0;
                }
                else {
                    room__.current_room_type = randomRoom();
                    if (room__.current_room_type >= 8 && room__.current_room_type <= 20)
                        room__.current_barrier_type = 0;
                    else
                        room__.current_barrier_type = rand() % 3;
                }
                room_map_[m[i][j]] = room__;
            }
    }

    //在出生点边上添加一个宝物房
    if (m[1][0] != MAZEWALL) {
        room_map_[m[1][0]].current_room_type = rand() % 9 + 8;
        room_map_[m[1][0]].current_barrier_type = 0;
    }
    else {
        room_map_[m[0][1]].current_room_type = rand() % 9 + 8;
        room_map_[m[0][1]].current_barrier_type = 0;
    }


    build_vm_from_room_map();
}

void RoomService::initDebug()
{
    init_room_id_ = 1;
    current_room_id_ = 0;
    room_map_.clear();
    store_.clear();
    win_ = false;

    //初始房间
    auto room__ = Room();
    room__.current_room_id = 1;
    room__.left_room_id = 2;
    room__.up_room_id = 0;
    room__.right_room_id = 3;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.item_taken = false;
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
    room__.item_taken = false;
    room__.current_room_type = 21;
    room__.current_barrier_type = 0;
    room_map_[2] = room__;

    room__ = Room();
    room__.current_room_id = 3;
    room__.left_room_id = 1;
    room__.up_room_id = 4;
    room__.right_room_id = 0;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.item_taken = false;
    room__.current_room_type = 20;
    room__.current_barrier_type = 1;
    room_map_[3] = room__;

    room__ = Room();
    room__.current_room_id = 4;
    room__.left_room_id = 0;
    room__.up_room_id = 5;
    room__.right_room_id = 0;
    room__.down_room_id = 3;
    room__.visited = false;
    room__.item_taken = false;
    room__.current_room_type = 3;
    room__.current_barrier_type = 0;
    room_map_[4] = room__;

    room__ = Room();
    room__.current_room_id = 5;
    room__.left_room_id = 6;
    room__.up_room_id = 0;
    room__.right_room_id = 10;
    room__.down_room_id = 4;
    room__.visited = false;
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
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
    room__.item_taken = false;
    room__.current_room_type = 15;
    room__.current_barrier_type = 0;
    room_map_[13] = room__;

    build_vm_from_room_map();
}