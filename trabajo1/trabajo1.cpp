#include "trabajo1.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	char key = 0;	// Variable para la tecla.
	char keyAnterior = 0;	// Variable para última tecla pulsada.
	mostrarMenu();	// Se muestra el menú de operaciones.
	TheVideoCapturer.open(0);	// Se abre la cámara.

	if (!TheVideoCapturer.isOpened()) {	// Se comprueban posibles errores.
		std::cerr<<"Could not open video"<<std::endl;
		return -1;
	}

	while(key != 27 && TheVideoCapturer.grab()) {		// Mientras sea distinto de ESC...

		TheVideoCapturer.retrieve(bgrMap);
		key = waitKey(30);

		if(key == 99 || key == 114 || key == 97 || key == 118
				|| key == 109 || key == 98 || key == 100
				|| key == 13){
			keyAnterior = key;
		}
		switch(keyAnterior){
		case 99:		// Se aplica contraste.*/
			bgrMap = mejorarContraste(bgrMap);
			break;
		case 114:	// Se cambia el color de la piel a rojo.
			bgrMap = cambiarColor(bgrMap,2);
			break;
		case 97:	// Se cambia el color de la piel a azul.
			bgrMap = cambiarColor(bgrMap,1);
			break;
		case 118:	// Se cambia el color de la piel a verde.
			bgrMap = cambiarColor(bgrMap,0);
			break;
		case 109:	// Se reduce el número de colores.
			break;
		case 98:	// Se aplica distorsión de barril.
			break;
		case 100:	// Se aplica distorsión de cojín.
			break;
		case 13:		// Se vuelve a poner normal.
			TheVideoCapturer.retrieve(bgrMap);
			break;
		default:
			break;
		}
		imshow("BGR camara", bgrMap);	// Se muestra lo visto por la cámara.
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
Mat mejorarContraste(Mat bgrMap){

	vector<Mat> canales;			// Vector para los tres canales.
	split(bgrMap, canales);		// Separamos los tres canales.

	// Se ecualizan los canales.
	equalizeHist(canales[0], canales[0]);
	equalizeHist(canales[1], canales[1]);
	equalizeHist(canales[2], canales[2]);

	merge(canales,bgrMap);

	return bgrMap;
}

/*
 * Función que cambia el color de la piel.
 */
Mat cambiarColor(Mat bgrMap, int color){
	Mat hsi;
	cvtColor(bgrMap, hsi,CV_BGR2HSV);
	if(color == 0){		// Color azul.
		for (int i=0; i<hsi.rows; i++) {
			 uchar* data= hsi.ptr<uchar>(i); // puntero a la fila i
			 for (int j=0; j<hsi.cols*hsi.channels(); j = j +3) {
				 if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					 data[j] = 60;
				 }
				 // o si te gusta mas, puedes hacerlo:
				 // *data++= *data/div*div + div/2;
			 }
		 }
	} else if(color == 1){		// Color verde.
		for (int i=0; i<hsi.rows; i++) {
			uchar* data= hsi.ptr<uchar>(i); // puntero a la fila i
			for (int j=0; j<hsi.cols*hsi.channels(); j = j +3) {
				if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					 data[j] = 120;
				 }
			 }
		 }
	} else{				// Color rojo.
		for (int i=0; i<hsi.rows; i++) {
			 uchar* data= hsi.ptr<uchar>(i); // puntero a la fila i
			 for (int j=0; j<hsi.cols*hsi.channels(); j = j +3) {
				 if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					 data[j] = 0;
				 }
			 }
		 }
	}
	cvtColor(hsi, bgrMap,CV_HSV2BGR);
	return bgrMap;
}

/*
 * Método que reduce el número de colores.
 */
int reducirColores(){

	return 0;
}
