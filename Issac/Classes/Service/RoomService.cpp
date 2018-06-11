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
RoomViewModel RoomService::get_room(const int room_id)
{
    if (room_id > 0)
    {
        auto r = store_[room_id];
        return r;
    }
    throw runtime_error("Room Not Found");
}

MiniMapViewModel RoomService::get_mini_map(int room_id)
{
    if (room_id <= 0)
    {
        throw runtime_error("Room Not Found");
    }
    const auto m = room_map_[room_id];
    const auto l = m.left_room_id;
    const auto r = m.right_room_id;
    const auto u = m.up_room_id;
    const auto d = m.down_room_id;

    vector<vector<int>> masks;

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


/**
 * \brief 初始化所有房间信息
 */
RoomService::RoomService()
{
    auto room1 = RoomViewModel();
    auto door = vector<int>();
    door.push_back(1);
    door.push_back(1);
    door.push_back(1);
    door.push_back(1);
    room1.setDoorEnable(door);

    auto door_style = vector<string>();
    door_style.emplace_back("res/gfx/grid/door_01_normaldoor.png");
    door_style.emplace_back("res/gfx/grid/door_02_treasureroomdoor.png");
    door_style.emplace_back("res/gfx/grid/door_03_ambushroomdoor.png");
    door_style.emplace_back("res/gfx/grid/door_04_selfsacrificeroomdoor.png");
    room1.setDoorStyle(door_style);


    store_[1] = room1;

    for (int i = 1; i < 10; ++i)
    {
        store_[i + 1] = RoomViewModel();
        room_map_[i + 1] = Room();
    }

    init_room_id_ = 1;
}

RoomService* RoomService::inst_ = nullptr;
