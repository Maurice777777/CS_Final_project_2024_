#ifndef CLOSEMONSTER_H_INCLUDED
#define CLOSEMONSTER_H_INCLUDED

#include <string>
#include <map>
#include <memory>  // 添加這一行來使用 std::shared_ptr
#include "../shapes/Point.h"
// 狀態的定義
enum class CloseMonsterState {
    WALK,
    RUN,
    ATTACK,
    CROUCH,
    CLOSEMONSTERSTATE_MAX
};

class CloseMonster {
public:
    void init();
    void update();
    void draw();
    void set_position(int x, int y);
    int get_HP() const;
    void take_damage(int damage);
    int get_money()const;
    Point get_position()const;
private:
    CloseMonsterState state = CloseMonsterState::WALK;
    double speed = 3.0; // 基本移動速度
    bool is_charging = false; // 用於標記是否正在衝刺
    int charge_counter = 0;
    double charge_speed_multiplier = 2.0; // 衝刺時速度的倍數
    int attack_range = 20; // 攻擊的距離
    int charge_range = 100; // 觸發衝刺的距離
    int charge_duration = 60; // 衝刺持續的時間（以幀計）
    std::shared_ptr<Rectangle> shape; // 使用 shared_ptr，確保包含了 <memory> 頭檔
    int HP = 100;
    int money = 10;
    bool is_alive = true;
    // GIF 路徑對應
    std::map<std::pair<CloseMonsterState, int>, std::string> gifPath;
};

#endif // CLOSEMONSTER_H_INCLUDED
