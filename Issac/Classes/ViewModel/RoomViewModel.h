#ifndef LEVEL_MODEL_H_
#define LEVEL_MODEL_H_

#define GRID_WIDTH 13
#define GRID_HEIGHT 7
#define GRID_WIDTH_HALF 6
#define GRID_HEIGHT_HALF 3

#include "cocos2d.h"
#include "SimpleItemViewModel.h"

USING_NS_CC;
using namespace std;

const Size RoomUnitSize = Size(26, 27);

class RoomViewModel
{
public:
	//roomType:0：初始房间
	//roomType:1~7怪物房间，1代表全Fatty
    //roomType:8~14宝藏房间
	//roomType:15~20代表Boss房
        //15~17 Boss1
        //18~20 Boss2
	static RoomViewModel createRoomViewModel(int roomType);
	void init(int roomType);

	//1,2,3,4四个门（左、上、右、下）的位置是否有门
    CC_SYNTHESIZE(vector<int>, door_enable, DoorEnable)
	//门样式["door_style_1","door_style_2","door_style_3","door_style_4"]方便从cache中获取
    CC_SYNTHESIZE(vector<string>, door_style, DoorStyle)
	//光影是一张贴图，"overlay_style_1"
    CC_SYNTHESIZE(string, overlay_style, OverlayStyle)
	//地面是一张贴图，"ground_style_1"
    CC_SYNTHESIZE(string, ground_style, GroundStyle)
	
	int getRoomMap(int x, int y) {
		assert(x >= 0 && x < GRID_WIDTH);
		assert(y >= 0 && y < GRID_HEIGHT);
		return room_map[x][y];
	}
	void setPlayerPos(int x, int y) {
		assert(x >= 0 && x < GRID_WIDTH);
		assert(y >= 0 && y < GRID_HEIGHT);
		room_map[x][y] = 3;
	}
private:
	//棋盘13*7(442-96=346 * 286-96=190)，每个格子大小为RoomUnitSize
	//棋盘中0表示空地，1表示小石头，2表示大石头，3表示玩家
	//4~19表示怪物的各种类别,20~30item
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	//0,0,0,0,0,0,0,0,0,0,0,0,0
	int room_map[GRID_WIDTH][GRID_HEIGHT];
};


#endif

