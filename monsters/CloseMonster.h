#ifndef CLOSEMONSTER_H_INCLUDED
#define CLOSEMONSTER_H_INCLUDED

#include <string>
#include <map>
#include "../Object.h"
//#include "shapes/Point.h"

enum class CloseMonsterState
{
    RUN_LEFT,
    RUN_RIGHT,
    RUN_DOWN,
    RUN_UP,
    UPPER_LEFT,
    UPPER_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    ATTACK_LEFT,
    ATTACK_RIGHT,
    ATTACK_FRONT,
    ATTACK_BACK,
    ATTACK_UPPER_LEFT,
    ATTACK_UPPER_RIGHT,
    ATTACK_DOWN_LEFT,
    ATTACK_DOWN_RIGHT,
    CLOSEMONSTERSTATE_MAX
};

class CloseMonster : public Object
{
    public:
        void init();
        void update();
        void draw();
        void set_position(int x,int y);
        Point get_position() const;
        static CloseMonster* create_monster(CloseMonsterState state);
    private:
        std::map<CloseMonsterState, std::string> gifPath; // 存儲每個狀態對應的 GIF 路徑
        double speed = 2.0; // 怪物移動速度
        bool is_charging = false; // 是否正在衝刺
        int charge_counter = 0; // 衝刺計數器
        static constexpr int charge_duration = 60; // 衝刺持續時間（幀數）
        static constexpr double charge_speed_multiplier = 3.0; // 衝刺時的速度倍數
        static constexpr double attack_range = 100.0; // 攻擊範圍
        static constexpr double charge_range = 200.0; // 開始衝刺的範圍
        CloseMonsterState state = CloseMonsterState::RUN_DOWN;

};

#endif // REDWITCH_H_INCLUDED
