#ifndef RoomSceneModel_hpp
#define RoomSceneModel_hpp

class RoomSceneModel
{
private:
public:
    RoomSceneModel(){};
    RoomSceneModel(int wd, int hd){
        walking_direction = wd;
        head_direction = hd;
    };
    int walking_direction = 4;
    int head_direction = -1;
};
#endif /* RoomSceneModel_hpp */
