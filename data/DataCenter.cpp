#include "DataCenter.h"
#include <cstring>
#include "../Level.h"
#include "../Player.h"
/*---Revis---*/
#include "../RedWitch.h"
#include "../Witch_bullet.h"
#include "../monsters/CloseMonster.h"
/*---Revis---*/

// fixed settings
namespace DataSetting 
{
	constexpr double FPS = 60; //每秒的幀數設定為 60
	constexpr int window_width = 800; //遊戲視窗的寬度為 800
	constexpr int window_height = 600; //遊戲視窗的高度為 600
	constexpr int game_field_length = 600; //遊戲場地的邊長設定為 600
}

DataCenter::DataCenter() {
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;
	
	// 初始化鍵盤狀態
	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	
	// 初始化滑鼠狀態
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	
	// 初始化玩家和關卡
	player = new Player();
	level = new Level();
	/*---Revis---*/
	witch = new Witch();
	/*---Revis---*/
}

DataCenter::~DataCenter() {
	delete player;
	delete level;
	delete witch;

	for(CloseMonster *&m : closeMonsters) {
		delete m;
	}

	for(Witch_bullet *&wb:witchBullets)
	{
		delete wb;
	}
}
