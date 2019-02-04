#include "LogicEventGenerator.h"


LogicEventGenerator::LogicEventGenerator(Allegro * al, Userdata* data): EventGenerator(al, data)
{
	al_key_queue = al->get_al_queue();
	time_out_timer = al->get_front_time_out_timer();
	time_out_count = 0;
	
	coordinate_scene_events_queue = al_create_event_queue();
	coordinate_scene_events_timer = al_create_timer(50.0 / 1000.0);
	al_register_event_source(coordinate_scene_events_queue, al_get_timer_event_source(coordinate_scene_events_timer));
	al_start_timer(coordinate_scene_events_timer);
	append_all_queues( (int) LogicQueues::TOTAL_QUEUES);
}


LogicEventGenerator::~LogicEventGenerator()
{
}

EventPackage * LogicEventGenerator::fetch_event()
{
	update_from_allegro_events();
	return EventGenerator::fetch_event();
}

void LogicEventGenerator::update_from_allegro_events() {
	update_from_allegro_keyboard_events();
	update_from_allegro_timer_events();
}
void LogicEventGenerator::update_from_allegro_keyboard_events() {

	ALLEGRO_EVENT * allegroEvent = NULL;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(al_key_queue, allegroEvent)) {			//tomo de la cola en caso de que no este vacia

		if (allegroEvent->type == ALLEGRO_EVENT_DISPLAY_CLOSE) {	//debo quittear porque mandaron a cerrar la pantalla				
			ev_pack = new LOCAL_QUIT_EventPackage();
		}
		else if (allegroEvent->type == ALLEGRO_EVENT_KEY_DOWN) {					//tecla presionada
			if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_UP) {

				if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT)

					if (my_user_data->my_network_data.is_client())
						ev_pack = new MOVE_EventPackage(Direction_type::Jump_Left);
					else
						ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Jump_Left);

				else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT)

					if (my_user_data->my_network_data.is_client())
						ev_pack = new MOVE_EventPackage(Direction_type::Jump_Right);
					else
						ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Jump_Right);
				else

					if (my_user_data->my_network_data.is_client())
						ev_pack = new MOVE_EventPackage(Direction_type::Jump_Straight);
					else
						ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Jump_Straight);
			}

			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_LEFT) {	//tecla izquierda

				if (my_user_data->my_network_data.is_client())
					ev_pack = new MOVE_EventPackage(Direction_type::Left);
				else
					ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Left);
			}

			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_RIGHT) {	//tecla derecha

				if (my_user_data->my_network_data.is_client())
					ev_pack = new MOVE_EventPackage(Direction_type::Right);
				else
					ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Move, Direction_type::Right);
			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_SPACE) {

				if (my_user_data->my_network_data.is_client())
					ev_pack = new ATTACK_EventPackage();
				else
					ev_pack = new ACTION_REQUEST_EventPackage(Action_type::Attack, Direction_type::None);

			}
			else if (allegroEvent->keyboard.keycode == ALLEGRO_KEY_Q) {
				ev_pack = new LOCAL_QUIT_EventPackage();
			}
		}
	}
	else
		ev_pack = new NO_EVENT_EventPackage();

	append_new_event(ev_pack,(int) LogicQueues::allegro);

}

void LogicEventGenerator::update_from_allegro_timer_events() {
	ALLEGRO_EVENT * allegroEvent = NULL;
	EventPackage * ev_pack = NULL;

	if (al_get_next_event(coordinate_scene_events_queue, allegroEvent)) {
		if (allegroEvent->type == ALLEGRO_EVENT_TIMER) {
			if (allegroEvent->timer.source == coordinate_scene_events_timer) {

			}
			else if (allegroEvent->timer.source == time_out_timer) {

			}
		}
	}

}

void LogicEventGenerator::empty_all_queues() {
	EventGenerator::empty_all_queues();
	al_flush_event_queue(al_key_queue);
	al_flush_event_queue(coordinate_scene_events_queue);
}
