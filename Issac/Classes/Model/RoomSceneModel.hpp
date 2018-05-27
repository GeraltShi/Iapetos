#ifndef RoomSceneModel_hpp
#define RoomSceneModel_hpp

class RoomSceneModel
{
private:
public:
    RoomSceneModel(){};
    RoomSceneModel(int wd, int td){
        walk_direction = wd;
        tear_direction = td;
    };
    int walk_direction = 5;
    int tear_direction = 5;
};
#endif /* RoomSceneModel_hpp */
