#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <vector>
#include <utility>
#include <tuple>
#include "./shapes/Rectangle.h"

/**
 * @brief The class manages data of each level.
 * @details The class could load level with designated input file and record. The level itself will decide when to create next monster.
 * @see DataCenter::level
 */
class Level
{
public:
	Level() {}
	void init();
	void load_level(int lvl);
	void update();
	void draw();
	void generate_random_monster();
	int remain_monsters() const {
		int res = 0;
		for(const int &i : num_of_monsters) res += i;
		return res;
	}
private:
	/**
	 * @brief Stores the monster's attack route, whose Point is represented in grid format.
	 */
	/**
	 * @brief The index of current level.
	 */
	int level;
	/**
	 * @brief Number of grid in x-direction.
	 */
	int grid_w;
	/**
	 * @brief Number of grid in y-direction.
	 */
	int grid_h;
	/**
	 * @brief Time remaining for the next monster to spawn.
	 */
	int monster_spawn_rate;
	int monster_spawn_counter;
	/**
	 * @brief Number of each different type of monsters.
	 */
	std::vector<int> num_of_monsters;
	std::vector<CloseMonster*>closemonsters;
};

#endif
