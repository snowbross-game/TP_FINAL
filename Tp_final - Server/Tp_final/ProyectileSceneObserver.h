#pragma once
#include "Scene.h"
#include "ProyectilesActionsFSM.h"

class ProyectileSceneObserver : public Observer
{
public:
	ProyectileSceneObserver(Proyectile* proy, Scene * scenario);
	~ProyectileSceneObserver();
	void update();

protected:
	Proyectile * proy = NULL;
	void perform_logical_movement();
private:
	Scene * scenario = NULL;
	EventGenerator* ev_gen = NULL;
	ProyectilesActionsFSM * fsm = NULL;

	void perform_movement(Action_info action);
	void direction_to_deltas(Action_info* action);
};

