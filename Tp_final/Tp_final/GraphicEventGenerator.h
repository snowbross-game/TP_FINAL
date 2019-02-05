#pragma once
#include "EventGenerator.h"

class GraphicEventGenerator: public EventGenerator
{
public:
	GraphicEventGenerator(Allegro * al, Userdata* data);
	~GraphicEventGenerator();

	edge_t* Iddle_state = NULL;

	edge_t* Moving_state = NULL;
	edge_t* _state = NULL;

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

