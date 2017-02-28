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
	//TheVideoCapturer.grab();
	TheVideoCapturer.retrieve(bgrMap);		// Obtenemos la imagen.
	calcularCoordenadas();					//Calculamos las coordenadas.

	//VideoWriter wtr("trabajo.avi", CV_FOURCC('D','I','V','X'), 30, Size(640,480));
	while(key != 27 && TheVideoCapturer.grab()) {		// Mientras sea distinto de ESC...

		TheVideoCapturer.retrieve(bgrMap);		// Obtenemos la imagen.
		key = waitKey(20);

		// Comprobamos si es opción válida para cambiar de vista.
		if(key == 99 || key == 114 || key == 97 || key == 118
				|| key == 109 || key == 98 || key == 100
				|| key == 13 || key == 113 || key == 105
				|| key == 103 || key == 115 || key == 116
				|| key == 101){
			keyAnterior = key;
		}
		switch(keyAnterior){
		case 99:		// Se aplica contraste.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = ecualizar(bgrMap);
			break;
		case 101:		// Se aplica contraste.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = mejorarContraste(bgrMap);
			break;
		case 114:	// Se cambia el color de la piel a rojo.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = cambiarColor(bgrMap,2);
			break;
		case 97:	// Se cambia el color de la piel a azul.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = cambiarColor(bgrMap,1);
			break;
		case 118:	// Se cambia el color de la piel a verde.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = cambiarColor(bgrMap,0);
			break;
		case 109:	// Se reduce el número de colores.
			// Se inicializan las variables.
			primeroCoj = true;	primeroBar = true; primeroBin = true;
			primeroSim = true;
			bgrMap = reducirColores(bgrMap);
			break;
		case 98:	// Se aplica distorsión de barril.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBin = true;
			primeroSim = true;
			bgrMap = distorsionBarril(bgrMap);
			break;
		case 100:	// Se aplica distorsión de cojín.
			// Se inicializan las variables.
			primeroRed = true; primeroBar = true; primeroBin = true;
			primeroSim = true;
			bgrMap = distorsionCojin(bgrMap);
			break;
		case 113:		// Se rota la imagen.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = rotar(bgrMap);
			break;
		case 105:		// Se invierte la imagen 180º.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = invertir(bgrMap);
			break;
		case 103:		// Se convierte a escala de grises.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true; primeroSim = true;
			bgrMap = escalaGrises(bgrMap);
			break;
		case 115:		// Se convierte a la simétrica en torno a un eje.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroBin = true;
			bgrMap = simetrica(bgrMap);
			break;
		case 116:	// Se convierte a imagen binaria.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true; primeroBar = true;
			primeroSim = true;
			bgrMap = binaria(bgrMap);
			break;
		case 13:		// Se vuelve a poner normal.
			// Se inicializan las variables.
			primeroRed = true; primeroCoj = true;	primeroBar = true;
			primeroBin = true; primeroSim = true;
			TheVideoCapturer.retrieve(bgrMap);
			break;
		default:
			break;
		}
		imshow("BGR camara", bgrMap);	// Se muestra lo visto por la cámara.
		//wtr.write(bgrMap);
	}
	//wtr.release();
}

/*
 * Método que muestra el menú de operaciones por pantalla.
 */
int mostrarMenu(){

	// Se muestra el menú.
	cout << "|--------------------------------------------------------|" << endl;
	cout << "|                  MENU DE OPERACIONES                   |" << endl;
	cout << "|--------------------------------------------------------|" << endl;
	cout << "| 1.- Pulsa 'c' para ecualizar el histograma.            |" << endl;
	cout << "| 2.- Pulsa 'e' para mejorar el contraste.               |" << endl;
	cout << "| 3.- Pulsa 'r' para cambiar el color de la piel a rojo. |" << endl;
	cout << "| 4.- Pulsa 'a' para cambiar el color de la piel a azul. |" << endl;
	cout << "| 5.- Pulsa 'v' para cambiar el color de la piel a verde.|" << endl;
	cout << "| 6.- Pulsa 'm' para reducir el número de colores.       |" << endl;
	cout << "| 7.- Pulsa 'b' para aplicar distorsion de barril.       |" << endl;
	cout << "| 8.- Pulsa 'd' para aplicar distorsion de cojin.        |" << endl;
	cout << "| 9.- Pulsa 'i' para invertir la imagen.                 |" << endl;
	cout << "| 10.- Pulsa 'q' para rotar la imagen (180º).            |" << endl;
	cout << "| 11.- Pulsa 'g' para pasar a escala de grises.          |" << endl;
	cout << "| 12.- Pulsa 's' para doblar la imagen en torno a un eje.|" << endl;
	cout << "| 13.- Pulsa 't' para convertir la imagen a binaria.     |" << endl;
	cout << "| 14.- Pulsa 'esc' para terminar.                        |" << endl;
	cout << "|--------------------------------------------------------|" << endl << endl;

	return 0;
}

