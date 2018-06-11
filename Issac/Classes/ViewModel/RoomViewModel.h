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
	//1~14怪物房间，1代表全Fatty
	//15~20代表Boss房
	static RoomViewModel createRoomViewModel(int roomType);
	void init(int roomType);
    //房间：门的位置（enable），门的样式，地面物品（棋盘），地面的样子，光影，边界（棋盘）。
    //棋盘13*7(442-96=346 * 286-96=190) 
	//棋盘中0表示空地，1表示石头，2表示怪物
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //地面物品（绝对坐标）vector<SimpleItemViewModel>
    //地面石头（棋盘）vector<vector<int>> 0代表空，1，2，3，4代表障碍和样式，"stone_style_{number}"

	//1,2,3,4四个门（左、上、右、下）的位置是否有门
    CC_SYNTHESIZE(vector<int>, door_enable, DoorEnable)
	//门样式["door_style_1","door_style_2","door_style_3","door_style_4"]方便从cache中获取
    CC_SYNTHESIZE(vector<string>, door_style, DoorStyle)
    CC_SYNTHESIZE(vector<SimpleItemViewModel>, items, Items)
    //CC_SYNTHESIZE(vector<vector<int>>, barrier_mask, BarrierMask)
	//怪物类型与位置
	CC_SYNTHESIZE(vector<int>, monsterType, MonsterType)
	CC_SYNTHESIZE(vector<Vec2>, monsterPos, MonsterPos)
	//光影是一张贴图，"overlay_style_1"
    CC_SYNTHESIZE(string, overlay_style, OverlayStyle)
	//地面是一张贴图，"ground_style_1"
    CC_SYNTHESIZE(string, ground_style, GroundStyle)
	
	int getRoomMap(int x, int y) {
		assert(x >= 0 && x < 13);
		assert(y >= 0 && y < 7);
		return room_map[x][y];
	}
private:
	int room_map[13][7];
};


#endif

