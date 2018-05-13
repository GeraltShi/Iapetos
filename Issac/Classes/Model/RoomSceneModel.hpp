#ifndef RoomSceneModel_hpp
#define RoomSceneModel_hpp

class RoomSceneModel
{
private:
public:
    RoomSceneModel(){};
    RoomSceneModel(int wd){
        walking_direction = wd;
    };
    int walking_direction = -1;
};
#endif /* RoomSceneModel_hpp */
