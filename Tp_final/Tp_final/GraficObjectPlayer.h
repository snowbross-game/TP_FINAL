#pragma once
#include "GraficObject.h"


enum PLAYER_TYPE { TOM, NICK };

enum PLAYER_STATE { player_WALKING, player_JUMPING, player_JUMPING_FOWARD, player_IDLE, player_ATTACKING, player_FALLING , player_PUSHING, player_DYING};


class Obj_Graf_Player :
	public Obj_Graf
{
public:
	Obj_Graf_Player();
	Obj_Graf_Player(double ID, PLAYER_TYPE type);		// se setea la velorcidad del player
	~Obj_Graf_Player();

	void draw();
	void startDraw(Direction dir, void *estado, POINT& pos);
	void destroy();

private:
	PLAYER_STATE state;
	PLAYER_TYPE type;
	void loadBitmap(PLAYER_TYPE type);						// se pasa el tipo para saber que imagenes cargar
	unsigned int attackActualImage;
	unsigned int dieActualImage;
	ALLEGRO_BITMAP ** walkImages = NULL;
	ALLEGRO_BITMAP ** jumpImages = NULL;
	ALLEGRO_BITMAP ** idleImages = NULL;
	ALLEGRO_BITMAP ** attackImages = NULL;
	ALLEGRO_BITMAP ** fallImages = NULL;
	ALLEGRO_BITMAP ** pushImages = NULL;
	ALLEGRO_BITMAP ** dieImages = NULL;
};