#include "RoomViewModel.h"

RoomViewModel RoomViewModel::createRoomViewModel(int roomType)
{
	RoomViewModel room1;
	room1.init(roomType);
	return room1;
}

void RoomViewModel::init(int roomType)
{
	door_style.emplace_back("res/gfx/grid/door_01_normaldoor.png");
	door_style.emplace_back("res/gfx/grid/door_02_treasureroomdoor.png");
	door_style.emplace_back("res/gfx/grid/door_03_ambushroomdoor.png");
	door_style.emplace_back("res/gfx/grid/door_04_selfsacrificeroomdoor.png");

	//生成几种房间之一,放入石头
	int barrierType = rand() % 3;
	if (barrierType == 0) {
		//没有石头
	}
	if (barrierType == 1) {
		
	}
	if (barrierType == 2) {
	
	}

	//根据roomType放入怪物
	if (roomType == 1) {
		int Fatty_num = rand() % 4 + 2;

	}

}