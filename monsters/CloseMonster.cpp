#include "CloseMonster.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include "shapes/Point.h"
#include "../Witch_bullet.h"
#include "../RedWitch.h"


/*
所在資料夾位置：

走：./assets/gif/Monster-closecombat/KnightBasic/Walk
跑：./assets/gif/Monster-closecombat/KnightBasic/Run
出拳：./assets/gif/Monster-closecombat/KnightAdvCombat/Knock/
蹲下：./assets/gif/Monster-closecombat/KnightExMovement/Crouch/
*/
namespace CloseMonsterSetting {
    static constexpr char gif_basic_root_path[50] = "./assets/gif/Monster-closecombat/KnightBasic/";
    static constexpr char gif_atk_root_path[50] = "./assets/gif/Monster-closecombat/KnightAdvCombat/";
    static constexpr char gif_move_root_path[60] = "./assets/gif/Monster-closecombat/KnightExMovement/";
    static constexpr char gif_basic_postfix[][30] = {
        "Run/Knight_Run_dir",
        "Walk/Knight_Walk_dir"
    };
    static constexpr char gif_atk_postfix[20] = "Knight_Knock_dir";
    static constexpr char gif_move_postfix[20] = "Knight_Crouch_dir";
    static constexpr int charge_duration = 60; // 衝刺持續時間（幀數）
    static constexpr double charge_speed_multiplier = 3.0; // 衝刺時的速度倍數
    static constexpr double attack_range = 100.0; // 攻擊範圍
    static constexpr double charge_range = 200.0; // 開始衝刺的範圍
}


void CloseMonster::init()
{
    // set walk/run gif path for each direction
    for (int dir = 1; dir <= 8; ++dir) 
    {
        char buffer[100];

        // 設置走路動作的 GIF 路徑
        sprintf(buffer, "%s%s%d.gif",
            CloseMonsterSetting::gif_basic_root_path,
            CloseMonsterSetting::gif_basic_postfix[1],  // Walk 動作
            dir);
        gifPath[static_cast<CloseMonsterState>(dir - 1)] = std::string{buffer};

        // 設置跑步動作的 GIF 路徑
        sprintf(buffer, "%s%s%d.gif",
            CloseMonsterSetting::gif_basic_root_path,
            CloseMonsterSetting::gif_basic_postfix[0],  // Run 動作
            dir);
        gifPath[static_cast<CloseMonsterState>(dir + 7)] = std::string{buffer};
    }

    // set attack gifs for each direction
    for (int dir = 1; dir <= 8; ++dir) 
    {
        char buffer[100];
        sprintf(buffer, "%s%s%d.gif",
            CloseMonsterSetting::gif_atk_root_path,
            CloseMonsterSetting::gif_atk_postfix,
            dir);
        gifPath[static_cast<CloseMonsterState>(dir + 15)] = std::string{buffer};
    }

    // set crouch gif for each direction
    for (int dir = 1; dir <= 8; ++dir) 
    {
        char buffer[100];
        sprintf(buffer, "%s%s%d.gif",
            CloseMonsterSetting::gif_move_root_path,
            CloseMonsterSetting::gif_move_postfix,
            dir);
        gifPath[static_cast<CloseMonsterState>(dir + 23)] = std::string{buffer};
    }

    // set initial position and hit box of monster
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    DataCenter *DC = DataCenter::get_instance();
    shape.reset(new Rectangle(DC->window_width / 2,
                          DC->window_height / 2,
                          DC->window_width / 2 + gif->width,
                          DC->window_height / 2 + gif->height));
}


void CloseMonster::draw()
{
    // load GIF from GIFCenter based on current state
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
   if (gif) 
   {
        algif_draw_gif(gif,
                   shape->center_x() - gif->width / 2,
                   shape->center_y() - gif->height / 2,
                   0);
   }
}

void CloseMonster::update()
{
    DataCenter *DC = DataCenter::get_instance();
    Point hero_position = DC->witch->get_position();
    double dx = shape->center_x() - hero_position.x;
    double dy = shape->center_y() - hero_position.y;
    double distance_to_hero = std::sqrt(dx * dx + dy * dy);


    // 如果正在衝刺，更新衝刺狀態
    if (is_charging) 
    {
        charge_counter--;
        if (charge_counter <= 0) 
        {
            is_charging = false;
        } 
        else 
        {
            // 朝著原本確定的方向衝刺
            double dx = hero_position.x - shape->center_x();
            double dy = hero_position.y - shape->center_y();
            double magnitude = sqrt(dx * dx + dy * dy);
            shape->update_center_x(shape->center_x() + (dx / magnitude) * speed * CloseMonsterSetting::charge_speed_multiplier);
            shape->update_center_y(shape->center_y() + (dy / magnitude) * speed * CloseMonsterSetting::charge_speed_multiplier);
            return;
        }
    }

    // 根據與 Hero 的距離進行不同動作
    if (distance_to_hero < CloseMonsterSetting::attack_range) {
        // 進入攻擊狀態
        state = static_cast<CloseMonsterState>(15 + static_cast<int>(state) % 8); // 將狀態設為對應方向的攻擊動作
    } 
    else if (distance_to_hero < CloseMonsterSetting::charge_range && !is_charging) 
    {
        // 進入衝刺狀態
        is_charging = true;
        charge_counter = CloseMonsterSetting::charge_duration;
        state = static_cast<CloseMonsterState>(23 + static_cast<int>(state) % 8); // 將狀態設為對應方向的蹲下動作
    }
    else 
    {
        // 普通移動狀態
        double dx = hero_position.x - shape->center_x();
        double dy = hero_position.y - shape->center_y();
        double magnitude = sqrt(dx * dx + dy * dy);
        shape->update_center_x(shape->center_x() + (dx / magnitude) * speed);
        shape->update_center_y(shape->center_y() + (dy / magnitude) * speed);

        // 根據方向設置狀態
        if (abs(dx) > abs(dy))  state = (dx > 0) ? CloseMonsterState::RUN_RIGHT : CloseMonsterState::RUN_LEFT;
        else state = (dy > 0) ? CloseMonsterState::RUN_DOWN : CloseMonsterState::RUN_UP;
    }
}

CloseMonster*CloseMonster::create_monster(CloseMonsterState state)
{
    CloseMonster* monster = new CloseMonster();
    monster->state = state;
    return monster;
}

void CloseMonster::set_position(int x,int y)
{
    
}