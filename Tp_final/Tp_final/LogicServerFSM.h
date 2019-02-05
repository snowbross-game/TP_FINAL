#pragma once
#include "FSM_Class.h"

class LogicServerFSM: public FSM
{
public:
	LogicServerFSM(Userdata * data);
	~LogicServerFSM();

private:

	/****************************
	states
	******************************/


	edge_t* Initial_state = NULL;

	edge_t* Naming_him_state = NULL;
	edge_t* Naming_me_state = NULL;

	edge_t* Waiting_for_ACK_name_state = NULL;

	edge_t* Waiting_for_map_state = NULL;
	edge_t* Waiting_for_ACK_map_state = NULL;

	edge_t* Waiting_for_enemy_actions_state = NULL;
	edge_t* Waiting_for_ACK_enemy_actions_state = NULL;

	edge_t* Waiting_for_game_start_state = NULL;
	edge_t* Waiting_for_ACK_game_start_state = NULL;

	edge_t* Playing_state = NULL;

	edge_t* Waiting_for_ACK_quit_state = NULL;

	edge_t* Waiting_for_ACK_playing_state = NULL;
	edge_t* Waiting_for_servers_response_state = NULL;

	edge_t* Waiting_if_the_client_wants_to_play_again = NULL;
	edge_t* Waiting_if_the_server_wants_to_play_again = NULL;
	edge_t* Waiting_if_the_user_wants_to_play_again = NULL;
};

