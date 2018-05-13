#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IMainSceneListener.h"
#include "Model/MainSceneModel.h"

class MainScene : public cocos2d::Scene
{
  public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);

    void set_event_listener(IMainSceneListener *listener);
    void set_model(MainSceneModel model);
    void update(float delta) override;
    MainSceneModel model;
private:
    Size size;
    IMainSceneListener * listener_ = nullptr;
    
    void menu_update(int n) const;
    //void peppa_move(int direction) const;

    Sprite * selector = nullptr;
    int menuflag = 0;
    int selector_init_x = 0;
    int selector_init_y = 0;
};

#endif // __MAIN_SCENE_H__
