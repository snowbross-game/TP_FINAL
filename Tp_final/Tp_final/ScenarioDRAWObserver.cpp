#include "ScenarioDRAWObserver.h"


ScenarioDRAWObserver::ScenarioDRAWObserver(Scene* scenario, DRAW* drawer)
{
	this->scenario = scenario;
	this->drawer = drawer;
}


ScenarioDRAWObserver::~ScenarioDRAWObserver()
{
}

void ScenarioDRAWObserver::update() {
	/*
	if (scenario->new_character) {
		lastly_created_character = scenario->get_lastly_created_character();
		lastly_created_character->add_observer(new CharacterDRAWObserver(lastly_created_character, drawer));

	}
	*/
}