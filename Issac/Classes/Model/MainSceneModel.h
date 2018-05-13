#ifndef __MAIN_SCENE_MODEL_H__
#define __MAIN_SCENE_MODEL_H__

class MainSceneModel
{
private:
public:
    MainSceneModel(){};
    MainSceneModel(int wd){
        menun = wd;
    }
    void shiftMenu(int wd){
        menun = (menun+wd+5)%5;
    }
    int menun = 0;
};

#endif // __MAIN_SCENE_MODEL_H__
