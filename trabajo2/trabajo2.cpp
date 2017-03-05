#include "trabajo2.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	leerArchivos("./imagenesT2");		// Se leen los archivos de la carpeta.

	//mostrarHistogramas();

	umbralizar();
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
void umbralizar(){

	// Método adaptativo u Otsu.
	Mat umbralizada1, umbralizada2;

	// Creamos iterador.
	std::list<string>::iterator it = ficheros.begin();
	while(it != ficheros.end()){		// Recorremos las imagenes.
		Mat imagen = imread(*it, CV_LOAD_IMAGE_GRAYSCALE);

		if(!imagen.data){		// Se comprueba si se puede ller la imagen.
			cout <<  "No se puede abrir la imagen: " << *it << endl ;
			exit(1);
		}

		umbralizada1 = metodoOtsu(imagen);		// Umbralizamos la imagen.
		umbralizada2 = metodoAdaptativo(imagen);
		++it;		// Actualizamos iterador.
		waitKey(0);
	}

}

/*
 * Método que umbraliza según el método de Otsu.
 */
Mat metodoOtsu(Mat imagen){

	threshold(imagen,imagen,0,255,THRESH_BINARY | THRESH_OTSU);
	namedWindow( "Otsu", CV_WINDOW_AUTOSIZE );
	imshow("Otsu", imagen);
	return imagen;
}


/*
 * Método que umbraliza según el método adaptativo.
 */
Mat metodoAdaptativo(Mat imagen){

	Mat imagen1, imagen2;
	adaptiveThreshold(imagen,imagen1,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,51,2);
	namedWindow( "Adaptativo media", CV_WINDOW_AUTOSIZE );
	imshow("Adaptativo media", imagen1);
	adaptiveThreshold(imagen,imagen2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,51,2);
	namedWindow( "Adaptativo gauss", CV_WINDOW_AUTOSIZE );
	imshow("Adaptativo gauss", imagen1);
	return imagen;
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
 * Método que muestra los histogramas de los archivos.
 */
void mostrarHistogramas(){

	// Creamos iterador.
	std::list<string>::iterator it = ficheros.begin();
	while(it != ficheros.end()){		// Recorremos las imagenes.
		Mat imagen = imread(*it, CV_LOAD_IMAGE_GRAYSCALE);
		mostrarHistograma(*it,imagen);		// Generamos histograma.
		++it;		// Actualizamos iterador.
		waitKey(0);
	}

}

/*
 * Método que muestra el histograma de una imagen.
 */
void mostrarHistograma(string titulo, Mat bgrMap) {

	Mat hist;	// Matriz para el histograma.

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
