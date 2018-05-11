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
    ~MainScene(){};

private:
    IMainSceneListener * listener_ = nullptr;
    MainSceneModel model;

    void peppa_move(int direction) const;

    Sprite * peppa = nullptr;
};

#endif // __MAIN_SCENE_H__
