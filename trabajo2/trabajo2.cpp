#include "trabajo2.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	Mat imagen1, imagen2;		// Imagen devuelta por cada método.
	vector<vector<Point>> contornos;	// Vector para los contornos.
	leerArchivos("./imagenesT2");		// Se leen los archivos de la carpeta.

	// Creamos iterador.
	std::list<string>::iterator it = ficheros.begin();
	while(it != ficheros.end()){		// Recorremos las imagenes.
		Mat imagen = imread(*it, CV_LOAD_IMAGE_GRAYSCALE);

		if(!imagen.data){		// Se comprueba si se puede ller la imagen.
			cout <<  "No se puede abrir la imagen: " << *it << endl ;
			exit(1);
		}

		mostrarHistograma("Histograma", imagen);		// Se muestra el histograma.
		imagen1 = umbralizarOtsu(imagen);		// Umbralizamos la imagen.
		imagen2 = umbralizarAdaptativo(imagen);
		contornos = obtenerBlops(imagen1);			// Obtenemos los blops.
		obtenerDescriptores(contornos);			// Obtenemos los descriptores.

		++it;		// Actualizamos iterador.
		waitKey(0);
	}

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
 * Método que umbraliza según el método de Otsu.
 */
Mat umbralizarOtsu(Mat imagen){

	// Aplicamos el threshold.
	threshold(imagen,imagen,0,255,THRESH_BINARY_INV | THRESH_OTSU);
	namedWindow( "Otsu", CV_WINDOW_AUTOSIZE );
	imshow("Otsu", imagen);		// Devolvemos la matriz.
	return imagen;
}


/*
 * Método que umbraliza según el método adaptativo.
 */
Mat umbralizarAdaptativo(Mat imagen){

	Mat imagen1, imagen2;

	// Aplicamos el threshold.
	adaptiveThreshold(imagen,imagen1,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV,51,2);
	namedWindow( "Adaptativo media", CV_WINDOW_AUTOSIZE );
	imshow("Adaptativo media", imagen1);
	adaptiveThreshold(imagen,imagen2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,51,2);
	namedWindow( "Adaptativo gauss", CV_WINDOW_AUTOSIZE );
	imshow("Adaptativo gauss", imagen1);
	return imagen;			// Devolvemos la matriz.
}

/*
 * Método que obtiene los distintos blops de la imagen.
 */
vector<vector<Point>> obtenerBlops(Mat imagen){

	vector<vector<Point> > contornos;	// Vector para puntos del contorno.
	vector<vector<Point> > contornos1;	// Vector para puntos del contorno.
	vector<vector<Point> > contornos2;	// Vector para puntos del contorno.
	vector<vector<Point> > contornos3;	// Vector para puntos del contorno.
	vector<Vec4i> jerarquia;		// Vector para la jerarquía.
	vector<Vec4i> jerarquia1;		// Vector para la jerarquía.
	vector<Vec4i> jerarquia2;		// Vector para la jerarquía.
	vector<Vec4i> jerarquia3;		// Vector para la jerarquía.

	// Se obtienen los contornos.
	findContours(imagen, contornos, jerarquia,
			CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
	findContours(imagen, contornos1, jerarquia1,
			CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0, 0));
	findContours(imagen, contornos2, jerarquia2,
			CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0, 0));
	findContours(imagen, contornos3, jerarquia3,
			CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));

	// Se dibujan los contornos.
	RNG rng(12345);		// Variable para mostrar contornos.
	Mat drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( int i = 0; i< contornos.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos, i, color, 2, 8, jerarquia, 0, Point());
	}

	/// Se muestra la imagen.
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	imshow( "Contours", drawing );

	drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( int i = 0; i< contornos1.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos1, i, color, 2, 8, jerarquia1, 0, Point());
	}

	/// Show in a window
	namedWindow( "Contours1", CV_WINDOW_AUTOSIZE );
	imshow( "Contours1", drawing );

	drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( int i = 0; i< contornos2.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos2, i, color, 2, 8, jerarquia2, 0, Point());
	}

	/// Show in a window
	namedWindow( "Contours2", CV_WINDOW_AUTOSIZE );
	imshow( "Contours2", drawing );

	drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( int i = 0; i< contornos3.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos3, i, color, 2, 8, jerarquia3, 0, Point());
	}

	/// Show in a window
	namedWindow( "Contours3", CV_WINDOW_AUTOSIZE );
	imshow( "Contours3", drawing );

	return contornos;
}

/*
 * Método que obtiene los descriptores de la imagen.
 */
void obtenerDescriptores(vector<vector<Point>> contornos){

	vector<Moments> mu(contornos.size());	// Vector para los momentos.
	// Se calculan los momentos para cada objeto.
	for( int i = 0; i < contornos.size(); i++ ){
		mu[i] = moments(contornos[i], false );
	}
	for( int i = 0; i < contornos.size(); i++ ){
		// Aplicar filtro por área del contorno.
		cout << "El tamaño del contorno es: " << contornos.size() << endl;
		cout << "El área del contorno es: " << mu[i].m00 << endl;
	}

}

/*
 * Método que guarda o actualiza los parámetros del objeto en
 * el fichero.
 */
void guardarObjeto(){

	// Utilizar fs para ir guardando si ya hay un objeto con ese nombre.

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
