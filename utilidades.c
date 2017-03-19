#include "utilidades.h"

// Definicion de mensajes base
const char *MENSAJE_ERROR_AYUDA = "Error! - La opcion -h excluye las demas opciones";
const char *MENSAJE_AYUDA = "Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida] \n-h: Muestra por pantalla un mensaje de ayuda, excluye del resto de opciones\n-n i: Nivel de concurrencia solicitado (uno por defecto)\n-d directorio: directorio desde donde calcula el espacio utilizado (actual por defecto)\nsalida: Archivo con lista de directorios y el espacio ocupado por los archivos regulares (salida estandar por defecto)";
const char *MENSAJE_ERROR_ABRIR_ARCHIVO = "Error! - No se pudo abrir archivo";
const char *MENSAJE_ERROR_ARGUMENTOS = "Error! Maximo de argumentos superado\n Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida]";
const char *MENSAJE_ERROR_ABRIR_DIR = "Error! - No se pudo abrir el directorio de trabajo";


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
			//printf("Salida: %s\n", arr[opts]);
			return salida;
		}
	}

	return salida;
}

char *working_dir(){
	if (directorio == NULL){
		char* cp;
		char* cwd = malloc (sizeof (char) * BUFSIZE);

		if(!(cp = getcwd(cwd, BUFSIZE))) {
			printf("%s\n",MENSAJE_ERROR_ABRIR_DIR);
		    exit(1);
		}

		return cwd;			
	} 
	else {
		// el peo es aqui xD
		char* actualpath = malloc(sizeof(char)*BUFSIZE);
		
		realpath(directorio, actualpath);

		return actualpath;
	}

//	return directorio;

}

// Funcion para verificar si un arhivo es oculto
int es_oculto(char *direccion) {
	char *comprobante = NULL;
	comprobante = strstr(direccion, ".");
	if (comprobante != direccion) {
		return 0;
	}
	return 1;
}

//Funcion para determinar si un string representa un directorio
int es_directorio(char* direccion){
	
	struct stat buffer;
	if (stat(direccion, &buffer)) {
		printf("No se pudo aplicar stat sobre %s\n", direccion);
	}
	return S_ISDIR(buffer.st_mode);
}

void encolar(char *directorio) {
	nodo *nuevo_nodo = (nodo*) malloc(sizeof(nodo));
	nuevo_nodo -> directorio = strdup(directorio);
	nuevo_nodo -> siguiente = NULL;

	if (cabeza == NULL && cola == NULL) {
		cabeza = nuevo_nodo;
		cola = cabeza;
	}
	else {
		cola -> siguiente = nuevo_nodo;
		cola = nuevo_nodo;
	}
}

char *desencolar() {
	if (cabeza == NULL) {
		return NULL;
	}
	char *directorio = strdup(cabeza -> directorio);
	nodo * nodoC = cabeza;
	cabeza = cabeza -> siguiente;
	if (cabeza == NULL) {
		cola = NULL;
	}
	free(nodoC);
	return directorio;
}

void tls(int t_num, FILE *outpot, char *act_dir){
	DIR *dir;
	struct dirent * dir_info;

	if((dir = opendir(act_dir)) == NULL){
		printf("%s: %s\n",act_dir,MENSAJE_ERROR_ABRIR_DIR);
		exit(1);
	}

	while ((dir_info = readdir(dir)) != NULL){
		if (!es_oculto(dir_info->d_name)){
			if (es_directorio(dir_info->d_name)){
				encolar(dir_info->d_name);
			}
		}
	}

	if (outpot == NULL){
		printf("n: %d\n", t_num);
		printf("d: %s\n", act_dir);

	} else {
		fprintf(outpot,"n: %d\n", t_num);
		fprintf(outpot,"d: %s\n", act_dir);
	}

	while(cabeza != NULL){
		printf("%s\n",desencolar() );
	}	

}