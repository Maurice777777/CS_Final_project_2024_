#include "Level.h"
#include <string>
#include "Utils.h"
#include "monsters/CloseMonster.h"
#include "data/DataCenter.h"
#include <allegro5/allegro_primitives.h>
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <array>

using namespace std;

// fixed settings
namespace LevelSetting {
	constexpr char level_path_format[] = "./assets/level/LEVEL%d.txt";
	//! @brief Grid size for each level.
	constexpr array<int, 4> grid_size = {
		40, 40, 40, 40
	};
	//constexpr int monster_spawn_rate = 90;//生成怪物的速率，每 90 幀生成一個怪物
};

void
Level::init() 
{
	//皆設為-1表示尚未載入任何關卡
	level = -1;
	grid_w = -1;
	grid_h = -1;
	monster_spawn_counter = 0;//用來控制何時生成下一個怪物
}

void Level::load_level(int lvl) {
    DataCenter *DC = DataCenter::get_instance();

    // 根據不同的關卡設置不同的怪物數量或生成頻率
    switch (lvl) {
        case 1:
            num_of_monsters = {10, 5, 3}; // 第一關卡有 10 個近戰，5 個遠程，3 個固定位置的怪物
            monster_spawn_rate = 100;      // 每 100 幀生成一個怪物
            break;
        case 2:
            num_of_monsters = {15, 10, 5};
            monster_spawn_rate = 80;
            break;
        default:
            num_of_monsters = {20, 15, 10};
            monster_spawn_rate = 60;
            break;
    }

    level = lvl;
    monster_spawn_counter = 0;
    debug_log("<Level> load level %d.\n", lvl);
}


/**
 * @brief Updates monster_spawn_counter and create monster if needed.
*/
void Level::update() {
	if(monster_spawn_counter>0) {
		monster_spawn_counter--;
		return;
	}
	DataCenter *DC = DataCenter::get_instance();

	for(size_t i = 0; i < num_of_monsters.size(); ++i) {
		if(num_of_monsters[i] == 0) continue;

		int random_x = rand()%DC->game_field_length;
		int random_y = rand()%DC->game_field_length;

		CloseMonster *monster = CloseMonster::create_monster(static_cast<CloseMonsterState>(i));
		monster->set_position(random_x,random_y);

		DC->monsters.emplace_back(monster);
		num_of_monsters[i]--;

		break;
	}
	monster_spawn_counter = monster_spawn_rate;
}

void Level::draw() {
    // 如果關卡尚未初始化，直接返回
    if (level == -1) return;

    // 繪製所有怪物
    DataCenter *DC = DataCenter::get_instance();
    for (auto &monster : DC->monsters) {
        monster->draw(); // 呼叫每個怪物的 draw 方法
    }
}
