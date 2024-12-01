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

void Level::init() 
{
	//皆設為-1表示尚未載入任何關卡
	level = -1;
	grid_w = -1;
	grid_h = -1;
	monster_spawn_counter = 0;//用來控制何時生成下一個怪物
	srand(time(nullptr));
}

void Level::update() {
    if (monster_spawn_counter) {
        monster_spawn_counter--;
        return;
    }

    // 生成新怪物
    generate_random_monster();
    monster_spawn_counter = 120; // 每 120 幀生成一次
}



void Level::generate_random_monster() {
    DataCenter *DC = DataCenter::get_instance();

    // 隨機生成怪物位置
    int random_x = rand() % DC->game_field_length;
    int random_y = rand() % DC->game_field_length;

    CloseMonster *monster = new CloseMonster();
    monster->set_position(random_x, random_y);
    closemonsters.push_back(monster);
}

void Level::draw() {
    for (auto &monster : closemonsters) {
        monster->draw();
    }
}