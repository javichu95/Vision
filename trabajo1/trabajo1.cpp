#include "trabajo1.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	char key = 0;	// Variable para la tecla.
	mostrarMenu();	// Se muestra el menú de operaciones.
	TheVideoCapturer.open(0);	// Se abre la cámara.

	if (!TheVideoCapturer.isOpened()) {	// Se comprueban posibles errores.
		std::cerr<<"Could not open video"<<std::endl;
		return -1;
	}

	while(key != 27 && TheVideoCapturer.grab()) {		// Mientras sea distinto de ESC...
		TheVideoCapturer.retrieve(bgrMap);
		imshow("BGR image", bgrMap);	// Se muestra lo visto por la cámara.

		key = waitKey(30);
		switch(key){
		case 99:		// Se aplica contraste.
			cout << "Aplicando contraste..." << endl;
			mejorarContraste();
			break;
		case 114:	// Se cambia el color de la piel a rojo.
			cout << "Cambiando color a rojo..." << endl;
			cambiarColor(0);
			break;
		case 97:	// Se cambia el color de la piel a azul.
			cout << "Cambiando color a azul..." << endl;
			cambiarColor(1);
			break;
		case 118:	// Se cambia el color de la piel a verde.
			cout << "Cambiando color a verde..." << endl;
			cambiarColor(2);
			break;
		case 109:	// Se reduce el número de colores.
			cout << "Reduciendo el número de colores..." << endl;
			break;
		case 98:	// Se aplica distorsión de barril.
			cout << "Aplicando distorsión de barril..." << endl;
			break;
		case 100:	// Se aplica distorsión de cojín.
			cout << "Aplicando distorsión de cojín..." << endl;
			break;
		default:
			break;
		}
	}
}
/*
 * Método que muestra el menú de operaciones por pantalla.
 */
int mostrarMenu(){

	// Se muestra el menú.
	cout << "|--------------------------------------------------------|" << endl;
	cout << "|                  MENU DE OPERACIONES                   |" << endl;
	cout << "|--------------------------------------------------------|" << endl;
	cout << "| 1.- Pulsa 'c' para aplicar contraste a la imagen.      |" << endl;
	cout << "| 2.- Pulsa 'r' para cambiar el color de la piel a rojo. |" << endl;
	cout << "| 3.- Pulsa 'a' para cambiar el color de la piel a azul. |" << endl;
	cout << "| 4.- Pulsa 'v' para cambiar el color de la piel a verde.|" << endl;
	cout << "| 5.- Pulsa 'm' para reducir el número de colores.       |" << endl;
	cout << "| 6.- Pulsa 'b' para aplicar distorsion de barril.       |" << endl;
	cout << "| 7.- Pulsa 'd' para aplicar distorsion de cojin.        |" << endl;
	cout << "| 8.- Pulsa 'esc' para terminar.                         |" << endl;
	cout << "|--------------------------------------------------------|" << endl;

	return 0;
}

/*
 * Función que mejora el constraste de la imagen.
*/
int mejorarContraste(){

	return 0;
}

/*
 * Función que cambia el color de la piel.
 */
int cambiarColor(int color){

	if(color == 0){		// Color rojo.

	} else if(color == 1){		// Color verde.

	} else{				// Color azul.

	}

	return 0;
}

/*
 * Método que reduce el número de colores.
 */
int reducirColores(){

	return 0;
}
