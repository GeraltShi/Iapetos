#ifndef MINIMAP_VIEWMODEL_
#define MINIMAP_VIEWMODEL_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MiniMapViewModel
{
    //-1表示空
    //其余数字和room_type定义一致
    //-1 -1 -1 -1 -1
    //-1 -1 -1 -1 -1
    //-1  2  0  2 -1
    //-1 -1 -1 -1 -1
    //-1 -1 -1 -1 -1
    //中间的房间永远是“亮”
    CC_SYNTHESIZE(vector<vector<int>>, mini_mask_, MiniMask)
};

#endif
