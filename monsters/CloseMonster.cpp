#include "CloseMonster.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <cmath>
#define M_PI 3.14159265358979323846

namespace CloseMonsterSetting {
    static constexpr char gif_basic_root_path[] = "./assets/gif/Monster-closecombat/KnightBasic/";
    static constexpr char gif_atk_root_path[] = "./assets/gif/Monster-closecombat/KnightAdvCombat/";
    static constexpr char gif_move_root_path[] = "./assets/gif/Monster-closecombat/KnightExMovement/";
    static constexpr char gif_postfix[][6] = {
        "1.gif", "2.gif", "3.gif", "4.gif", "5.gif", "6.gif", "7.gif", "8.gif"
    };
}

void CloseMonster::init() {
    // 設定走路和跑步的 gif path
    for (int dir = 0; dir < 8; ++dir) {
        char buffer[100];
        // Walk GIF Path
        sprintf(buffer, "%sWalk/Knight_Walk_dir%s", CloseMonsterSetting::gif_basic_root_path, CloseMonsterSetting::gif_postfix[dir]);
        gifPath[{CloseMonsterState::WALK, dir}] = std::string(buffer);

        // Run GIF Path
        sprintf(buffer, "%sRun/Knight_Run_dir%s", CloseMonsterSetting::gif_basic_root_path, CloseMonsterSetting::gif_postfix[dir]);
        gifPath[{CloseMonsterState::RUN, dir}] = std::string(buffer);
    }

    // 設定攻擊和蹲下的 gif path
    for (int dir = 0; dir < 8; ++dir) {
        char buffer[100];
        // Attack GIF Path
        sprintf(buffer, "%sKnock/Knight_Knock_dir%s", CloseMonsterSetting::gif_atk_root_path, CloseMonsterSetting::gif_postfix[dir]);
        gifPath[{CloseMonsterState::ATTACK, dir}] = std::string(buffer);

        // Crouch GIF Path
        sprintf(buffer, "%sCrouch/Knight_Crouch_dir%s", CloseMonsterSetting::gif_move_root_path, CloseMonsterSetting::gif_postfix[dir]);
        gifPath[{CloseMonsterState::CROUCH, dir}] = std::string(buffer);
    }

    // 設定初始位置和碰撞盒
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[{CloseMonsterState::WALK, 0}]); // 預設初始為向左下方走
    DataCenter *DC = DataCenter::get_instance();
    shape.reset(new Rectangle(DC->window_width / 2,
                              DC->window_height / 2,
                              DC->window_width / 2 + gif->width,
                              DC->window_height / 2 + gif->height));
}

void CloseMonster::update() {
    DataCenter *DC = DataCenter::get_instance();
    Point hero_position = DC->witch->get_position();

    double dx = hero_position.x - shape->center_x();
    double dy = hero_position.y - shape->center_y();
    double distance_to_hero = std::sqrt(dx * dx + dy * dy);

    // 根據距離和狀態決定下一步動作
    if (is_charging) {
        // Charging towards hero
        if (charge_counter > 0) {
            shape->update_center_x(shape->center_x() + charge_speed_multiplier * speed * (dx / distance_to_hero));
            shape->update_center_y(shape->center_y() + charge_speed_multiplier * speed * (dy / distance_to_hero));
            charge_counter--;
        } else {
            is_charging = false;
            state = CloseMonsterState::WALK; // 回到行走狀態
        }
    } else if (distance_to_hero <= attack_range) {
        // 距離足夠近，執行攻擊
        state = CloseMonsterState::ATTACK;
    } else if (distance_to_hero <= charge_range) {
        // 進入蹲下並衝刺的狀態
        state = CloseMonsterState::CROUCH;
        is_charging = true;
        charge_counter = charge_duration;
    } else {
        // 朝著英雄走動
        state = CloseMonsterState::WALK;
        shape->update_center_x(shape->center_x() + speed * (dx / distance_to_hero));
        shape->update_center_y(shape->center_y() + speed * (dy / distance_to_hero));
    }
}

void CloseMonster::draw() {
    DataCenter *DC = DataCenter::get_instance();
    Point hero_position = DC->witch->get_position();

    // 根據相對位置決定方向 (方向 1~8)
    double angle = atan2(hero_position.y - shape->center_y(), hero_position.x - shape->center_x());
    int dir = static_cast<int>((angle + M_PI) / (M_PI / 4)) % 8;

    // 獲取對應狀態和方向的 GIF
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[{state, dir}]);

    // 畫出 GIF
    algif_draw_gif(gif, shape->center_x() - gif->width / 2, shape->center_y() - gif->height / 2, 0);
}

void CloseMonster::set_position(int x, int y) {
    shape->update_center_x(x);
    shape->update_center_y(y);
}
