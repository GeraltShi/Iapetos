#ifndef MINIMAP_VIEWMODEL_
#define MINIMAP_VIEWMODEL_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MiniMapViewModel
{
    CC_SYNTHESIZE(vector<vector<int>>, mini_mask_, MiniMask)

    MiniMapViewModel();
};

#endif
