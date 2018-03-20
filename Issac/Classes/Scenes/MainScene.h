#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"


class Main : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(Main);
};

#endif // __MAIN_SCENE_H__