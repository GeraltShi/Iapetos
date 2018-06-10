#include "RoomService.h"
#include "cocos2d.h"

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


/**
 * \brief 初始化所有房间信息
 */
RoomService::RoomService()
{
    for (int i = 0; i < 10; ++i)
    {
        store_[i + 1] = RoomViewModel();
        room_map_[i + 1] = Room();
    }
}