/*
 * Función que mejora el constraste de la imagen ecualizando el
 * histograma.
*/
Mat ecualizar(Mat bgrMap){

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
 * Función que mejora el constraste de la imagen.
*/
Mat mejorarContraste(Mat bgrMap){

	// Aumentamos el contraste de la imagen por un escalar.
	bgrMap.convertTo(bgrMap, -1, 2, 0);

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que cambia el color de la piel.
 */
Mat cambiarColor(Mat bgrMap, int color){

	Mat hsv;		// Matriz para la nueva representación del color.
	cvtColor(bgrMap, hsv,CV_BGR2HSV);		// Cambiamos a hsv.

	if(color == 0){		// Color verde.
		for (int i=0; i<hsv.rows; i++) {		// Recorremos las filas.
			uchar* data= hsv.ptr<uchar>(i); 		// Obtenemos la fila.
			for (int j=0; j<hsv.cols*hsv.channels(); j = j +3) {
				// Miramos si está en el rango de la piel.
				if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					data[j] = 60;		// Lo ponemos a verde.
				}
			}
		}
	} else if(color == 1){		// Color azul.
		for (int i=0; i<hsv.rows; i++) {	// Recorremos las filas.
			uchar* data= hsv.ptr<uchar>(i); // Obtenemos la fila.
			for (int j=0; j<hsv.cols*hsv.channels(); j = j +3) {
				// Miramos si está en el rango de la piel.
				if((data[j] <= 25) || (data[j] >= 162 && data[j] <= 180)) {
					data[j] = 120;		// Lo ponemos a azul.
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

	// Se definen los argumentos para realizar k-means.
	int intentos = 1; Mat centroides; Mat etiq;

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

	if(primeroCoj){		// Si es la primera iteración se pregunta coeficiente.
		cout << "Escriba coeficiente de distorsión (positivo): ";
		cin >> coeficiente;		// Se lee coeficiente.
		primeroCoj = false;
		// Variables para realizar cambio de coordenadas para distorsion de cojin.
		double Cy = (double)bgrMap.cols/2;
		double Cx = (double)bgrMap.rows/2;
		coordXCojin.create(bgrMap.size(), CV_32FC1);
		coordYCojin.create(bgrMap.size(), CV_32FC1);

		for (int x=0; x<coordXCojin.rows; x++) {		// Se recorren las filas.
			for (int y=0; y<coordYCojin.cols; y++) {		// Se recorren las columnas.
				// Se calculan nuevas coordenadas y se guardan.
				double r2 = (x-Cx)*(x-Cx) + (y-Cy)*(y-Cy);
				coordXCojin.at<float>(x,y) =
						(double) ((y-Cy)/(1 + double(coeficiente/1000000.0)*r2)+Cy);
				coordYCojin.at<float>(x,y) =
						(double) ((x-Cx)/(1 + double(coeficiente/1000000.0)*r2)+Cx);
			}
		}
	}

	// Se aplican las nuevas coordenadas a la imagen.
	remap(bgrMap, bgrMap, coordXCojin, coordYCojin, CV_INTER_LINEAR);

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que aplica una distorsión de barríl a la imagen.
 */
Mat distorsionBarril(Mat bgrMap){

	if(primeroBar){		// Si es la primera iteración se pregunta coeficiente.
		cout << "Escriba coeficiente de distorsión (positivo): ";
		cin >> coeficiente;		// Se lee coeficiente.
		primeroBar = false;
		// Variables para realizar cambio de coordenadas para distorsion de cojin.
		double Cy = (double)bgrMap.cols/2;
		double Cx = (double)bgrMap.rows/2;
		// Variables para realizar cambio de coordenadas para la distorsion de barril.
		coordXBarril.create(bgrMap.size(), CV_32FC1);
		coordYBarril.create(bgrMap.size(), CV_32FC1);

		for (int x=0; x<coordXBarril.rows; x++) {		// Se recorren las filas.
			for (int y=0; y<coordYBarril.cols; y++) {		// Se recorren las columnas.
				// Se calculan nuevas coordenadas y se guardan.
				double r2 = (x-Cx)*(x-Cx) + (y-Cy)*(y-Cy);
				coordXBarril.at<float>(x,y) =
						(float) ((y-Cy)/(1 + float(-coeficiente/1000000.0)*r2)+Cy);
				coordYBarril.at<float>(x,y) =
						(float) ((x-Cx)/(1 + float(-coeficiente/1000000.0)*r2)+Cx);
				}
		}
	}

	// Se aplican las nuevas coordenadas a la imagen.
	remap(bgrMap, bgrMap, coordXBarril, coordYBarril, CV_INTER_LINEAR);

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que invierte la imagen captada por la cámara.
 */
Mat invertir(Mat bgrMap){

	// Se aplican las nuevas coordenadas.
	remap(bgrMap, bgrMap, coordXInv, coordYInv, CV_INTER_LINEAR);

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que da la vuelta a la imagen captada por la cámara (rota 180º).
 */
Mat rotar(Mat bgrMap){


	// Se aplican las nuevas coordenadas.
	remap(bgrMap, bgrMap, coordXRot, coordYRot, CV_INTER_LINEAR);

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que dobla la imagen respecto al eje X o Y (simétrica).
 */
Mat simetrica(Mat bgrMap){

	Mat redimen;		// Variable para la matriz redimensionada.
	if(primeroSim){		// Si es la primera iteración se pregunta valor del eje.
		cout << "Escriba el eje de simetría (X o Y): ";
		cin >> eje;		// Se lee el eje.
		for (uint i=0; i < eje.size(); i++)		// Se pasa a minúsculas.
			eje.at(i) = tolower(eje.at(i));
		primeroSim = false;
	}

	if(eje.compare("x") == 0){	// Eje de simetría X.
		// Se redimensiona la imagen.
		resize(bgrMap,redimen,Size(bgrMap.cols,bgrMap.rows/2));
		// Se aplican las nuevas coordenadas.
		remap(redimen, bgrMap, coordXSimX, coordYSimX, CV_INTER_LINEAR);


	} else{			// Eje de simetría Y.
		// Se redimensiona la imagen.
		resize(bgrMap,redimen,Size(bgrMap.cols/2,bgrMap.rows));
		// Se aplican las nuevas coordenadas.
		remap(redimen, bgrMap, coordXSimY, coordYSimY, CV_INTER_LINEAR);
	}

	return bgrMap;	// Devolvemos la matriz.
}

/*
 * Función que pasa la imagen a escala de grises.
 */
Mat escalaGrises(Mat bgrMap){

	// Se pasa la imagen a escala de grises.
	cvtColor(bgrMap,bgrMap,CV_RGB2GRAY);

	return bgrMap;		// Devolvemos la matriz.
}

/*
 * Función que pasa una imagen a binaria.
 */
Mat binaria(Mat bgrMap){

	// Se pasa la imagen a escala de grises.
	cvtColor(bgrMap,bgrMap,CV_BGR2GRAY);
	if(primeroBin){		// Si es la primera iteración se pregunta valor de threshold.
		cout << "Escriba valor de threshold: ";
		cin >> thresVal;		// Se lee coeficiente.
		primeroBin = false;
	}

	threshold(bgrMap, bgrMap, thresVal, maxBinaria, THRESH_BINARY);
	return bgrMap;		// Se devuelve la matriz.
}

/*
 * Calcula las coordenadas que se utilizaran en los diferentes modos de la imagen.
 */
void calcularCoordenadas() {

	// Se crean las matrices para las nuevas coordenadas para invertir la imagen.
	coordXInv.create(bgrMap.size(), CV_32FC1);
	coordYInv.create(bgrMap.size(), CV_32FC1);

	// Se calculan las coordenadas para invertir.
	for (int x=0; x<coordXInv.rows; x++) {		// Se recorren las filas.
		for (int y=0; y<coordYInv.cols; y++) {		// Se recorren las columnas.
			// Se calculan nuevas coordenadas y se guardan.
			coordXInv.at<float>(x,y) = bgrMap.cols-y;
			coordYInv.at<float>(x,y) = x;
		}
	}

	// Se crean las matrices para las nuevas coordenadas para rotar la imagen.
	coordXRot.create(bgrMap.size(), CV_32FC1);
	coordYRot.create(bgrMap.size(), CV_32FC1);

	// Se calculan las coordenadas para rotar.
	for (int x=0; x<coordXRot.rows; x++) {		// Se recorren las filas.
		for (int y=0; y<coordYRot.cols; y++) {		// Se recorren las columnas.
			// Se calculan nuevas coordenadas y se guardan.
			coordXRot.at<float>(x,y) = y;
			coordYRot.at<float>(x,y) = bgrMap.rows-x;
		}
	}

	// Se crean las matrices para las nuevas coordenadas para simetría en eje X.
	coordXSimX.create(bgrMap.size(), CV_32FC1);
	coordYSimX.create(bgrMap.size(), CV_32FC1);

	// Se calculan las coordenadas para simetría en eje X.
	for (int x=0; x<coordXSimX.rows/2; x++) {		// Se recorren las filas.
		for (int y=0; y<coordYSimX.cols; y++) {		// Se recorren las columnas.
			// Se calculan nuevas coordenadas y se guardan.
			coordXSimX.at<float>(x,y) = y;
			coordYSimX.at<float>(x,y) = x;
			coordXSimX.at<float>(x+coordXSimX.rows/2,y) = y;
			coordYSimX.at<float>(x+coordXSimX.rows/2,y) = coordYSimX.rows/2-x;
		}
	}

	// Se crean las matrices para las nuevas coordenadas para simetria en eje y.
	coordXSimY.create(bgrMap.size(), CV_32FC1);
	coordYSimY.create(bgrMap.size(), CV_32FC1);

	// Se calculan coordenadas para simetría en eje Y.
	for (int x=0; x<coordXSimY.rows; x++) {		// Se recorren las filas.
		for (int y=0; y<coordYSimY.cols/2; y++) {		// Se recorren las columnas.
			// Se calculan nuevas coordenadas y se guardan.
			coordXSimY.at<float>(x,y) = y;
			coordYSimY.at<float>(x,y) = x;
			coordXSimY.at<float>(x,y+coordXSimY.cols/2) = coordXSimY.cols/2-y;
			coordYSimY.at<float>(x,y+coordXSimY.cols/2) = x;
		}
	}
}
