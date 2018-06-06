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
    
    void shift_pausemenu(int wd){
        paused_menu_cursor = (paused_menu_cursor+wd+2)%2;
    }
    bool paused = false;
    int paused_menu_generated_flag = 0;
    int paused_menu_cursor = 1;
};
#endif /* RoomSceneModel_hpp */
