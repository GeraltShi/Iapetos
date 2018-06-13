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
        paused_menu_cursor = (paused_menu_cursor+wd+3)%3;
    }
    void shift_optionmenu(int wd){
        option_menu_cursor = (option_menu_cursor+wd+3)%3;
    }
    bool bomb = false;
    int game_stat = 0;// 游戏状态控制，0为运行，1为暂停，2为结束
    int paused_menu_generated_flag = 0;
    int paused_menu_cursor = 1;//1表明光标初始化在 resume
    
    int option_menu_cursor = 0;
    int option_display = 0;
    int sfx_volume = 0;
    int music_volume = 0;// 0-10
    int map_opacity = 0;// 0-10
    
    int dead_menu_generated_flag = 0;
    
};
#endif /* RoomSceneModel_hpp */
