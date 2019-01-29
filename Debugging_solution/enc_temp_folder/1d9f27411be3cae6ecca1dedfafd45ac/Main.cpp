#include "Scene.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

char* random_192_string();

int main(void) {

	Scene scenario;
	srand(time(NULL));
	//scenario.load_on_map(random_192_string());
	//scenario.print_current_map();

	Map * mapa = new Map(12, 16);
	char * string = random_192_string();
	printf("%s\n", string);
	mapa->load_on_map(string);
	for (int i = 0; i < 192; i++)
		mapa->print_cell(i / 16, i % 16);
	getchar();
	return 0;
}

char* random_192_string() {
	char posibles_letras[7] = { 'T','N','P','G','C','F','E' };		
	char * string_resultado = new char[193];

	for (int i = 0; i < 192; i++){
		string_resultado[i] = posibles_letras[rand() % 7];
	}
	string_resultado[192] = 0;
	return string_resultado;
}
