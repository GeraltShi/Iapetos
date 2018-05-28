#ifndef ROOM_SCENE_MODEL_HPP
#define ROOM_SCENE_MODEL_HPP

class RoomSceneModel
{
public:
    RoomSceneModel() = default;
    RoomSceneModel(int wd, int td){
        walk_direction = wd;
        tear_direction = td;
    };
    int walk_direction = 5;
    int tear_direction = 5;
};
#endif /* RoomSceneModel_hpp */
