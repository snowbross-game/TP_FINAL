#pragma once
#include "Character.h"
class Player: public Character
{
public:
	Player(unsigned int id);
	~Player();

	unsigned int lives = 3;
	//unsigned int potion

	bool is_player();
	void move();
	void attack();
	void lose_life();
	void revive();
	void die();


};

