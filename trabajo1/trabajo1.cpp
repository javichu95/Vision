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

		TheVideoCapturer.retrieve(bgrMap);		// Obtenemos la imagen.
		key = waitKey(30);

		// Comprobamos si es opción válida para cambiar de vista.
		if(key == 99 || key == 114 || key == 97 || key == 118
				|| key == 109 || key == 98 || key == 100
				|| key == 13){
			keyAnterior = key;
		}
		switch(keyAnterior){
		case 99:		// Se aplica contraste.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			bgrMap = mejorarContraste(bgrMap);
			break;
		case 114:	// Se cambia el color de la piel a rojo.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			bgrMap = cambiarColor(bgrMap,2);
			break;
		case 97:	// Se cambia el color de la piel a azul.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			bgrMap = cambiarColor(bgrMap,1);
			break;
		case 118:	// Se cambia el color de la piel a verde.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			bgrMap = cambiarColor(bgrMap,0);
			break;
		case 109:	// Se reduce el número de colores.
			// Se inicializan las variables.
			primeroCoj = true;	primeroBar = true;
			bgrMap = reducirColores(bgrMap);
			break;
		case 98:	// Se aplica distorsión de barril.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true;
			//bgrMap = distorsionBarril(bgrMap);
			break;
		case 100:	// Se aplica distorsión de cojín.
			// Se inicializan las variables.
			primeroRed = true; primeroBar = true;
			bgrMap = distorsionCojin(bgrMap);
			break;
		case 13:		// Se vuelve a poner normal.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true;	primeroBar = true;
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
	cout << "|--------------------------------------------------------|" << endl << endl;

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

	merge(canales,bgrMap);		// Se juntan los tres canales.

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que cambia el color de la piel.
 */
Mat cambiarColor(Mat bgrMap, int color){

	Mat hsv;		// Matriz para la nueva representación del color.
	cvtColor(bgrMap, hsv,CV_BGR2HSV);		// Cambiamos a hsv.

	if(color == 0){		// Color azul.
		for (int i=0; i<hsv.rows; i++) {		// Recorremos las filas.
			uchar* data= hsv.ptr<uchar>(i); 		// Obtenemos la fila.
			for (int j=0; j<hsv.cols*hsv.channels(); j = j +3) {
				// Miramos si está en el rango de la piel.
				if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					data[j] = 60;		// Lo ponemos a azul.
				}
			}
		}
	} else if(color == 1){		// Color verde.
		for (int i=0; i<hsv.rows; i++) {	// Recorremos las filas.
			uchar* data= hsv.ptr<uchar>(i); // Obtenemos la fila.
			for (int j=0; j<hsv.cols*hsv.channels(); j = j +3) {
				// Miramos si está en el rango de la piel.
				if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					data[j] = 120;		// Lo ponemos a verde.
				}
			}
		}
	} else{				// Color rojo.
		for (int i=0; i<hsv.rows; i++) {	// Recorremos las filas.
			uchar* data= hsv.ptr<uchar>(i); 	// Obtenemos la fila.
			for (int j=0; j<hsv.cols*hsv.channels(); j = j +3) {
				if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					 data[j] = 0;		// Lo ponemos a rojo.
				}
			}
		}
	}

	cvtColor(hsv, bgrMap,CV_HSV2BGR);		// Cambiamos a RGB.
	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Método que reduce el número de colores.
 */
Mat reducirColores(Mat bgrMap){

	if(primeroRed){		// Si es la primera iteración se pregunta número.
		cout << "Escriba número de colores para la imagen: ";
		cin >> numColores;
		primeroRed = false;
	}

	// Matriz en la que se guardará cada canal de la imagen en una fila.
	Mat imagenVector = Mat(bgrMap.cols*bgrMap.rows,3,CV_32F);

	// Se guardan los datos en la nueva matríz.
	for (int i=0; i<bgrMap.rows; i++) {	// Recorremos las filas.
		for (int j=0; j<bgrMap.cols; j++) {
			imagenVector.at<float>(i + j*bgrMap.rows,0) = bgrMap.at<Vec3b>(i,j)[0];
			imagenVector.at<float>(i + j*bgrMap.rows,1) = bgrMap.at<Vec3b>(i,j)[1];
			imagenVector.at<float>(i + j*bgrMap.rows,2) = bgrMap.at<Vec3b>(i,j)[2];
		}
	}

	//Se definen los argumentos para realizar k-means.
	int intentos = 1;
	Mat centroides;
	Mat etiq;

	// Se utiliza k-means para reducir el número de colores mediante clustering.
	kmeans(imagenVector, numColores, etiq,
			TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,1,1.0),
			intentos, KMEANS_PP_CENTERS, centroides);

	// Se modifica la imagen con los colores reducidos.
	for (int i=0; i<bgrMap.rows; i++) {	// Recorremos las filas.
		for (int j=0; j<bgrMap.cols; j++) {
			int indice = etiq.at<int>(i+j*bgrMap.rows,0);
			bgrMap.at<Vec3b>(i,j)[0] = centroides.at<float>(indice,0);
			bgrMap.at<Vec3b>(i,j)[1] = centroides.at<float>(indice,1);
			bgrMap.at<Vec3b>(i,j)[2] = centroides.at<float>(indice,2);
		}
	}

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que aplica una distorsión de cojín a la imagen.
 */
Mat distorsionCojin(Mat bgrMap){

	if(primeroCoj){		// Si es la primera iteración se pregunta número.
		cout << "Escriba coeficiente de distorsión (positivo): ";
		cin >> coeficiente;
		primeroCoj = false;
	}

	Mat map_x, map_y, output;
	double Cy = (double)bgrMap.cols/2;
	double Cx = (double)bgrMap.rows/2;
	map_x.create(bgrMap.size(), CV_32FC1);
	map_y.create(bgrMap.size(), CV_32FC1);

	for (int x=0; x<map_x.rows; x++) {
		for (int y=0; y<map_y.cols; y++) {
			double r2 = (x-Cx)*(x-Cx) + (y-Cy)*(y-Cy);
			map_x.at<float>(x,y) = (double) ((y-Cy)/(1 + double(coeficiente/1000000.0)*r2)+Cy); // se suma para obtener la posicion absoluta
			map_y.at<float>(x,y) = (double) ((x-Cx)/(1 + double(coeficiente/1000000.0)*r2)+Cx); // la posicion relativa del punto al centro
		}
	}
	remap(bgrMap, bgrMap, map_x, map_y, CV_INTER_LINEAR);

	return bgrMap;		// Devolvemos la matriz.
}
