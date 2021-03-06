#pragma once
#include "Observer.h"
#include "ProyectilesActionsFSM.h"
#include "DRAW.h"
#include "Proyectile.h"

class ProyectilesActionsFSMDRAWObserver : public Observer
{
public:
	ProyectilesActionsFSMDRAWObserver(ProyectilesActionsFSM* fsm, EventGenerator* ev_gen, Proyectile* proyectile);
	~ProyectilesActionsFSMDRAWObserver();

	void update();
private:

	ProyectilesActionsFSM * fsm = NULL;
	Proyectile* proyectile = NULL;
	DRAW* drawer = NULL;
	EventGenerator* ev_gen = NULL;
	PROYECTILE_STATE curr_state;
	bool first_update = true;
};

