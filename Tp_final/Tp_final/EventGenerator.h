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

	EventGenerator(Allegro * al, Userdata* data);
	~EventGenerator();
	
	virtual EventPackage * fetch_event();
	void append_new_event(EventPackage* ev_pack);
	//In case an error ocurred and there are pending events to be run by the fsm
	virtual void empty_all_queues();
protected:
	std::vector<std::queue<EventPackage*>*> event_queues;

private:

};

