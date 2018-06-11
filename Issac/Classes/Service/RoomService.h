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
    bool visited;
    int current_room_type;
};


class RoomService
{
public:
	static RoomService* getInstance();
	RoomViewModel get_room(int room_id);
    MiniMapViewModel get_mini_map(int room_id);
    int get_init_room_id() const;

private:
    static RoomService *inst_;
    RoomService();

    map<int, RoomViewModel> store_;
    map<int, Room> room_map_;

    int init_room_id_;

    string get_doorstyle_from_room_type(int room_type);
    string get_ministyle_from_room_type(int room_type);
    void build_door_from_room_map();
};


#endif // _ROOMSERVICE_H_

