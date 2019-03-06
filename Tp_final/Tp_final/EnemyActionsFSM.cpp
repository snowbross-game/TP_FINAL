#include "EnemyActionsFSM.h"


void do_nothing_enemy_r(void* data);
void check_got_hit_and_get_hit_r(void* data);
void partially_unfroze_r(void* data);
void freeze_r(void* data);
void unfroze_r(void* data);
void start_moving_snowball_r(void* data);
void snowball_move_r(void* data);
void enemy_die_r(void* data);
void start_got_hit_r(void*data);

EnemyActionsFSM::EnemyActionsFSM(Enemy* enemy): CharacterActionsFSM(enemy)
{
	this->enemy = enemy;
	set_states();

	this->actual_state = iddle_state;

	set_processes();
	create_all_timers();
}


EnemyActionsFSM::~EnemyActionsFSM()
{
	delete freezing_state;
	delete frozen_state;
}
void EnemyActionsFSM::set_states()
{

	expand_state(iddle_state, { Event_type::GOT_HIT, freezing_state, start_got_hit_r });

	freezing_state = new std::vector<edge_t>();
	frozen_state = new std::vector<edge_t>();

	freezing_state->push_back({ Event_type::GOT_HIT, freezing_state, check_got_hit_and_get_hit_r});
	freezing_state->push_back({ Event_type::FROZE, frozen_state, freeze_r });
	freezing_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	freezing_state->push_back({ Event_type::UNFROZE, iddle_state, unfroze_r });
	freezing_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_enemy_r });

	frozen_state->push_back({ Event_type::GOT_HIT, frozen_state, start_moving_snowball_r });
	frozen_state->push_back({ Event_type::MOVE, frozen_state, snowball_move_r });
	frozen_state->push_back({ Event_type::DIED, dead_state, enemy_die_r });
	frozen_state->push_back({ Event_type::END_OF_TABLE, frozen_state, do_nothing_enemy_r });
}


void EnemyActionsFSM::set_processes() {

}
void EnemyActionsFSM::create_all_timers() {

}

void EnemyActionsFSM::got_hit() {
	
	enemy->be_hit();

}
void EnemyActionsFSM::start_got_hit() {

	start_freezing_timer();
}

void do_nothing_enemy_r(void* data) {

}
void check_got_hit_and_get_hit_r(void* data) {
	(EnemyActionsFSM*)fsm = (EnemyActionsFSM*) data;
	fsm->got_hit();
}
void start_got_hit_r(void*data) {
	(EnemyActionsFSM*)fsm = (EnemyActionsFSM*)data;
	fsm->start_got_hit();
}

void partially_unfroze_r(void* data){

}
void freeze_r(void* data){

}
void unfroze_r(void* data){

}
void start_moving_snowball_r(void* data){

}
void snowball_move_r(void* data){

}

void enemy_die_r(void* data) {
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->obs_info.dying_graph = true;
	fsm->notify_obs();
	fsm->obs_info.dying_graph = false;
	fsm->kill_character();
}

std::vector<ALLEGRO_TIMER*> EnemyActionsFSM::get_all_my_timers(){
	
	std::vector<ALLEGRO_TIMER*> original_timers = CharacterActionsFSM::get_all_my_timers();
	//original_timers.push_back();
	return original_timers;
}