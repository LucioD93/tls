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

	// Declaracion de mensajes base
	#define BUFSIZE 2048
	extern const char *MENSAJE_ERROR_AYUDA;
	extern const char *MENSAJE_AYUDA;
	extern const char *MENSAJE_ERROR_ABRIR_ARCHIVO;

	// Estructura para definir una lista de directorios a ser explorados
	// Se manejara la estructura como una cola
	typedef struct _nodo {
		char *directorio;
		struct _nodo *siguiente;
	} nodo;

	// Estructura para devolver el resultado del trabajo de un hilo y ser
	// imprimido en la salida
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
	void manejo_de_ayuda(int , int);
	FILE *output_ready(int , int, char**);
	char * get_directorio_actual();
	void tls(int, FILE*, char*);

#else
#endif
