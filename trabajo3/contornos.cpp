#include "contornos.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa para detectar
 * el punto de fuga.
 */
int main(int argc, char *argv[]) {

	argc = 2;
	argv[1] = (char*)("imagenesT3/pasillo3.pgm");

	if(argc > 2 ) {			// Comprueba el número de argumentos.
		cout << "Usar: contornos ó contornos [imagen]" << endl;
		return 0;
	}

	if(argc == 1){
		// Se captura el punto en tiempo real.
		fugaReal();
	}

	if(argc == 2){
		// Se lee la imagen.
		string ruta = argv[1];
		Mat imagen = leerImagen(ruta);

		fugaImagen(imagen);	// Se captura el punto de fuga de una imagen.
	}

}

/*
 * Método que lee la imagen dada su ruta.
 */
Mat leerImagen(string ruta){

	// Se lee la imagen.
	Mat img = imread(ruta, CV_LOAD_IMAGE_GRAYSCALE);

	cout << "Leyendo imagen: " << ruta << "..." << endl;

	if(!img.data){		// Se comprueba si se puede leer la imagen.
		cout <<  "No se puede abrir la imagen: " << ruta << endl ;
		exit(1);
	}

	namedWindow("Imagen", CV_WINDOW_AUTOSIZE);	// Se crea una ventana.
	imshow("Imagen", img);		// Se muestra la imagen.

	waitKey(0);		// Se pausa para mostrar la imagen.

	return img;			// Se devuelve la matriz.
}

/*
 * Método que calcula el punto de fuga de una cierta imagen
 * pasada como argumento.
 */
void fugaImagen(Mat img){

	// Matrices para el gradiente en cada eje, modulo y ángulo.
	Mat orientacion, modulo, grad_x, grad_y;

	img = aplicarFiltro(img, 3, 3, 0, 0);	// Se aplica un filtro Gaussiano.

	// Gradiente en el eje X.
	//Sobel(img, grad_x, CV_32F, 1, 0, CV_SCHARR);		// Operador Scarr.
	Sobel(img, grad_x, CV_32F, 1, 0, 3);				// Operador Sobel.

	// Gradiente en el eje Y.
	//Sobel(img, grad_y, CV_32F, 0, 1, CV_SCHARR);		// Operador Scharr.
	Sobel(img, grad_y, CV_32F, 0, 1, 3);				// Operador Sobel.

	grad_y = -grad_y;			// Se invierte el eje.

	// Se muestran los gradientes por pantalla.
	Mat mostrar = (grad_x/2+128)/255;
	mostrarMatriz(mostrar, "Gradiente X");
	mostrar = (grad_y/2+128)/255;
	mostrarMatriz(mostrar, "Gradiente Y");

	// Se obtiene el módulo y ángulo.
	cartToPolar(grad_x, grad_y, modulo, orientacion);

	// Se muestra el módulo por pantalla.
	mostrar = modulo/255;
	mostrarMatriz(mostrar, "Modulo");

	// Se muestra el ángulo por pantalla.
	mostrar = ((orientacion/CV_PI)*128)/255;
	mostrarMatriz(mostrar, "Orientacion");

	waitKey(0);			// Se para para ver los valores calculados.

	mostrarPuntos(img.clone(), modulo);	// Se muestran los puntos que votarían.

	waitKey(0);			// Se pausa para ver los puntos.

	// Se calcula el índice de la columna del punto de fuga.
	int maxIndice = transformada(img, orientacion, modulo);

	cout << "Columna máxima: " << maxIndice;

	dibujarX(maxIndice, img.rows/2, img);	// Se señala con una X el punto de fuga.

	waitKey(0);			// Se pausa para ver los resultados.

}

/*
 * Método que aplica un filtro Gaussiano a la imagen.
 */
Mat aplicarFiltro(Mat imagen, int tamX, int tamY, double sigmaX, double sigmaY){

	Mat filtrada;		// Matríz para la imagen filtrada.

	// Se aplica el filtro.
	GaussianBlur(imagen, filtrada, Size(tamX, tamY), sigmaX, sigmaY, BORDER_DEFAULT);

	namedWindow("Imagen Filtro", CV_WINDOW_AUTOSIZE);	// Se crea una ventana.
	imshow("Imagen Filtro", filtrada);		// Se muestra la imagen.

	waitKey(0);			// Se pausa para mostrar la imagen.

	return filtrada;		// Se devuelve la matríz.

}

/*
 * Método que muestra una matríz por pantalla.
 */
void mostrarMatriz(Mat matriz, string nombre){

	namedWindow(nombre);		// Se da nombre a la ventana.
	imshow(nombre, matriz);	// Se muestra la matriz.

}

