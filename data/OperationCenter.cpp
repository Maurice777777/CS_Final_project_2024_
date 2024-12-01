#include "OperationCenter.h"
#include "DataCenter.h"
#include "../monsters/CloseMonster.h"
#include "../Player.h"
#include "../shapes/Point.h"
#include "../RedWitch.h"

void OperationCenter::update() {
	// Update monsters.
	_update_monster();
	// If any monster reaches the end, hurt the player and delete the monster.
	_update_monster_player();
}


void OperationCenter::_update_monster_player()
{
	DataCenter *DC = DataCenter::get_instance();
    std::vector<CloseMonster*> &monsters = DC->closeMonsters;
    Player *&player = DC->player;
	Witch *&witch  = DC->witch;

    for (size_t i = 0; i < monsters.size(); ++i) {
        // Check if the monster is killed.
        if (monsters[i]->get_HP() <= 0) {
            // Monster gets killed. Player receives money.
            player->coin += monsters[i]->get_money();
            delete monsters[i];
            monsters.erase(monsters.begin() + i);
            --i;
            // Since the current monster is killed, we can directly proceed to next monster.
            continue;
        }

        // Check if the monster is close enough to attack the player.
        double distance_to_hero = Point::dist2(witch->get_position(),monsters[i]->get_position());
        if (distance_to_hero < 20) {
            player->HP--;
            delete monsters[i];
            monsters.erase(monsters.begin() + i);
            --i;
        }
    }
}

void OperationCenter::draw() {
	_draw_monster();
}

void OperationCenter::_draw_monster() {
	std::vector<CloseMonster*> &monsters = DataCenter::get_instance()->closeMonsters;
	for(CloseMonster *monster : monsters)
		monster->draw();
}