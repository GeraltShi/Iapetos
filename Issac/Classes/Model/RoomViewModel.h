#ifndef LEVEL_MODEL_H_
#define LEVEL_MODEL_H_

#include "cocos2d.h"
#include "ViewModel/SimpleItemViewModel.h"

USING_NS_CC;
using namespace std;

class LevelModel
{
public:
    LevelModel();
    ~LevelModel();
    //房间：门的位置（enable），门的样式，地面物品（棋盘），地面的样子，光影，边界（棋盘）。
    //棋盘13*7
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,2,2,3,4,4,0,0,0,0,0
    //0,0,0,1,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //0,0,0,0,0,0,0,0,0,0,0,0,0
    //门[0,0,0,0]   [1,1,1,1] 1表示有门，0表示无门
    //门样式["door_style_1","door_style_2","door_style_3","door_style_4"]方便从cache中获取
    //地面物品（绝对坐标）vector<SimpleItemViewModel>
    //地面石头（棋盘）vector<vector<int>> 0代表空，1，2，3，4代表障碍和样式，"stone_style_{number}"
    //光影是一张贴图，"overlay_style_1"
    //地面是一张贴图，"ground_style_1"
    CC_SYNTHESIZE(vector<int>, door_enable, DoorEnable)
    CC_SYNTHESIZE(vector<string>, door_style, DoorStyle)
    CC_SYNTHESIZE(vector<SimpleItemViewModel>, items, Items)
    CC_SYNTHESIZE(vector<vector<int>>, barrier_mask, BarrierMask)
    CC_SYNTHESIZE(string, overlay_style, OverlayStyle)
    CC_SYNTHESIZE(string, ground_style, GroundStyle)
};


#endif

