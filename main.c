/*
 * Archivo: main.c
 * Autores:
 *          Sergio Medina 09-11259
 *          Lucio Mederos 13-10856
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <dirent.h>

int main(int argc, char** argv){

    // Se verifican los argumentos
	//numeroArgumentos(argc);

	int hflag = 0;
	int nvalue = 0;
	char *dvalue = NULL;
	int n;

	opterr = 0;

    // Se procede a procesar las opciones
	while ((n = getopt(argc,argv, "hd:n:")) != -1){
		switch(n){
			case 'h':
		{
			hflag = 1;
				break;
			}
			case 'd':
			{
                	dvalue = optarg;
			break;
			}
			case 'n':
			{
				nvalue = atoi(optarg);
				break;
			}
			case '?':
			{
				if (optopt == 'n'){
					fprintf(stderr, "Opcion -%c requiere un argumactualo.\n", optopt);
				} else if (isprint(optopt)){
					fprintf(stderr, "Opcion desconocida '-%c'.\n", optopt);
				} else {
					fprintf(stderr, "Caracter desconocido '\\x%x'.\n", optopt);
				}
				return 1;
			}
			default:
			{
				abort();
			}
		}
	}

    // Si se pasa la opcion h no deben haber mas opciones
	if ((hflag == 1) && (argc > 2)) {
		fprintf(stderr, "La opcion '-h' es excluyactuale del resto de las opciones\n");
		exit(1);
	}

    // Se imprimen las opcines de UsoDisco y se finaliza la ejecucion
	if (hflag == 1){
		printf("UsoDisco Usage:\n");
		printf("./UsoDisco [-h] | [-n <i>] [-d <directorio>] [salida] \n");
		printf("-h: Muestra por pantalla un mensaje de ayuda, excluyactuale del resto de opciones\n");
		printf("-n i: Nivel de concurrencia solicitado (uno por defecto)\n");
		printf("-d directorio: directorio desde donde calcula el espacio utilizado (actual por defecto)\n");
		printf("salida: Archivo con lista de directorios y el espacio ocupado por los archivos regulares (salida estandar por defecto)\n");
		exit(1);
	}


	return 0;
}