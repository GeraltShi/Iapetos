#ifndef LEVEL_MODEL_H_
#define LEVEL_MODEL_H_

#include "cocos2d.h"
#include "SimpleItemViewModel.h"

USING_NS_CC;
using namespace std;

const Size RoomUnitSize = Size(26, 27);

class RoomViewModel
{
public:
	//roomType:0：初始房间
	//roomType:1~14怪物房间，1代表全Fatty
	//roomType:15~20代表Boss房
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
		assert(x >= 0 && x < 13);
		assert(y >= 0 && y < 7);
		return room_map[x][y];
	}
	void setPlayerPos(int x, int y) {
		assert(x >= 0 && x < 13);
		assert(y >= 0 && y < 7);
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
	int room_map[13][7];
};


#endif

