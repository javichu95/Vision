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

	// Se lee la imagen.
	Mat img = imread(imagen, CV_LOAD_IMAGE_GRAYSCALE);

	cout << "Leyendo imagen: " << imagen << "..." << endl;

	if(!img.data){		// Se comprueba si se puede leer la imagen.
		cout <<  "No se puede abrir la imagen: " << imagen << endl ;
		exit(1);
	}

	namedWindow("Imagen", CV_WINDOW_AUTOSIZE);	// Se crea una ventana.
	imshow("Imagen", img);		// Se muestra la imagen.

	// Matrices para el gradiente en cada eje.
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	// Gradiente en el eje X.
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(img, grad_x, CV_32F, 1, 0, 3);

	// Gradiente en el eje Y.
	Sobel(img, grad_y, CV_32F, 0, 1, 3);
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );

	// Se obtiene el módulo y ángulo.
	//cartToPolar(outputX, -outputY, modulo, angle);

	// Se normalizan los valores para mostrarlos por pantalla.
	grad_x = (grad_x/2)+128;
	grad_y = (grad_y/2)+128;

	Mat angle = Mat(grad_x.rows, grad_x.cols, CV_32F);

	for(int i = 0; i < grad_x.cols; i++) {
		for(int j = 0; j < grad_x.rows; j++) {
			angle.at<float>(i,j) = atan2(grad_y.at<float>(i, j), grad_x.at<float>(i,j));
		}
	}

	namedWindow("GradienteX");
	imshow("GradienteX", grad_x);
	namedWindow("GradienteY");
	imshow("GradienteY", grad_y);
	//namedWindow("Modulo");
	//imshow("Modulo", (modulo/4)/255);
	namedWindow("Orientacion");
	imshow("Orientacion", ((angle/CV_PI)*128)/255);

	waitKey(0);
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
