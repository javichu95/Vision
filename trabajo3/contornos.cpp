#include "contornos.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa para detectar
 * el punto de fuga.
 */
int main(int argc, char *argv[]) {

	argc = 2;
	argv[1] = (char*)("imagenesT3/pasillo2.pgm");

	if(argc > 2 ) {			// Comprueba el número de argumentos.
		cout << "Usar: contornos ó contornos [imagen]" << endl;
		return 0;
	}

	if(argc == 1){
		// Se captura el punto en tiempo real.
		fugaReal();
	}

	if(argc == 2){
		// Se captura el punto de una imagen.
		string imagen = argv[1];
		fugaImagen(imagen);
	}

}

/*
 * Método que calcula el punto de fuga de una cierta imagen
 * pasada como argumento.
 */
void fugaImagen(string imagen){

	// Matrices para el gradiente en cada eje, modulo y ángulo.
	Mat orientacion, modulo, grad_x, grad_y;

	// Se lee la imagen.
	Mat img = imread(imagen, CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2;

	cout << "Leyendo imagen: " << imagen << "..." << endl;

	if(!img.data){		// Se comprueba si se puede leer la imagen.
		cout <<  "No se puede abrir la imagen: " << imagen << endl ;
		exit(1);
	}

	namedWindow("Imagen", CV_WINDOW_AUTOSIZE);	// Se crea una ventana.
	imshow("Imagen", img);		// Se muestra la imagen.

	// Se aplica un filtro gaussiano.
	img = aplicarFiltro(img, 3, 3, 0, 0);

	namedWindow("Imagen Filtro", CV_WINDOW_AUTOSIZE);	// Se crea una ventana.
	imshow("Imagen Filtro", img);		// Se muestra la imagen.

	// Gradiente en el eje X.
	//Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(img, grad_x, CV_32F, 1, 0, 3);

	// Gradiente en el eje Y.
	Sobel(img, grad_y, CV_32F, 0, 1, 3);
	//Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );

	grad_y = -grad_y;			// Se invierte el eje.

	// Se muestran los gradientes por pantalla.
	Mat mostrar = (grad_x/2+128)/255;
	mostrarMatriz(mostrar, "Gradiente X");
	mostrar = (grad_y/2+128)/255;
	mostrarMatriz(mostrar, "Gradiente Y");

	// Se obtiene el módulo y ángulo.
	cartToPolar(grad_x, grad_y, modulo, orientacion);


	for(int i=0; i<orientacion.rows; i++){
		for(int j=0; j<orientacion.cols; j++){
			cout << orientacion.at<float>(i,j) << endl;
		}
	}

	// Se muestra el módulo por pantalla.
	mostrar = (modulo/4)/255;
	mostrarMatriz(mostrar, "Modulo");

	// Se muestra el ángulo por pantalla.
	mostrar = ((orientacion/CV_PI)*128)/255;
	mostrarMatriz(mostrar, "Orientacion");

	/*double maximo = 0.0;
	for(int i=0; i<modulo.rows; i++){
		for(int j=0; j<modulo.cols; j++){
			cout << modulo.at<float>(i,j) << endl;
			if(modulo.at<float>(i,j)>maximo){
				maximo = modulo.at<float>(i,j);
			}
		}
	}

	cout << maximo << endl;*/

	waitKey(0);

	transformada(img, orientacion, modulo);

	waitKey(0);
}

/*
 * Método que aplica un filtro gaussiano a la imagen.
 */
Mat aplicarFiltro(Mat imagen, int tamX, int tamY, double sigmaX, double sigmaY){

	Mat filtrada;		// Matríz para la imagen filtrada.

	// Se aplica el filtro.
	GaussianBlur(imagen, filtrada, Size(tamX, tamY), sigmaX, sigmaY, BORDER_DEFAULT);

	return filtrada;		// Se devuelve la matríz.

}

/*
 * Método que muestra una matríz por pantalla.
 */
void mostrarMatriz(Mat matriz, string nombre){

	namedWindow(nombre);		// Se da nombre a la ventana.
	imshow(nombre, matriz);	// Se muestra la matríz.
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

/*
 * Método que calcula la transformada de Hough de una cierta imagen.
 */
int transformada(Mat imagen, Mat orientacion, Mat modulo){

	int rectas[imagen.cols];	// Tabla con los votos de cada recta.
	for(int i = 0; i < imagen.cols; i++) {
		rectas[i] = 0;
	}
	int x = 0, y = 0;		// Variable para el eje.
	float umbral = 65.0;			// Valor umbral.
	for(int i = 0; i < imagen.rows; i++){		// Se recorren las filas.
		for(int j = 0; j < imagen.cols; j++){	// Se recorren las columnas.
			if(modulo.at<float>(i,j) >= umbral) {
				x = j - imagen.cols/2;
				y = imagen.rows/2 - i;
				float theta = orientacion.at<float>(i,j);
				int rho = x*cosf(theta) + y*sinf(theta);
				cout << x << " " << theta << " " << rho << endl;
				rectas[rho] = rectas[rho] + 1;
			}
		}
	}



	// Se definen las variables para el máximo.
	int maximo = 0;
	int maxIndice = 0;
	for(int i = 0; i < imagen.cols; i++){		// Se recorren las posiciones.
		if(rectas[i] > maximo){			// Si es mayor que el máximo actual...
			// Se guarda su valor y su índice.
			maximo = rectas[i];
			maxIndice = i;
		}
	}

	cout << "MAXIMO: " << maximo << endl;
	cout << "MAX INDICE: " << maxIndice << endl;

	circle(imagen, Point(maxIndice,imagen.rows/2), 1, CV_RGB(255,0,0), 10);
	mostrarMatriz(imagen, "Imagen final");

	return maxIndice;
}

/*
 * Método que realiza la votación.
 */
void votar(){


}
