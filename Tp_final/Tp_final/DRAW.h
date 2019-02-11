#pragma once
#include "GraficObjectPlayer.h"
#include "GraficObjectEnemy.h"
#include "GraficObjectProjectile.h"
#include "GraficObjectBall.h"
#include <iostream>
#include <map>
#include <vector>

#include "AllegroClass.h"

using namespace std;

class DRAW
{
public:
	DRAW();
	~DRAW();
//	bool init();
	Obj_Graf_Player* createObjGraf(double ID, PLAYER_TYPE type);						// crea un objeto grafico del tipo deseado y se lo añade al mapa de objetos
	Obj_Graf_Enemy* createObjGraf(double ID, ENEMY_TYPE type);
	Obj_Graf_Projectile* createObjGraf(double ID, PROYECTILE_TYPE type);
	Obj_Graf_Ball* createObjGraf(double ID, BALL_TYPE type);
	template <typename T> void startDraw(T state, double ID, Direction dir, POINT_& pos);		// inicia la secuencia de dibujo de un objeto grafico
	void draw();															// esta funcion refresca los objetos graficos activos
	void destroyObj(double ID);
	void destroyAll();														// destruye todos los objetos graficos
	void setLevel(unsigned int level);
	bool secuenceOver(double ID);

private:
	map<double, Obj_Graf*> mapObjGraf;									// mapa de objetos graficos
	ALLEGRO_BITMAP * floor = NULL;
	ALLEGRO_BITMAP * empty = NULL;
	ALLEGRO_BITMAP ** backgrounds = NULL;
	vector<string> levels;
	unsigned int level;
	void drawLevel();
};



template<typename T>
inline void DRAW::startDraw(T state, double ID, Direction dir, POINT_& pos)
{
	void *vp;
	vp = &state;
	mapObjGraf[ID]->startDraw(dir, vp, pos);
}
