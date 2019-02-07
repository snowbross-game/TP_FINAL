#include "PurpleGuy.h"

double PurpleGuy::moving_speed = 300;

PurpleGuy::PurpleGuy(unsigned int id) :Enemy(id)
{
	printable = Item_type::PURPLE_GUY;
}


PurpleGuy::~PurpleGuy()
{
}

/******************************************
**************act**************************
*******************************************
*act returns the Enemy Action information of the enemies next action. This method doesn't
*execute the action, it just gives the information of the Enemy's next action so that it will be executed by correct Class (Scene).
*Only valid actions will be returned.
*	INPUT:
*		1) void.
*	OUTPUT:
*		EA_info containing all the information of the Enemy's next action. This action will always be local as the
*		information is generated locally.
*/
EA_info PurpleGuy::act(){

	EA_info returnable_EA;
	al_stop_timer(acting_timer);
	double sample = acting_probabilities(generator);
	double timer_speed;

	while (!returnable_EA.valid){
		if ((sample >= 0) && (sample <= 0.6)) {			//0.6 probability
			move_to_nearest_player(&returnable_EA);
			timer_speed = 0;
		}
		else if ((sample >= 0.6) && (sample <= 0.9)) {							//0.3 probability
			sample = acting_probabilities(generator);

			while (!returnable_EA.valid) {
				if ((sample >= 0) && (sample <= 1.0 / 3.0)) 						//1/3 probability
					jump(&returnable_EA) ? timer_speed = 0 : sample = 0.5;

				else if ((sample >= 1.0 / 3.0) && (sample <= 2.0 / 3.0)) 			//1/3 probability
					move_in_opposite_direction(&returnable_EA) ? timer_speed = 0 : sample = 0.9;
				else																//1/3 probability
					move_in_same_direction(&returnable_EA) ? timer_speed = 0 : sample = 0.1;
			}
		}
		else if ((sample >= 0.9) && (sample <= 1.0)) {		//0.1 probability
			stay_still(&returnable_EA);
			timer_speed = 0;
		}
	}

	al_set_timer_speed(acting_timer, timer_speed);
	al_start_timer(acting_timer);
}

/******************************************
**************move_to_nearest_player*******
*******************************************
*move_to_nearest_player returns modifies an EA_info structure so that the Enemy Action will make the PurpleGuy move
*to the nearest player, taking the shortest route towards it.
*	INPUT:
*		1) next_enemy_action : EA_info to be modified.
*	OUTPUT:
*		void.
*/
void PurpleGuy::move_to_nearest_player(EA_info * next_enemy_action) {
	EA_info_common_filling(next_enemy_action);

	calculate_shortest_distance = true;
	notify_obs();
	calculate_shortest_distance = false;

	next_enemy_action->final_pos_x = next_movement_2_nearest_player.fil;
	next_enemy_action->final_pos_y = next_movement_2_nearest_player.col;
	next_enemy_action->action = Action_type::Move;
	next_enemy_action->valid = true;
}


/******************************************
**************set_next_movement_2_nearest_player*******
*******************************************
*set_next_movement_2_nearest_player sets the final position in which the PurpleGuy should move as a result of calling
*move_to_nearest_player method. This method is designed to be called by an Observer.
*	INPUT:
*		1) final_pos : position the PurpleGuy guy should move to after calling move_to_nearest_player();
*	OUTPUT:
*		void.
*/
void PurpleGuy::set_next_movement_2_nearest_player(Position final_pos) {
	this->next_movement_2_nearest_player = final_pos;
}

