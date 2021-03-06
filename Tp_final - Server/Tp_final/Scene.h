#pragma once
#include "Userdata.h"
#include "Allegroclass.h"
#include "general.h"
#include "Observable.h"
#include "Map.h"
#include <iostream>

using namespace std;
/*******************************************************************************
							ENUM CLASS STATE_TYPE
******************************************************************************/
class Scene : public Observable
{
public:

	void control_enemies();
	Scene(Userdata* data, Item_type my_player, Item_type his_player);
	~Scene();

	void gameInit();

/*****************************************************************************
	STATE OF THE GAME
******************************************************************************/
	//generadas por tommy para hacer mas facil el manejo de mapas
	bool both_players_dead();
	bool any_monsters_left();
	bool did_we_win();  //I�m client, analyze if the game was won by the players
	bool did_we_lose(); //I�m client, analyze if the game was lost by the players

	bool game_is_finished();
	void finish_game();			//ends the game

	//Getters

	//player information
	Item_type give_me_my_player();
	Item_type give_the_other_player();
	Player * get_player(Item_type player_to_be_found);

	Action_info give_me_my_enemy_action(bool is_initializing);

/*******************************************************************************
	MOVEMENTS
******************************************************************************/

	//checkers
	bool check_if_has_to_fall(Character* charac);
	void check_current_game_situation();
	bool is_the_action_possible(Action_info * package_to_be_analyze, bool map_thing_check); //wrap for a clearer implementation of check_Action

	//Executing functions
	void execute_action(Action_info * action_to_be_executed, bool & should_be_hit);
	void execute_proyectile(Proyectile* proyectile_to_be_executed, bool & should_hit);
	Position shortest_movement_2_nearest_player(PurpleGuy* purple_guy);

	void control_enemy_actions();
	void control_all_actions();
/*******************************************************************************
	OPERATING OVER MAPS
******************************************************************************/

	void load_new_map(bool is_client, const char * the_map =NULL, char the_checksum=NULL );
	bool is_the_map_okay(const char * the_map , char the_checksum );
	void load_new_graphic_level();
	const char * give_me_the_map_info();

	vector <Map*> maps;
	int actual_map;

	void load_action_on_character(Action_info action);
	void load_action_on_projectile(Action_info action);
/*******************************************************************************
	FLAGS FOR OBSERVERS
******************************************************************************/
	bool game_started = false;
	bool game_finished = false;
	bool initializing = false;
	bool enemys_ready = false;
	bool we_lost = false;
	bool we_won = false;
	bool check_local_action = false;		//see where this flag is turn on or off
	bool new_enemy_action = false;
	bool should_hit = false;
	bool load_graphic_level = false;

	void append_new_auxilar_event(Action_info new_action_info);

	std::queue<Action_info>* assistant_queue;

	void append_graphic_facility(void* drawer);

private:
	void * graphics = NULL;

	unsigned char make_checksum(const char * CSV_map_location);

	//map information
	const char * give_me_the_CSV(unsigned int actual_map);

	//checkers
	bool check_move(Action_info * package_to_be_analyze, bool character_check);
	Direction_type load_direction(Position * extern_destination, Character* the_one_that_moves, bool* out_of_range);
	bool check_attack(Action_info * package_to_be_analyze, bool proj_check);
	bool check_enemy_action(Action_info * package_to_be_analyze);
	bool check_proy_move(Action_info * Action_info_to_be_checked);

/*******************************************************************************
	CONTROLLER FUNCTIONS
******************************************************************************/


	//executers
	void execute_move(Action_info * move_to_be_executed, bool & should_die);
	void execute_attack(Action_info * attack_to_be_executed);
	void execute_enemy_action(Action_info * enemy_action_to_be_executed, bool & should_be_hit);
	void execute_proy_move(Action_info * action_to_be_executed, bool & should_be_hit);

	//EventPackage* action_from_allegro; //se lo guarda cuando se llama a draw, no esta chequeado. Se lo manda despues a ScenarioEventsObserver::update() para chquearlo
	Action_info action_to_be_loaded;

	unsigned int points;
	Item_type my_player;
	Item_type other_player;

	vector<Player*>* curr_players;
	vector<Enemy*>* curr_enemies;
	vector<Proyectile*>* curr_proyectiles;

	Action_info enemy_action_info;

	Player* find_nearest_player(int pos_x, int pos_y);

	Userdata* data;
	int curr_enemy_to_act_on = 0;
};
