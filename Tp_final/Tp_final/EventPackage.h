#pragma once
#include "Userdata.h"
#include <stdint.h> 
#include <cstring>

typedef unsigned int uint;
typedef unsigned char uchar;



enum class Event_type  //Events that are usde by the internal function of the program 
{
	END_OF_TABLE,

	//ACK:
	ACK,

	//LOCAL_QUIT:Evento de allegro de quit, tiene que ser enviado por networking al otro usuario
	LOCAL_QUIT,

	//EXTERN_QUIT:Evento de networking de quit
	EXTERN_QUIT,

	//LOCAL_ACTION: Evento generado por allegro pero no ejecutado por la maquina,falta analizar
	MOVE,

	//EXTERN_ACTION   Es un MOVE/ATTACK del servidor que llega por networking siendo cliente
	ATTACK,

	//ACTION_REQUEST   //action request generado por el cliente que no fue chequeado
	ACTION_REQUEST,

	//ERROR: Evento de software cuando se produce un error interno, diversos origenes
	ERROR1,

	//NAME_IS: 
	NAME_IS,

	//NAME:
	NAME,

	//MAP_IS:
	MAP_IS,

	//ENEMY_ACTION: El servidor crea una enemy action
	ENEMY_ACTION,

	//ENEMYS_LOADED: Recibi todos los enemy  action como para poder empezar el juego
	ENEMYS_LOADED,

	//GAME_START:
	GAME_START,

	//WE_WON
	WE_WON,

	//PLAY_AGAIN
	PLAY_AGAIN,

	//FINISHED_LEVEL
	FINISHED_LEVEL,

	//GAME_OVER
	GAME_OVER,

	//START_COMMUNICATION: Evento de software generado cuando se inicilizo todo correctamente, el servidor esta listo para inicilizar
	START_COMMUNICATION,

	NO_EVENT,

	GOT_HIT,

	MOVE_TICKED,

	IMPACT_TICKED,
	DISAPPEARED
};


class EventPackage
{
public:
	EventPackage(Event_type event, bool is_local = NULL);
	Event_type give_me_your_event_type();
	bool is_this_a_local_action();


protected:
	Event_type my_internal_event;
	bool local_action;

};

class Action_EventPackage
{
public:
	Action_EventPackage(unsigned char fil_de, unsigned char col_de);
	Action_EventPackage(Direction_type direction_type);

	unsigned char give_me_your_destination_row();
	unsigned char give_me_your_destination_column();
	void set_destination_row(unsigned char my_destination_row);
	void set_destination_column(unsigned char my_destination_column);
	Direction_type give_me_your_direction();
	void set_direction(Direction_type new_direction = Direction_type::None);


private:
	unsigned char destination_row;
	unsigned char destination_column;
	Direction_type my_direction;
};

/******************************************************************************
*******************************************************************************
ACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACK_EventPackage : public EventPackage
{
public:
	ACK_EventPackage();

};

/******************************************************************************
*******************************************************************************
LOCAL_QUIT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class LOCAL_QUIT_EventPackage : public EventPackage
{
public:
	LOCAL_QUIT_EventPackage();

};

/******************************************************************************
*******************************************************************************
EXTERN_QUIT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_QUIT_EventPackage : public EventPackage
{
public:
	EXTERN_QUIT_EventPackage();

};

/******************************************************************************
*******************************************************************************
MOVE_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class MOVE_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	MOVE_EventPackage(Direction_type direction_type); //local MOVE
	MOVE_EventPackage(unsigned char fil_de, unsigned char col_de);			//extern MOVE
	MOVE_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de);		//MOVE to be send by networking made from an AR

	Item_type give_me_the_character();
	void set_character(Item_type the_one_that_moves);

private:
	Item_type character;
};

/******************************************************************************
*******************************************************************************
ATTACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ATTACK_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	ATTACK_EventPackage(); // local ATTACK
	ATTACK_EventPackage(unsigned char fil_de, unsigned char col_de);			//extern ATTACK
	ATTACK_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de);		//ATTACK to be send by networking made from an AR

	Item_type give_me_the_character();
	void set_character(Item_type the_one_that_moves);

private:
	Item_type character;


};


/******************************************************************************
*******************************************************************************
ACTION_REQUEST_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	ACTION_REQUEST_EventPackage(Action_type the_action, Direction_type direction); //local ACTION_REQUEST
	ACTION_REQUEST_EventPackage(Action_type the_action, char fil_de, char col_de); //extern ACTION_REQUEST
	Action_type give_me_the_action();


private:
	Action_type action;

};


/******************************************************************************
*******************************************************************************
ERROR_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ERROR_EventPackage : public EventPackage
{
public:
	ERROR_EventPackage(bool is_local);
	bool is_this_a_local_error();

private:
	bool local_error;  //For the FSM recogniztion analyze_error() function

};


/******************************************************************************
*******************************************************************************
NAME_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class NAME_EventPackage : public EventPackage
{
public:
	NAME_EventPackage();

};

/******************************************************************************
*******************************************************************************
				NAME_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class NAME_IS_EventPackage : public EventPackage
{
public:
	NAME_IS_EventPackage(bool is_local, uchar namelenght, const char * newname);
	uchar get_name_lenght();
	char * give_me_your_name();

private:
	uchar count;
	char * Name; // without terminator
};




/******************************************************************************
*******************************************************************************
			MAP_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class MAP_IS_EventPackage : public EventPackage
{
public:
	MAP_IS_EventPackage(bool is_local, const char * themap, char checksum);
	char * give_me_the_map();
	char give_me_the_checksum();

private:
	char * map;
	char Checksum;
};

/******************************************************************************
*******************************************************************************
			ENEMY_ACTION_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class ENEMY_ACTION_EventPackage : public EventPackage
{
public:
	ENEMY_ACTION_EventPackage(bool is_local, uchar the_MonsterID, Action_type the_action, char fil_de, char col_de);
	ENEMY_ACTION_EventPackage(EA_info * ea_info);
	uchar give_me_the_monsterID();
	Action_type give_me_the_action();
	char give_me_the_destination_row();
	char give_me_the_destination_column();
private:
	uchar MonsterID;
	Action_type action;
	char destination_row;
	char destination_column;
};

/******************************************************************************
*******************************************************************************
ENEMYS_LOADED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class ENEMYS_LOADED_EventPackage : public EventPackage
{
public:
	ENEMYS_LOADED_EventPackage();

};


/******************************************************************************
*******************************************************************************
GAME_START_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class GAME_START_EventPackage : public EventPackage
{
public:
	GAME_START_EventPackage();

private:

};


/******************************************************************************
*******************************************************************************
WE_WON_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class WE_WON_EventPackage : public EventPackage
{
public:
	WE_WON_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
PLAY_AGAIN_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class PLAY_AGAIN_EventPackage : public EventPackage
{
public:
	PLAY_AGAIN_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
GAME_OVER_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class GAME_OVER_EventPackage : public EventPackage
{
public:
	GAME_OVER_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
START_COMMUNICATION_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class START_COMMUNICATION_EventPackage : public EventPackage
{
public:
	START_COMMUNICATION_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
FINISHED_LEVEL_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class FINISHED_LEVEL_EventPackage : public EventPackage
{
public:
	FINISHED_LEVEL_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
NO_EVENT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class NO_EVENT_EventPackage : public EventPackage
{
public:
	NO_EVENT_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
END_OF_TABLE_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class END_OF_TABLE_EventPackage : public EventPackage
{
public:
	END_OF_TABLE_EventPackage();

private:

};
