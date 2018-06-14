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
	int current_barrier_type;
};


class RoomService
{
public:
	static RoomService* getInstance();
	RoomViewModel enter_room(int room_id);
    MiniMapViewModel get_mini_map(int room_id);
    int get_init_room_id() const;
    int get_current_room_id() const;
    int get_left_room_id();
    int get_up_room_id();
    int get_right_room_id();
    int get_down_room_id();
    bool is_init_room() const;
    void init();

private:
    static RoomService *inst_;
    RoomService();

    map<int, RoomViewModel> store_;
    map<int, Room> room_map_;

    int init_room_id_;
    int current_room_id_;

    static string get_doorstyle_from_room_type(int room_type);
    static string get_groundstyle_from_room_type(int room_type);
    void build_vm_from_room_map();
};


#endif // _ROOMSERVICE_H_

