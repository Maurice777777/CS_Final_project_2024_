// #ifndef MONSTER_H_INCLUDED
// #define MONSTER_H_INCLUDED

// #include "../Object.h"
// #include <vector>
// #include <string>

// enum class MonsterType
// {
//     CLOSECOMBAT,
//     RANGEDCOMBAT,
//     STATIC,
//     MONSTERTYPE_MAX
// };

// class Monster : public Object
// {
// public:
//     Monster(const std::vector<Point> &path, MonsterType type);
//     virtual ~Monster() {}

//     virtual void update() = 0; // 使用純虛函數讓子類必須覆寫
//     virtual void draw() = 0;   // 使用純虛函數讓子類必須覆寫

//     MonsterType get_type() const;

// protected:
//     MonsterType type;
//     std::vector<Point> path;  // 怪物行進的路徑

//     // 動畫相關
//     std::vector<std::string> gif_paths;
//     std::string current_gif;
// };

// #endif // MONSTER_H_INCLUDED
