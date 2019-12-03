
#include "parser.h"


/**********************
*    parseCALLBACK    *
***********************
*SYNTAX: chequea que los valores ingresados por el usuario sean correctos y actualiza la estructura userData apropiadamente con la informaci�n correspondiente.
*INPUT:
*	-key : puede ser tanto una clave como un par�metro seg�n si el parser detect� una opci�n o un par�metro.
*	-value : valor correspondiente a la clave para esa opci�n. NULL si key corresponde a un par�metro.
*	-userData : puntero a void a una estructura en la cual se aloja la informaci�n de la data ingresada por usuario.
*
*OUTPUT:
*	- si la interpretaci�n de las opciones y/o par�metros es correcta, se devolver� un 1. En caso de que el procesamiento deba detenerse debido
*     al hallazgo de una opci�n o par�metro inv�lido, se devolver� un 0.
*/
int parseCallback(char *key, char *value, void *userData);



typedef int(*pCallback) (char *, char*, void *);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int parseCallback(char *key, char *value, void *userData)
{

	infoType *myData = (infoType *)userData;

	int validInput = 0;

	if (key != NULL)				//si recibe key y valor
	{
		if (!strcmp(key, "ip"))               //filtra los keys validos
		{
			/* deberia fijarme que cumpla con el protocolo!!!
			if (cumple con protocolo)       
			{
				validInput = 1;
			}
			else
				validInput = 0;
			*/
			std::string input; 
			input = std::string(value);
			myData->ip = input;
			if (myData->receivedSth){
				validInput = 0;
			}
			else {
				myData->receivedSth = true;
				myData->cliente = true;
				validInput = 1;
			}
		}
		else
			validInput = 0;
	}
	else                                            //en caso de podeer el key en NULL, es un parametro
	{
		if (myData->receivedSth) {
			validInput = 0;
		}
		else {
			myData->receivedSth = true;
			myData->cliente = false;
			validInput = 1;
		}
		
	}
	return validInput;
}