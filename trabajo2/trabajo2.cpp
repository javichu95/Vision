#include "trabajo2.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	leerArchivos("./imagenesT2");		// Se leen los archivos de la carpeta.
	cout << endl << endl << ficheros.front();
	Mat imagen = imread(ficheros.front(), CV_LOAD_IMAGE_GRAYSCALE);
	if(!imagen.data ){
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
	imshow("Display window", imagen);
	string titulo = "histograma";
	mostrarHistograma(titulo,imagen);
	waitKey(0);
	umbralizar(imagen);
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
				cout << elem << endl;
				ficheros.push_back("./"+dir+"/"+elem);		// Se guarda el fichero en la lista.
			}
			elemento = readdir(directorio);	// Se leen los elementos.
		}
	} else{		// Si no se puede leer, se muestra el error.
		cout << "El directorio no se puede leer." << endl;
	}
	closedir(directorio);		// Se cierra el directorio.

}

/*
 * Método que umbraliza la imagen pasada como parámetros para convertirla
 * en una imagen binaria.
 */
Mat umbralizar(Mat imagen){

	// Método adaptativo u Otsu.
	Mat umbralizada;
	return umbralizada;		// Se devuelve la matriz.
}

/*
 * Método que obtiene los distintos blops de la imagen.
 */
Mat obtenerBlops(Mat imagen){

	// findContours.
}

/*
 * Método que obtiene los descriptores de la imagen.
 */
Mat obtenerDescriptores(Mat imagen){

}

/*
 * Método que muestra el histograma de una imagen.
 */
void mostrarHistograma(string titulo, Mat bgrMap) {

	Mat hist;

	// Número de valores posible.
	int histSize = 256;

	// Se define el rango del histograma.
	float rango[] = { 0, 255 } ;
	const float* histRango = { rango };

	// Se calcula el histograma.
	calcHist( &bgrMap, 1, 0, Mat(), hist, 1, &histSize,
			&histRango, true, false );

	// Se definen los valores de la ventana.
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );
	// Matriz a mostrar.
	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	// Se normalizan los resultados para que entren en el histograma.
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	// Se dibujan los canales
	for( int i = 1; i < histSize; i++ ) {
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
				Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
				Scalar( 0, 0, 255), 2, 8, 0  );
	}

		// Se muestra el histograma
		namedWindow(titulo, CV_WINDOW_AUTOSIZE );
		imshow(titulo, histImage );
}



