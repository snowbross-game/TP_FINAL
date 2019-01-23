#pragma once
#include "Userdata.h" //Data usage
#include "FSM_Class.h"
#include "Communication.h"
#include "Allegroclass.h"
#include "EventPackage.h"
#include <queue> 




class EventGenerator
{
public:

	EventGenerator(Allegro * al, FSM * fsm, Userdata* data);
	~EventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;


	void append_new_net_event(EventPackage* new_ev_pack);
	void append_new_soft_event(EventPackage* new_ev_pack);
	void append_new_allegro_event(EventPackage* new_ev_pack);
	EventPackage * fetch_event_al();
	EventPackage * fetch_event_net();
	EventPackage * fetch_event_soft();

protected:
	
	ALLEGRO_EVENT_QUEUE * al_queue;				//Deber�a estar en clase allegro o por ah�

	std::queue<EventPackage*>* soft_queue;		//cola para eventos de software.
	std::queue<EventPackage*>* net_queue;		//cola para eventos de networking.
	std::queue<EventPackage*>* allegro_queue;		//cola para eventos de networking.

	ALLEGRO_TIMER * time_out_timer;  // has to be moved to allegro.cpp??
	FSM * my_fsm;
	Userdata * my_user_data;


	unsigned int time_out_count;

private:

};

