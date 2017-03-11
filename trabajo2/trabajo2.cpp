#include "trabajo2.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	leerArchivos("./imagenesT2");		// Se leen los archivos de la carpeta.

	aprendizaje();		// Se aprenden los distintos objetos.
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
 * Método que aprende los distintos objetos.
 */
void aprendizaje() {

	Mat imagen1, imagen2;		// Imagen devuelta por cada método.
	vector<vector<Point>> contornos;	// Vector para los contornos.

	list<string>::iterator it;		// Iterador para recorrer los ficheros.

	for(it = ficheros.begin(); it != ficheros.end(); it++){		// Recorremos las imagenes.
		bool encontrado = false;
		for(int i=0; !encontrado && i<objetos.size(); i++){

			string nombre = *it;
			// Se comprueba a que objeto corresponde.
			if(nombre.find(objetos.at(i)) != string::npos){
				Mat imagen = imread(nombre, CV_LOAD_IMAGE_GRAYSCALE);
				if(!imagen.data){		// Se comprueba si se puede leer la imagen.
					cout <<  "No se puede abrir la imagen: " << nombre << endl ;
					exit(1);
				}

				mostrarHistograma("Histograma", imagen);		// Se muestra el histograma.
				imagen1 = umbralizarOtsu(imagen);		// Umbralizamos la imagen.
				contornos = obtenerBlops(imagen1);			// Obtenemos los blops.
				obtenerDescriptores(contornos,i,*it);			// Obtenemos los descriptores.
				encontrado = true;		// Se indica que se ha procesado.
				numFicheros++;			// Se actualiza el número de ficheros procesados.
				waitKey(0);
			}
		}
	}
	fs.release();		// Se cierra el fichero.
	FileStorage fs("objetos.yml", FileStorage::READ);
	calcularDatos();	// Se calculan las medias y varianzas.

}

/*
 * Método que umbraliza según el método de Otsu.
 */
Mat umbralizarOtsu(Mat imagen){

	// Aplicamos el threshold.
	threshold(imagen,imagen,0,255,THRESH_BINARY_INV | THRESH_OTSU);
	namedWindow( "Otsu", CV_WINDOW_AUTOSIZE );
	imshow("Otsu", imagen);
	return imagen;	// Devolvemos la matriz.
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
	for( uint i = 0; i< contornos.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos, i, color, CV_FILLED, 8, jerarquia, 0, Point());
	}

	/// Se muestra la imagen.
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	imshow( "Contours", drawing );

	drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( uint i = 0; i< contornos1.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos1, i, color, CV_FILLED, 8, jerarquia1, 0, Point());
	}

	/// Show in a window
	namedWindow( "Contours1", CV_WINDOW_AUTOSIZE );
	imshow( "Contours1", drawing );

	drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( uint i = 0; i< contornos2.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos2, i, color, CV_FILLED, 8, jerarquia2, 0, Point());
	}

	/// Show in a window
	namedWindow( "Contours2", CV_WINDOW_AUTOSIZE );
	imshow( "Contours2", drawing );

	drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for( uint i = 0; i< contornos3.size(); i++ )
	{
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos3, i, color, CV_FILLED, 8, jerarquia3, 0, Point());
	}

	/// Show in a window
	namedWindow( "Contours3", CV_WINDOW_AUTOSIZE );
	imshow( "Contours3", drawing );

	return contornos;
}

/*
 * Método que obtiene los descriptores de la imagen.
 */
void obtenerDescriptores(vector<vector<Point>> contornos, int indice, string nombre){

	vector<Moments> mu(contornos.size());	// Vector para los momentos.
	double inv[7];		// Array para guardar los momentos invariantes.
	float momentos [5];		// Momentos del objeto.

	// Se calculan los momentos para cada objeto.
	for(uint i = 0; i < contornos.size(); i++){
		mu[i] = moments(contornos[i], false);
	}

	// Se aplica filtro de área.
	for(int i = 0; i < contornos.size(); i++){
		// Se comprueba si es el contorno válido.
		if(contornos.size() == 1 || (contornos.size() > 1 && mu[i].m00 > 500)){
			momentos[AREA] = mu[i].m00;	// Se obtiene el área.
			// Se calcula el perímetro.
			momentos[PERIMETRO] = arcLength(contornos[i],true);

			// Se obtienen los momentos invariantes.
			HuMoments(mu[i],inv);
			momentos[INV_1] = inv[0];
			momentos[INV_2] = inv[1];
			momentos[INV_3] = inv[2];
		}
	}

	// Se obtiene el nombre del fichero.
	String nomFichero = nombre.substr(nombre.find_last_of("/")+1,nombre.length());
	nomFichero = nomFichero.substr(0,nomFichero.find_last_of("."));
	// Se escriben los datos en el fichero.
	fs << "PARAMETROS_" + nomFichero << "[:";
	for(int i=AREA; i<INV_3; i++){
		fs << momentos[i];
	}
	fs << "]";

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

/*
 * Método que recorre el fichero actualizando los datos y guardando
 * la media y la varianza.
 */
void calcularDatos() {

	list<string>::iterator it;		// Iterador para recorrer los ficheros.
	Vec<float,5> parametros;		// Vector para los parámetros.
	String nomFichero;			// String para el nombre del fichero.
	Vec<float,5> varParcial;	// Vector auxiliar para la varianza.

	for(it = ficheros.begin(); it != ficheros.end(); it++){		// Recorremos las imagenes.
		nomFichero = (*it).substr((*it).find_last_of("/")+1,(*it).length());
		nomFichero = nomFichero.substr(0,nomFichero.find_last_of("."));
		fs["PARAMETROS"+nomFichero] >> parametros;
		media = media + parametros;		// Se acumulan los valores.
		waitKey();
	}

	media = media / numFicheros;		// Se calcula la media.

	for(it = ficheros.begin(); it != ficheros.end(); it++){		// Recorremos las imagenes.
		nomFichero = (*it).substr((*it).find_last_of("/")+1,(*it).length());
		nomFichero = nomFichero.substr(0,nomFichero.find_last_of("."));
		fs["PARAMETROS"+nomFichero] >> parametros;
		for(int j = 0; j<parametros.cols; j++){
			// Se calcula la varianza.
			varParcial[j] = (parametros[j] - media[j]) * (parametros[j] - media[j]);
			varianza = varianza + varParcial;
		}
		waitKey();
	}

	varianza = varianza / (numFicheros-1);		// Se calcula la varianza.

}
