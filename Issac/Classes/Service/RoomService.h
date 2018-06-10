#ifndef _ROOMSERVICE_H_
#define _ROOMSERVICE_H_

#include <map>

#include "ViewModel/RoomViewModel.h"
#include "ViewModel/MiniMapViewModel.h"

struct Room
{
    int current_room_id;
    int left_room_id;
    int right_room_id;
    int up_room_id;
    int down_room_id;
};


class RoomService
{
public:
	static RoomService* getInstance();
	RoomViewModel get_room(int room_id);
    MiniMapViewModel get_mini_map(int room_id);

private:
    static RoomService *inst_;
    RoomService();

    map<int, RoomViewModel> store_;
    map<int, Room> room_map_;
};

RoomService* RoomService::inst_ = nullptr;

#endif // _ROOMSERVICE_H_

