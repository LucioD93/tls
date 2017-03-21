#include "utilidades.h"

// Definicion de mensajes base
const char *MENSAJE_ERROR_AYUDA = "Error! - La opcion -h excluye las demas opciones";
const char *MENSAJE_AYUDA = "Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida] \n-h: Muestra por pantalla un mensaje de ayuda, excluye del resto de opciones\n-n i: Nivel de concurrencia solicitado (uno por defecto)\n-d directorio: directorio desde donde calcula el espacio utilizado (actual por defecto)\nsalida: Archivo con lista de directorios y el espacio ocupado por los archivos regulares (salida estandar por defecto)";
const char *MENSAJE_ERROR_ABRIR_ARCHIVO = "Error! - No se pudo abrir archivo";
const char *MENSAJE_ERROR_ARGUMENTOS = "Error! Maximo de argumentos superado\n Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida]";
const char *MENSAJE_ERROR_ABRIR_DIR = "Error! - No se pudo abrir el directorio de trabajo";
const char *MENSAJE_PERMISO_NEGADO = "Error! Permiso negado para: ";

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

FILE *crear_salida(int posicion, int cantidad, char** argumentos){
	if (posicion < cantidad) {
		if ((salida = fopen(argumentos[posicion], "w")) == NULL) {
			printf("%s %s\n",MENSAJE_ERROR_ABRIR_ARCHIVO, argumentos[posicion]);
			exit(1);
		}
		else {
			//printf("Salida: %s\n", argumentos[posicion]);
			return salida;
		}
	}

	return salida;
}

void working_dir(char** directorio){
	char* cp;
	char* cwd = (char*) malloc(sizeof (char) * BUFSIZE);

	if(!(cp = getcwd(cwd,BUFSIZE))) {
		printf("%s\n",MENSAJE_ERROR_ABRIR_DIR);
	    exit(1);
	}

	if (*directorio == NULL){
		*directorio = cwd;

	} else {

		//Aqui cp sera 'tls'
		cp = basename(cwd);

		char* actualpath = (char*) malloc(sizeof(char)*BUFSIZE);
		printf("actualpath |%s|\n", actualpath);

		realpath(*directorio, actualpath);

		*directorio = actualpath;

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
		printf("%s%s\n",MENSAJE_PERMISO_NEGADO, direccion);
	}
	return S_ISDIR(buffer.st_mode);
}

char* copiar_string(char* s) {
	char *resultado = (char*) malloc(sizeof(char)*(strlen(directorio)+1));
	strcpy(resultado, s);
	return resultado;
}

void encolar(char *directorio) {
	int dirlen;
	dirlen = (int)strlen(directorio);
	nodo *nuevo_nodo = (nodo*) malloc(sizeof(nodo));
	directorio[dirlen] = '\0';

	nuevo_nodo->directorio = copiar_string(directorio);
	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->directorio[dirlen] = '\0';

	if (cabeza == NULL && cola == NULL) {
		cabeza = nuevo_nodo;
		cola = nuevo_nodo;
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

	char *directorio = copiar_string(cabeza -> directorio);

	cabeza = cabeza -> siguiente;
	if (cabeza == NULL) {
		cola = NULL;
	}

	return directorio;
}

void explorar_directorio(char* directorio_actual) {
	DIR *dir;
	struct dirent *informacion_directorio;
	char *direccion_completa;

	strcat(directorio_actual,"/");

	int act_name;
	if((dir = opendir(directorio_actual)) == NULL){
		printf("%s: %s\n",directorio_actual, MENSAJE_ERROR_ABRIR_DIR);
		exit(1);
	}

	while ((informacion_directorio = readdir(dir)) != NULL){
		act_name = (int)strlen(informacion_directorio->d_name);
		informacion_directorio->d_name[act_name]='\0';

		if (!es_oculto(informacion_directorio->d_name)){

			direccion_completa = copiar_string(directorio_actual);
			strcat(direccion_completa,informacion_directorio->d_name);
			
			if (es_directorio(direccion_completa)){
				encolar(direccion_completa);
			}
		}
	}

}

void tls(int numero_hilos, FILE *salida, char *directorio_actual){

	explorar_directorio(directorio_actual);

	if (salida == NULL){
		printf("n: %d\n", numero_hilos);
		printf("d: %s\n", directorio_actual);

	} else {
		fprintf(salida,"n: %d\n", numero_hilos);
		fprintf(salida,"d: %s\n", directorio_actual);
	}

	while(cabeza != NULL){
		explorar_directorio(desencolar());
	}

}
