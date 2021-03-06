#pragma once
#include "Userdata.h"
#include "general.h"

class MapThing
{

public:

	MapThing(unsigned int id, bool is_nothing, Sense_type sense);

	~MapThing();
	
	virtual bool is_proyectile();
	virtual bool is_enemy();
	virtual bool is_player();
	bool is_floor();			//este se decide inmediatamente, no necesita virtual

	Thing_Type get_map_thing_type();

	unsigned int id;

	void set_printable(Item_type printable);
	Item_type get_printable();
	void set_sense(Sense_type sense);
	Sense_type get_sense();

	int pos_x;
	int pos_y;

	
protected:
	Item_type printable;
	Sense_type my_sense;

private:
};

