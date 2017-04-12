#include "panorama.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa para detectar
 * el punto de fuga.
 */
int main(int argc, char *argv[]) {

	if(argc > 1 ) {			// Comprueba el número de argumentos.
		cout << "Número de parámetros incorrecto." << endl;
		return 0;
	}

	char key = 0;		// Variable para la tecla pulsada.
	string ruta;	// Variable para la ruta de las imágenes.

	while(key != 52){	// Bucle para indicar cuando terminar el programa.

		menu();		// Se muestra el menú.
		cin >> key;		// Se lee la tecla pulsada.

		switch(key){		// Se realiza una acción dependiendo de la tecla.
		case 49:		// Se lee las imágenes desde un directorio.
			cout << "Escriba la ruta: ";	// Se escribe la ruta de las imágenes.
			cin >> ruta;	// Se lee la ruta de las imágenes.
			leerArchivos(ruta);		// Se leen las imágenes y se guardan en una lista.
			cout << endl << key << endl;
			break;
		case 50:

			break;
		case 51:

			break;
		case 52:
			break;
		default:
			cout << "Opción incorrecta." << endl;
		}

		cout << endl << key << endl;
	}

}

/*
 * Método que muestra el menú de operaciones para elegir si coger imágenes
 * de disco o directamente desde la cámara.
 */
void menu(){

	// Se muestra el menú.
	cout << endl;
	cout << " ----------------------------------" << endl;
	cout << "|       MENÚ DE OPERACIONES        |" << endl;
	cout << " ----------------------------------" << endl;
	cout << "| 1.- Imágenes de disco            |" << endl;
	cout << "| 2.- Toma de imágenes por teclado |" << endl;
	cout << "| 3.- Toma de imágenes automática  |" << endl;
	cout << "| 4.- Salir.                       |" << endl;
	cout << "-----------------------------------" << endl;

	cout << endl << "Escriba un número: ";

}

/*
 * Método que lee los archivos de un cierto directorio y los
 * guarda en una lista.
 */
void leerArchivos(string dir){

	DIR * directorio;			// Se crea el puntero para el directorio.
	struct dirent * elemento;	// Estructura para el elemento.
	string elem;		// Nombre del elemento.

	directorio = opendir(dir.c_str());	// Se abre el directorio.
	if(directorio != NULL){		// Se comprueba si se puede leer.
		elemento = readdir(directorio);	// Se leen los elementos.
		while(elemento != NULL){
			elem = elemento -> d_name;
			if(elem.compare(".") != 0 && elem.compare("..") != 0){
				cout << "Leyendo fichero: " << dir << "/" << elem << endl;
				ficheros.push_back(dir+"/"+elem);		// Se guarda el fichero en la lista.
			}
			elemento = readdir(directorio);	// Se lee el siguiente elemento.
		}
	} else{		// Si no se puede leer, se muestra el error.
		cout << "El directorio no se puede leer." << endl;
	}
	closedir(directorio);		// Se cierra el directorio.

}
