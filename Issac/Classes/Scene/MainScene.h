#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IMainSceneListener.h"
#include "Model/MainSceneModel.h"

class MainScene : public Scene
{
  public:
	static Scene *createScene();
    bool init() override;
	CREATE_FUNC(MainScene)
    CC_SYNTHESIZE_RETAIN(Sprite*, selector, Selector)
    CC_SYNTHESIZE(IMainSceneListener*,listener_,Listener)

    void set_event_listener(IMainSceneListener *listener);
    void set_model(MainSceneModel model);
    void update(float delta) override;
    MainSceneModel model;
private:
    Size size;
    
    void menu_update(int n) const;
    int menuflag_ = 0;
    int selector_init_x_ = 0;
    int selector_init_y_ = 0;
};

#endif // __MAIN_SCENE_H__
