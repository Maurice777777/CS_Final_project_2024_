#include "OperationCenter.h"
#include "DataCenter.h"
#include "../monsters/CloseMonster.h"
#include "../Player.h"

void OperationCenter::update() {
	// Update monsters.
	_update_monster();
	// If any monster reaches the end, hurt the player and delete the monster.
	_update_monster_player();
}

void OperationCenter::_update_monster() {
	std::vector<CloseMonster*> &monsters = DataCenter::get_instance()->monsters;
	for(CloseMonster *monster : monsters)
		monster->update();
}



void OperationCenter::_update_monster_player() {
	DataCenter *DC = DataCenter::get_instance();
	std::vector<CloseMonster*> &monsters = DC->monsters;
	Player *&player = DC->player;
	for(size_t i = 0; i < monsters.size(); ++i) {
		// Check if the monster is killed.
		if(monsters[i]->HP <= 0) {
			// Monster gets killed. Player receives money.
			player->coin += monsters[i]->get_money();
			monsters.erase(monsters.begin()+i);
			--i;
			// Since the current monsster is killed, we can directly proceed to next monster.
			break;
		}
		// Check if the monster reaches the end.
		if(monsters[i]->get_path().empty()) {
			monsters.erase(monsters.begin()+i);
			player->HP--;
			--i;
		}
	}
}

void OperationCenter::draw() {
	_draw_monster();
}

void OperationCenter::_draw_monster() {
	std::vector<Monster*> &monsters = DataCenter::get_instance()->monsters;
	for(Monster *monster : monsters)
		monster->draw();
}