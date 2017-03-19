#include "utilidades.h"

// Definicion de mensajes base
const char *MENSAJE_ERROR_AYUDA = "Error, la opcion -h excluye las demas opciones";
const char *MENSAJE_AYUDA = "Uso de tls:\n./tls [-h] | [-n <i>] [-d <directorio>] [salida] \n-h: Muestra por pantalla un mensaje de ayuda, excluye del resto de opciones\n-n i: Nivel de concurrencia solicitado (uno por defecto)\n-d directorio: directorio desde donde calcula el espacio utilizado (actual por defecto)\nsalida: Archivo con lista de directorios y el espacio ocupado por los archivos regulares (salida estandar por defecto)";
const char *MENSAJE_ERROR_ABRIR_ARCHIVO = "Error! - No se pudo abrir archivo";

void verificar_argumentos(int cantidad) {
	if ((cantidad < 2) || (cantidad > 3)) {
		/* code */
	}
}