/*
 * Método que muestra los puntos de contorno según el umbral.
 */
void mostrarPuntos(Mat imagen, Mat modulo){

	for(int i = 0; i < modulo.rows; i++){		// Se recorren las filas.
		for(int j = 0; j < modulo.cols; j++){		// Se recorren las columnas.

			if(modulo.at<float>(i,j) > umbral){			// Se aplica el filtro por umbral.
				// Se señala el punto en la imagen.
				circle(imagen, Point(j,i), 1, CV_RGB(255,0,0));
			}

		}
	}

	// Se muestran los puntos que pasan el filtro.
	mostrarMatriz(imagen, "Puntos de contorno");

}

/*
 * Método que calcula la transformada de Hough de una cierta imagen.
 */
int transformada(Mat imagen, Mat orientacion, Mat modulo){

	int rectas[imagen.cols];	// Tabla con los votos de cada recta.

	for(int i = 0; i < imagen.cols; i++) {		// Se inicializan los valores a 0.
		rectas[i] = 0;
	}

	int x = 0, y = 0;		// Variable para el eje.
	for(int i = 0; i < imagen.rows; i++){		// Se recorren las filas.
		for(int j = 0; j < imagen.cols; j++){	// Se recorren las columnas.

			if(modulo.at<float>(i,j) >= umbral) {
				x = j - imagen.cols/2;		// Se calcula el punto X.
				y = imagen.rows/2 - i;		// Se calcula el punto Y.
				float theta = orientacion.at<float>(i,j);

				votar(rectas, x, y,j , i, theta, imagen);	// Se vota el punto.
			}

		}
	}

	// Se definen las variables para el máximo.
	int maxIndice = 0;
	for(int i = 0; i < imagen.cols; i++){		// Se recorren las posiciones.
		if(rectas[i] > rectas[maxIndice]){			// Si es mayor que el máximo actual...
			// Se guarda su índice.
			maxIndice = i;
		}
	}

	return maxIndice;		// Se devuelve el índice con mayor valor.

}

/*
 * Método que realiza la votación.
 */
void votar(int rectas[], int x, int y, int j, int i, float theta, Mat src){


    float dist = theta - (int)(theta/(CV_PI/2))*(CV_PI/2);

    /*
     * Con a va bien y con dist no, hay que revisarlo.
     */
    if (dist > 0.07) {		// Se comprueba si es línea vertical u horizontal (4 grados).

    	float rho = x*cosf(theta) + y*sinf(theta);	// Se obtiene rho.
    	int corte = rho / cosf(theta);		// Se calcula el corte con el eje.

        if (corte < src.cols/2 && corte >= -src.cols/2) {	// Se comprueba que corta en la imagen.
            corte = corte + src.cols/2;		// Se pone el corte en el rango.
            rectas[corte] = rectas[corte] + 1;	// Se actualiza el valor.

            /*
             * PARTE PARA MOSTRAR LAS RECTAS
             */
            //circle(src, Point(j,i), 1, CV_RGB(255,0,0));
            //line(src, Point(j,i), Point(corte,src.rows/2), CV_RGB(255,0,0));
            //imshow("Pasillo", src);
            //for (;;) {
            	//if (waitKey(30)>=0) { destroyAllWindows();  break; }
            //}
        }
    }

}

/*
 * Método que dibuja el punto de fuga como una X de un cierto grosor.
 */
void dibujarX(int coordX, int coordY, Mat img){

	// Se obtienen los puntos para la X.
	Point p1 = Point(coordX, coordY-10);
	Point p2 = Point(coordX, coordY+10);
	Point p3 = Point(coordX-10, coordY);
	Point p4 = Point(coordX+10, coordY);

	// Se dibuja la X.
	line(img, p1, p2, CV_RGB(255,0,0), 4);
	line(img, p3, p4, CV_RGB(255,0,0), 4);
	circle(img, Point(coordX,coordY), 1, CV_RGB(255,0,0), 3);

	mostrarMatriz(img, "Imagen final");		// Se muestra la imagen.

}

/*
 * Método que calcula el punto de fuga en tiempo real a partir
 * de la cámara.
 */
void fugaReal(){

	VideoCapture TheVideoCapturer;		// Objeto para la cámara.
	Mat bgrMap;		// Matriz de lo obtenido de la cámara.

	TheVideoCapturer.open(0);	// Se abre la cámara.

	if (!TheVideoCapturer.isOpened()) {	// Se comprueban posibles errores.
		std::cerr<<"Could not open video"<<std::endl;
		exit(-1);
	}

	TheVideoCapturer.grab();
	TheVideoCapturer.retrieve(bgrMap);		// Obtenemos la imagen.

}
