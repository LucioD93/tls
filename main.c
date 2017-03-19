#include "utilidades.h"

// Funcion main
int main(int argc, char** argv){
	verificar_argumentos(argc);

	// Se definen las variables para ser capturadas como argumentos
	int hflag = 0;
	int numeroDeHilos = 0;
	directorio = NULL;
	salida = NULL;

	int valor;

	while ((valor = getopt(argc, argv, "hd:n:")) != -1){
		switch (valor) {
			case 'h':
				hflag = 1;
			break;
			case 'n':
				numeroDeHilos = atoi(optarg);
			break;
			case 'd':
				directorio = optarg;
			break;
			case '?':
				if (optopt == 'n' || optopt == 'd') {
					printf("Opcion '-%c' requiere un argumento\n", optopt);
				} else if(isprint(optopt)) {
					printf("Opcion desconocida '-%c'\n", optopt);
				} else {
					printf("Caracter desconocido '\\x%x'\n", optopt);
				}
				exit(1);
			default:
				exit(1);
		}
 	}

	if (hflag == 1 && argc > 2) {
		printf("%s---\n", MENSAJE_ERROR_AYUDA);
		exit(1);
 	}

	if (hflag == 1) {
		printf("%s\n",MENSAJE_AYUDA);
		exit(0);
	}

	if (optind < argc) {
		if ((salida = fopen(argv[optind], "w")) == NULL) {
			printf("%s %s\n",MENSAJE_ERROR_ABRIR_ARCHIVO, argv[optind]);
			exit(1);
		}
		else {
			printf("Salida: %s\n", argv[optind]);
		}
	}

	if (salida == NULL) {
		printf("Salida estandar\n");
	}

	printf("n: %d\n", numeroDeHilos);
	if (directorio == NULL) {
		printf("Se usa directorio actual\n");
		directorio = "..";
	}

	printf("d: %s\n", directorio);

	// Se crean la cantidad de hilos pedidos en los argumentos



	return 0;
}
