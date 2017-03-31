#include "contornos.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa para detectar
 * el punto de fuga.
 */
int main(int argc, char *argv[]) {

	argc = 2;
	argv[1] = "imagenesT3/poster.pgm";

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
	Mat grad_x, grad_y, modulo, angulo;

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
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(img, grad_x, CV_32F, 1, 0, 3);

	// Gradiente en el eje Y.
	Sobel(img, grad_y, CV_32F, 0, 1, 3);
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );

	// Se normalizan los valores.
	grad_x = (grad_x/2)+128;
	grad_y = -(grad_y/2)+128;

	// Se muestran los gradientes por pantalla.
	Mat mostrar = ((grad_x/2)+128)/255;
	mostrarMatriz(mostrar, "Gradiente X");
	mostrar = ((grad_y/2)+128)/255;
	mostrarMatriz(mostrar, "Gradiente Y");

	// Se obtiene el módulo y ángulo.
	cartToPolar(grad_x, grad_y, modulo, angulo);

	//Mat angle = Mat(grad_x.rows, grad_x.cols, CV_32F);

	/*for(int i = 0; i < grad_x.cols; i++) {
		for(int j = 0; j < grad_x.rows; j++) {
			angle.at<float>(i,j) = atan2(grad_y.at<float>(i, j), grad_x.at<float>(i,j));
		}
	}*/

	//namedWindow("Modulo");
	//imshow("Modulo", (modulo/4)/255);
	//namedWindow("Orientacion");
	//imshow("Orientacion", ((angle/CV_PI)*128)/255);

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
/*void transformada(Mat imagen){

	int x, y;		// Variables para los ejes.

	for(int i = 0; i < imagen.rows; i++){		// Se recorren las filas.
		for(int j = 0; j < imagen.cols; j++){	// Se recorren las columnas.
			x = j - imagen.cols/2;
			y = imagen.rows/2 - i;
			theta = imagen.at(i,j);
			rho = ;
			votar ;
		}
	}
}*/
