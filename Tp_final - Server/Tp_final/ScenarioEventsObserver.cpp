#include "ScenarioEventsObserver.h"
#include <iostream>
#include <string.h>
using namespace std;

ScenarioEventsObserver::ScenarioEventsObserver(LogicEventGenerator * event_gen, Scene * scenario,FSM * fsm, Userdata * data)
{
	this->ev_gen = event_gen;
	this->scenario = scenario;
	this->my_fsm = fsm;
	this->my_user_data = data;
}


ScenarioEventsObserver::~ScenarioEventsObserver()
{
}

void ScenarioEventsObserver::update() {

	if (scenario->game_started){
		if (my_user_data->my_network_data.handshake) {
			if (my_user_data->my_network_data.is_client() == false)  //si es cliente carga el paquete que inicia la fsm
				ev_gen->append_new_event(new START_COMMUNICATION_EventPackage(), (int)EventGenerator::LogicQueues::soft);
			scenario->initializing = true;
		}
	}

	if (this->scenario->enemys_ready)
		ev_gen->append_new_event(new ENEMYS_LOADED_EventPackage(),(int)EventGenerator::LogicQueues::soft);
	
	if (this->scenario->we_won){
		if (!my_user_data->my_network_data.is_client()) //we do this ckeck here because in scene we don�t have that info
			ev_gen->append_new_event(new WE_WON_EventPackage(), (int)EventGenerator::LogicQueues::soft);
	}
	if (scenario->we_lost){
		if (!my_user_data->my_network_data.is_client()) //we do this ckeck here because in scene we don�t have that info
			ev_gen->append_new_event(new GAME_OVER_EventPackage(), (int)EventGenerator::LogicQueues::soft);
	}
	if (scenario->new_enemy_action) {
		Action_info new_enemy_action = scenario->give_me_my_enemy_action(false);
		ENEMY_ACTION_EventPackage* to_append = new ENEMY_ACTION_EventPackage(&new_enemy_action);
		ev_gen->append_new_event(to_append, (int)EventGenerator::LogicQueues::soft);
	}
	
}
