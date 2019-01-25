#include "Scene.h"
 
Scene::Scene():Observable(Observable_type::SCENARIO)
{
	this->game_finished = false;
	this->game_started = false;
	this->check_local_action = false;		//see where this flag is turn on or off
	this->has_to_draw = false;
	this->action_from_allegro = NULL;

	load_maps(); //levanto los CVS, construyo los mapas y los cargo en el vector
}


Scene::~Scene()
{

	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		delete (*it);
	}
}



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action) {
	
}



void Scene::load_maps() {

	//load_vectors with txt
	//this->actual_map = maps.begin();  //asign iterator to the first map
	this->actual_map = 1;

}

void Scene::gameInit() {	

	this->game_started = true;	//indica que todo inicializo correctamente y entonces debe empezar a funcionar la FSM.
	notify_obs();
	this->game_started = false;

}



EventPackage * Scene::give_me_my_allegro_event() {
	return this->action_from_allegro;
}

Character_type Scene::give_me_my_player() {

	return this-> my_player;
}
Character_type Scene::give_the_other_player() {

	return this->other_player;

}

void Scene::set_new_allegro_event(EventPackage * new_event) {
	 this->action_from_allegro= new_event;
}


bool Scene::game_is_finished() {
	return this->game_finished;
}
void Scene::finish_game() {
	this->game_finished = true;
}


//analizo jugadas externas e internas relacionadas a scene
bool Scene::is_the_action_possible(EventPackage * package_to_be_analyze) { 

	bool is_the_action_possible = true;

	//fijarse si no son iguales los eventos que llegan por net, los de soft y los de allegro
	//creo que son iguales, despu��es seguir flujo y cheuqearlo


	if (package_to_be_analyze->is_this_a_local_action()) //analisis de todo paquete generado por allegro
	{

		//analysis
		is_the_action_possible = check_action(package_to_be_analyze); //funci�n aparte que chequea realemnte para mayor prolijidad
		
		if (is_the_action_possible)
			package_to_be_analyze->is_this_event_package_is_correct(true);  //valido el EventPackage
		else
			package_to_be_analyze->is_this_event_package_is_correct(false);  //invalido el EventPackage

	}
	else //analisis de todo pquete que llega por nwt
	{
		//analysis


		if (is_the_action_possible)
			package_to_be_analyze->is_this_event_package_is_correct(true);  //valido el EventPackage
		else
			package_to_be_analyze->is_this_event_package_is_correct(false);  //invalido el EventPackage
	}

	//if (is_the_action_possible) al pedo no? EventsCommunicationObserver::update() ya tiene el paquete
		//this->package_to_be_appended = package_to_be_analyze;


	return is_the_action_possible;
}

bool Scene::check_action(EventPackage * package_to_be_analyze) {

	//hacer funci�n chequeo
	return true;
}



bool Scene::do_you_have_to_draw() {

	return this->has_to_draw;
}


