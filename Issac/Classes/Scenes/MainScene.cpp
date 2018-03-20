#include "MainScene.h"

USING_NS_CC;
using namespace std;

cocos2d::Scene * Main::createScene()
{
	return Main::create();
}

bool Main::init()
{
	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	return true;
}
