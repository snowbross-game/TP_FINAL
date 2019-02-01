#include "Scene.h"
 
Scene::Scene():Observable(Observable_type::SCENARIO)
{
	//flags
	this->game_finished = false;
	this->game_started = false;
	this->check_local_action = false;		
	this->has_to_draw = false;
	this->enemys_ready = false;
	this->we_won = false;
	this->we_lost = false;


	this->action_from_allegro = NULL;
	this->actual_map = 1;

}


Scene::~Scene()
{

}



void Scene::handle_movement(Character_id char_id, unsigned int id, Direction_type dir, Action_type action) {
	
}



void Scene::execute_action(EventPackage * action_to_be_executed)
{




	//Lastly, we analyze the current game_situation
	if (this->both_players_dead())
	{
		this->we_lost = true;
		notify_obs();
		this->we_lost = false;
	}
	if ((!this->both_players_dead())&&(!this->any_monsters_left())&&(this->actual_map==10))
	{
		this->we_won = true;
		notify_obs();
		this->we_won = false;
	}
}

void Scene::load_new_map(bool is_client, EventPackage* map_to_be_checked=NULL) {


		Map * new_map = new Map(12, 16);

	if (is_client) //The map came by networking, already checked
	{	
		//esto es lo que tenias antes, que por ahora no se condice con lo que programe de Map. despues coordinar conmigo para que esto funke.
		//Map * new_map = new Map(12, 16, ((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_map(), ((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_checksum());
		//por que no meter todo esto en el constructor?
		new_map->load_on_map((const char*)(((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_map()));
		new_map->load_checksum(((MAP_IS_EventPackage*)map_to_be_checked)->give_me_the_checksum());
		
		this->actual_map++;
	}
	else
	{	//I�m server, I�ve the map available
		new_map->load_on_map(give_me_the_CSV(actual_map));
		new_map->load_checksum(this->make_checksum(give_me_the_CSV(actual_map)));
		//maps->push_back(new Map(12, 16, give_me_the_CSV(actual_map),this->make_checksum(give_me_the_CSV(actual_map))));
	}

		maps->push_back(new_map);

}

//hace checksum , funci�n guido
unsigned char Scene::make_checksum(const char * CSV_map_location) {

	unsigned char local_checksum = 'd';

	return local_checksum;
}//despu�s usar esta funci�n que haga guido para el checksum de mapas que llegan para validarlos(hecho)


bool Scene::is_the_map_okay(EventPackage * map_to_be_checked)
{
	bool map_validation;
	unsigned char extern_checksum = ((MAP_IS_EventPackage *)map_to_be_checked)->give_me_the_checksum();
	unsigned char local_checksum = this->make_checksum(((MAP_IS_EventPackage *)map_to_be_checked)->give_me_the_map());

	if (local_checksum == extern_checksum)
		map_validation = true;
	else
		map_validation = false;
	
	return map_validation;
}

//funci�n que hacce guido, va al archivo, lo convierte a const char* y lo devuelve
const char * Scene::give_me_the_CSV(unsigned int actual_map) {

	const char * prueba=NULL;
	return prueba;
}

EventPackage* Scene::give_me_my_enemy_action(bool is_initializing){

	EventPackage* my_enemy_action_event = NULL;

	my_enemy_action_event=maps->at(this->actual_map)->give_me_my_enemy_action(is_initializing);

	if (my_enemy_action_event == NULL) //ENEMYS_LOADED MUST BE SENT
	{
		bool enemys_ready=true;
		notify_obs();
		bool enemys_ready = true;
	}


	return my_enemy_action_event;
}


EventPackage* give_me_my_enemy_action(bool is_initializing);


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

bool Scene::both_players_dead()
{
	std::vector<Player*>* players = maps[actual_map].get_all_players();
	bool all_dead = true;
	for (int i = 0; i < players->size(); i++) 
		if (!players->at(i)->is_dead()) {
			all_dead = false;
			break;
		}
	return all_dead;
}

bool Scene::any_monsters_left()
{
	std::vector<Enemy*>* monsters = maps[actual_map].get_all_enemies();

	bool any_left = false;
	for (int i = 0; i < monsters->size(); i++)
		if (!monsters->at(i)->is_dead()) {
			any_left = true;
			break;
		}

	return any_left;
}


bool Scene::game_is_finished() {
	return this->game_finished;
}

void Scene::finish_game() {
	this->game_finished = true;
	notify_obs();
	this->game_finished = false;
}


//analizo jugadas externas e internas relacionadas a scene
bool Scene::is_the_action_possible(EventPackage * package_to_be_analyze) { 

	bool is_the_action_possible = true;


	//analysis
	is_the_action_possible = check_action(package_to_be_analyze); //funci�n aparte que chequea realemnte para mayor prolijidad
		


	if (is_the_action_possible) //Implementaci�n al pedo por como est� hecho en FSMEventsObserver
			package_to_be_analyze->is_this_event_package_is_correct(true);  //valido el EventPackage
	else
			package_to_be_analyze->is_this_event_package_is_correct(false);  //invalido el EventPackage

	return is_the_action_possible;
}

bool Scene::check_action(EventPackage * package_to_be_analyze) {

	//hacer funci�n chequeo
	//unsigned char Map::make_checksum(const char * CSV_map_location) funci�n para chequear el map_is entrante
	return true;
}

bool Scene::did_we_win(EventPackage * package_to_be_analyze)
{
	bool we_won;

	if ((!this->both_players_dead()) && (!this->any_monsters_left()) && (this->actual_map == 10))
	{
		we_won = true;

	}
	else
		we_won = false;

	return we_won;
}

bool Scene::did_we_lose(EventPackage * package_to_be_analyze)
{
	bool we_lost;

	if (this->both_players_dead())
	{
		we_lost = true;
	}
	else
		we_lost = false;

	return we_lost;
}



bool Scene::do_you_have_to_draw() {

	return this->has_to_draw;
}

void Scene::append_new_auxilar_event(EventPackage* new_ev_pack) {
	assistant_queue->push(new_ev_pack);
}