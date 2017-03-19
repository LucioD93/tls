#include "utilidades.h"

// Funcion main
int main(int argc, char** argv){

	//Se verifica que no se supere un maximo de argumentos
	verificar_argumentos(argc);

	// Se definen las variables para ser capturadas como argumentos
	int hflag = 0;
	int numeroDeHilos = 1;
	directorio = NULL;
	salida = NULL;

	int valor;
	// Se capturan los argumentos
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
 	// Se manejan las situaciones para -h
 	help_handler(hflag, argc);

 	// Se crea el archivo [salida], de ser necesario
 	salida = outpot_ready(optind,argc,argv);

	// Se trabaja con el directoria actual, si no se suministra uno
	if (directorio == NULL) {
		directorio = working_dir();
	}

	// Se crean la cantidad de hilos pedidos en los argumentos
	tls(numeroDeHilos, salida, directorio);

	return 0;
}