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
RoomService * RoomService::getInstance()
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
    
    const Size size = Director::getInstance()->getWinSize();

    if (room_id == 1)//第一个房间，Issac位置在中间
    {
        room_view_model.setPlayerPos(6, 3);
        current_room_id_ = 1;
    }
    else
    {
        const auto prev_id = current_room_id_;

        const auto r_map = room_map_[room_id];

        if (r_map.left_room_id == prev_id)//从左门进入
        {
            room_view_model.setPlayerPos(0, 3);
        }
        else if (r_map.up_room_id == prev_id)//从上门进入
        {
            room_view_model.setPlayerPos(6, 6);
        }
        else if (r_map.up_room_id == prev_id)//从右门进入
        {
            room_view_model.setPlayerPos(12, 3);
        }
        else if (r_map.up_room_id == prev_id)//从下门进入
        {
            room_view_model.setPlayerPos(6 , 0);
        }

        current_room_id_ = room_id;
    }
    
    return room_view_model;

}

MiniMapViewModel RoomService::get_mini_map(int room_id)
{
    if (room_id <= 0)
    {
        throw runtime_error("Room Not Found");
    }

    vector<vector<int>> masks;
    vector<vector<string>> style_masks;
    for (size_t i = 0; i < 5; i++)
    {
        vector<int> row;
        vector<string> row2;

        for (size_t j = 0; j < 5; j++)
        {
            row.push_back(0);
            row2.emplace_back("");
        }
        masks.push_back(row);
        style_masks.push_back(row2);
    }

    //5*5
    //00200
    //00200
    //02120
    //00000
    //00000

    //0:没有房间
    //1:初始房间
    //2:普通房间
    //3:特殊房间1
    //4:特殊房间2
    //5:特殊房间3

    const auto m = room_map_[room_id];
    const auto l = m.left_room_id;
    const auto r = m.right_room_id;
    const auto u = m.up_room_id;
    const auto d = m.down_room_id;
  
    if (l>0)//左边有房间
    {
        const auto ll = room_map_[l];
        const auto l_type = ll.current_room_type;
        masks[2][1] = l_type;
        style_masks[2][1] = get_ministyle_from_room_type(l_type);
    }



    vector<int> row1;
    vector<int> row2;
    vector<int> row3;

    row1.push_back(0);
    row1.push_back(u == 0 ? 0 : 1);
    row1.push_back(0);

    row2.push_back(l == 0 ? 0 : 1);
    row2.push_back(1);//current
    row2.push_back(r == 0 ? 0 : 1);

    row3.push_back(0);
    row3.push_back(d == 0 ? 0 : 1);
    row3.push_back(0);

    masks.push_back(row1);
    masks.push_back(row2);
    masks.push_back(row3);

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


/**
 * \brief 初始化所有房间信息
 */
RoomService::RoomService()
{
    init_room_id_ = 1;
    current_room_id_ = 0;

    //初始房间
    auto room__ = Room();
    room__.current_room_id = 1;
    room__.left_room_id = 2;
    room__.up_room_id = 0;
    room__.right_room_id = 3;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 0;
    room_map_[1] = room__;

    //怪物房间
    room__ = Room();
    room__.current_room_id = 2;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 1;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 2;
    room_map_[2] = room__;

    room__ = Room();
    room__.current_room_id = 3;
    room__.left_room_id = 1;
    room__.up_room_id = 4;
    room__.right_room_id = 0;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 2;
    room_map_[3] = room__;

    room__ = Room();
    room__.current_room_id = 4;
    room__.left_room_id = 0;
    room__.up_room_id = 5;
    room__.right_room_id = 0;
    room__.down_room_id = 3;
    room__.visited = false;
    room__.current_room_type = 1;
    room_map_[4] = room__;

    room__ = Room();
    room__.current_room_id = 5;
    room__.left_room_id = 6;
    room__.up_room_id = 0;
    room__.right_room_id = 10;
    room__.down_room_id = 4;
    room__.visited = false;
    room__.current_room_type = 2;
    room_map_[5] = room__;

    room__ = Room();
    room__.current_room_id = 6;
    room__.left_room_id = 0;
    room__.up_room_id = 7;
    room__.right_room_id = 5;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 3;
    room_map_[6] = room__;

    room__ = Room();
    room__.current_room_id = 7;
    room__.left_room_id = 9;
    room__.up_room_id = 8;
    room__.right_room_id = 0;
    room__.down_room_id = 6;
    room__.visited = false;
    room__.current_room_type = 2;
    room_map_[7] = room__;

    room__ = Room();
    room__.current_room_id = 8;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 0;
    room__.down_room_id = 6;
    room__.visited = false;
    room__.current_room_type = 5;
    room_map_[8] = room__;

    room__ = Room();
    room__.current_room_id = 9;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 7;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 1;
    room_map_[9] = room__;

    room__ = Room();
    room__.current_room_id = 10;
    room__.left_room_id = 5;
    room__.up_room_id = 0;
    room__.right_room_id = 11;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 6;
    room_map_[10] = room__;

    room__ = Room();
    room__.current_room_id = 11;
    room__.left_room_id = 10;
    room__.up_room_id = 12;
    room__.right_room_id = 13;
    room__.down_room_id = 0;
    room__.visited = false;
    room__.current_room_type = 7;
    room_map_[11] = room__;

    room__ = Room();
    room__.current_room_id = 12;
    room__.left_room_id = 0;
    room__.up_room_id = 0;
    room__.right_room_id = 0;
    room__.down_room_id = 11;
    room__.visited = false;
    room__.current_room_type = 2;
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
    room_map_[13] = room__;

    build_vm_from_room_map();
}

string RoomService::get_doorstyle_from_room_type(int room_type)
{
    if (room_type >= 0 && room_type < 15)//普通门
    {
        return "res/gfx/grid/door_01_normaldoor.png";
    }
    if (room_type >= 15 && room_type < 21)//Boss门
    {
        return "res/gfx/grid/door_02_treasureroomdoor.png";
    }

    //其他门
    return "res/gfx/grid/door_04_selfsacrificeroomdoor.png";
}

string RoomService::get_ministyle_from_room_type(int room_type)
{
    return "";
}

void RoomService::build_vm_from_room_map()
{
    for (auto it = room_map_.begin();it != room_map_.end();++it)
    {
        auto room_id = (*it).first;
        const auto room_m = (*it).second;

        const auto room_type = room_m.current_room_type;

        auto room_ = RoomViewModel::createRoomViewModel(room_type);

        int doors[] = { room_m.left_room_id,room_m.up_room_id,room_m.right_room_id,room_m.down_room_id };

        auto door_ = vector<int>();
        auto door_style = vector<string>();

        for (int door : doors)
        {
            door_.push_back(door);
            door_style.emplace_back(get_doorstyle_from_room_type(door));
        }
        room_.setDoorEnable(door_);
        room_.setDoorStyle(door_style);

        store_[room_id] = room_;
    }
}

RoomService* RoomService::inst_ = nullptr;
