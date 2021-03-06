#pragma once
#include "Userdata.h"

enum class Action_info_id{ MOVE, ATTACK, ACTION_REQUEST, ENEMY_ACTION, DIE, HIT, PROY_MOVE, None};
struct Action_info {

	Action_info_id my_info_header= Action_info_id::None;
	bool is_local;
	bool finished_loading; //For ENEMYS_LOADED_EventPackage
	unsigned int id;
	int final_pos_x;
	int final_pos_y;
	Action_type action;
	Direction_type my_direction;
	Item_type my_character;
	bool valid = false;
};

