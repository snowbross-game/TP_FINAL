#include "Player.h"
#include "PlayerActionsFSM.h"
#include "CharacterActionsEventGenerator.h"
#include "PlayerActionsFSMDRAWObserver.h"

//agr�go un bool para saber, desde scene que tiene el dato si es tom o nick

Player::Player(unsigned int id,bool is_nick, Sense_type sense) :Character(id, sense)
{
	if (is_nick)
		printable = Item_type::NICK;
	else
		printable = Item_type::TOM;

	PlayerActionsFSM* fsm = new PlayerActionsFSM(this);
	CharacterActionsEventGenerator* ev_gen = new CharacterActionsEventGenerator();
	fsm->add_observer(new PlayerActionsFSMDRAWObserver(fsm, ev_gen, this));
	player_handler = new EventHandler(fsm, ev_gen);
}


Player::~Player()
{
}

bool Player::is_player() {
	return true;
}
void Player::revive() {
	if(lives > 0)
		dead = false;
}


void Player::die()
{
	lose_life();
	dead = true;
}
void Player::lose_life()
{
	if (lives > 0)
		lives--;
	
}

