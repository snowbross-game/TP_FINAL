#ifndef PARSE_CMD_LINE_H

#define	PARSE_CMD_LINE_H


typedef int(*pCallback) (char *, char*, void *);


#define CANT_TIPOS_DE_ERROR 4		//este valor debera actualizarse cada vez que se agregue un nuevo tipo de error al enum siguiente.
enum tipos_de_errores { NO_KEY_ERROR = (-1) * CANT_TIPOS_DE_ERROR, NO_VALUE_ERROR, PARAMETERS_ERROR, PROCESSING_ERROR };



/*********************
*    parseCmdLine    *
**********************
*SYNTAX: revisara los parametros ingresados por linea de comando por el usuario y a trav�s de la funci�n de tipo pCallback actualizara userData con la informaci�n correspondiente.
*INPUT:
*	-argc : numero total de parametros que recibe el parser desde linea de comando, ingresado por usuario.
*	-argv : arreglo de strings, cada string con el parametro que deber� ser interpretado (dividido en par�metros y opciones) por el parser.
*	-p : funci�n de callback a trav�s de la cual se interpretar� el par�metro recibido y se modificar� la estructura en la cual se aloja la
*        informaci�n de la data ingresada por usuario.
*	-userData : puntero nulo a la estructura que contiene la informaci�n de la data ingresada por usuario.
*
*OUTPUT:
*	-si los datos fueron procesados correctamente, devuelve la cantidad de [opciones + par�metros] procesados. En caso de haberse hallado
*    un error, ser� devuelto un numero negativo, que indicara el tipo de error.
*/
int parseCmdLine(int argc, char *argv[], pCallback infoAnalysis, void *userData);

#endif