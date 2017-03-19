#ifndef utilidades
#define utilidades

	// Importacion de librerias externas
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
	#include <libgen.h>

	// Constantes
	#define BUFSIZE 4096

	// Declaracion de mensajes base
	extern const char *MENSAJE_ERROR_AYUDA;
	extern const char *MENSAJE_AYUDA;
	extern const char *MENSAJE_ERROR_ABRIR_ARCHIVO;
	extern const char *MENSAJE_ERROR_ARGUMENTOS;
	extern const char *MENSAJE_ERROR_ABRIR_DIR;

	// Estructura para definir una lista de directorios a ser explorados
	// Se manejara la estructura como una cola
	typedef struct _nodo {
		char *directorio;
		struct _nodo *siguiente;
	} nodo;

	// Estructura que contiene el numero de archivos y los bytes ocupados por estos
	typedef struct _respuesta {
		int numeroDeArchivos;
		int numeroDeBytes;
	} respuesta;

	// Variables globales
	// Apuntadores usados para la cola global de directorios
	nodo *cabeza;
	nodo *cola;

	// Archivo de salida
	FILE *salida;

	// contadores de archivos
	int numeroDeHilos;
	char *directorio;

	// Funciones a utilizar
	void verificar_argumentos(int);
	void help_handler(int , int);
	FILE *outpot_ready(int , int, char**);
	char *working_dir();
	void tls(int, FILE*, char*);

#else
#endif