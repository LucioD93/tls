#include "utilidades.h"

// Definicion de mensajes base
const char *MENSAJE_ERROR_AYUDA = "Error! - La opcion -h excluye las demas opciones";
const char *MENSAJE_AYUDA = "Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida] \n-h: Muestra por pantalla un mensaje de ayuda, excluye del resto de opciones\n-n i: Nivel de concurrencia solicitado (uno por defecto)\n-d directorio: directorio desde donde calcula el espacio utilizado (actual por defecto)\nsalida: Archivo con lista de directorios y el espacio ocupado por los archivos regulares (salida estandar por defecto)";
const char *MENSAJE_ERROR_ABRIR_ARCHIVO = "Error! - No se pudo abrir archivo";
const char *MENSAJE_ERROR_ARGUMENTOS = "Error! Maximo de argumentos superado\n Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida]";


// Se verifica la cantidad de argumentos recibida
void verificar_argumentos(int cantidad) {
	if (cantidad > 6) {
		printf("%s\n", MENSAJE_ERROR_ARGUMENTOS);
		exit(1);
	}
}

void help_handler(int h, int cantidad){
	if (h == 1 && cantidad > 2) {
		printf("%s\n", MENSAJE_ERROR_AYUDA);
		exit(1);
 	}	
	if (h == 1) {
		printf("%s\n",MENSAJE_AYUDA);
		exit(0);
	} 	
}

FILE *outpot_ready(int opts, int cant, char** arr){
	if (opts < cant) {
		if ((salida = fopen(arr[opts], "w")) == NULL) {
			printf("%s %s\n",MENSAJE_ERROR_ABRIR_ARCHIVO, arr[opts]);
			exit(1);
		}
		else {
			printf("Salida: %s\n", arr[opts]);
			return salida;
		}
	}

	if (salida == NULL) {
		printf("Salida estandar\n");
	}

	return salida;
}