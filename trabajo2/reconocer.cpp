#include "reconocer.hpp"

/*
 * Método principal que lanza todo el proceso para el reconocimiento
 * de imágenes.
 */
int main(int argc, char *argv[]) {

	argc = 2;
	argv[0] = "reconocer";
	argv[1] = "./imagenesT2/reco1.pgm";

	if(argc != 2) {			// Comprueba el número de argumentos.
		cout << "Usar: reconocer [fichero]" << endl;
		return 0;
	}

	string fichero = argv[1];		// Se obtiene el nombre del fichero.
	reconocer(fichero);			// Se realiza el reconocimiento.
}

/*
 * Método que reconoce los objetos de una imagen.
 */
void reconocer(string fich) {

	vector<vector<Point>> contornos;	// Vector para los contornos.
	Mat imgUm;		// Matriz para la imagen umbralizada.

	Mat img = imread(fich,CV_LOAD_IMAGE_GRAYSCALE);
	if(!img.data){		// Se comprueba si se puede leer la imagen.
		cout <<  "No se puede abrir la imagen: " << fich << endl ;
		exit(1);
	}

	imgUm = umbralizarOtsu(img);		// Umbralizamos la imagen.
	contornos = obtenerBlops(imgUm);			// Obtenemos los blops.
	obtenerDescriptores(contornos, fich);		// Obtenemos los descriptores.

	for(uint i = 0; i < descriptores.size(); i++) {		// Se recorren los descriptores.
		tipoContorno.clear();			// Se vacía el vector.
		for(uint j = 0; j < objetos.size(); j++) {		// Se recorren los objetos.
			leerDatos(objetos.at(j));		// Se leen los datos del objeto.
			float distM = mahalanobis(i);		// Se calcula la distancia a ese objeto.
			if(distM <= valChi){		// Si cumple el criterio.
				tipoContorno.push_back(objetos.at(j));		// Se añade a la lista.
			}
		}
		dibujarBlops(i,imgUm,"blop");
		mostrarResultados();		// Se muestran los resultados.
		waitKey(0);
	}

}

/*
 * Método que lee los datos del fichero objetos.
 */
void leerDatos(string objeto) {

	fs = FileStorage(fichObjetos, FileStorage::READ);		// Se abre el fichero para lectura.
	for(int i = 0; i < numParametros; i++) {
		FileNode n;		// Nodo para leer los datos.
		FileNodeIterator itPar;		// Iterador para recorrer la lista de parámetros.
		// Obtenemos el nodo de los parámetros.
		n = fs[objeto + "_" + parametros[i] + "_" + "media"];
		media[i] = (float)*(n.begin());		// Insetamos el parámetro.
		n = fs[objeto + "_" + parametros[i] + "_" + "varianza"];
		varianza[i] = (float)*(n.begin());		// Insertamos el parámetro.
	}

}

/*
 * Método que calcula la distancia de mahalanobis de uno de los objetos.
 */
float mahalanobis(int contorno) {

	//Se obtienen los parámetros.
	Vec<float,numParametros> parametros = descriptores.at(contorno);
	float mahalanobis = 0.0;		// Variables para la distancia.
	//Se calcula la distancia de mahalanobis.
	for(int i = 0; i < parametros.rows; i++) {
		mahalanobis += (pow(parametros[i]-media[i],2))/varianza[i];
	}

	return mahalanobis;		// Se devuelve la distancia.

}

/*
 * Método que muestra los resultados por pantalla.
 */
void mostrarResultados(){

	if(tipoContorno.size() == 0){
		// El objeto es desconocido.
		cout << "El objeto es desconocido." << endl;
	} else if(tipoContorno.size() == 1){
		// El objeto es de solo una clase.
		cout << "El objeto es " << tipoContorno.at(0) << "." << endl;
	} else{
		// Se recorren las clases de ese contorno.
		cout << "El objeto es ";
		for (uint j = 0; j < tipoContorno.size(); j++){
			if(j != tipoContorno.size() - 1){
				cout << tipoContorno.at(j) << " ó ";
			} else{
				cout << tipoContorno.at(j) << "." << endl;
			}
		}
	}

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

	vector<vector<Point>> contornos;	// Vector para puntos del contorno.
	vector<Vec4i> jerarquia;		// Vector para la jerarquía.

	// Se obtienen los contornos.
	findContours(imagen, contornos, jerarquia,
			CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));

	return contornos;

}

/*
 * Método que muestra los blops por pantalla.
 */
void dibujarBlops(int indice, Mat imagen, string objeto){

	vector<vector<Point>> contornos;	// Vector para puntos del contorno.
	vector<Vec4i> jerarquia;		// Vector para la jerarquía.

	// Se obtienen los contornos.
	findContours(imagen, contornos, jerarquia,
			CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

	// Se dibujan los contornos.
	RNG rng(12345);		// Variable para mostrar contornos.
	Mat drawing = Mat::zeros(imagen.size(), CV_8UC3);
	Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	drawContours(drawing, contornos, indice, color, CV_FILLED, 8, jerarquia, 0, Point());

	/// Se muestra la imagen.
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	imshow( "Contours", drawing );
}

/*
 * Método que obtiene los descriptores de la imagen.
 */
void obtenerDescriptores(vector<vector<Point>> contornos, string nombre){

	vector<Moments> mu(contornos.size());	// Vector para los momentos.
	double inv[7];		// Array para guardar los momentos invariantes.
	Vec<float,numParametros> momentos;		// Momentos del objeto.

	// Se calculan los momentos para cada objeto.
	for(uint i = 0; i < contornos.size(); i++){
		mu[i] = moments(contornos[i], false);
	}

	for(uint i = 0; i < contornos.size(); i++){
		// Se comprueba si es el contorno válido.
		if(contornos.size() == 1 || (contornos.size() > 1 && mu[i].m00 > 500)){
			momentos[0] = mu[i].m00;	// Se obtiene el área.
			// Se calcula el perímetro.
			momentos[1] = (arcLength(contornos[i],true));

			// Se obtienen los momentos invariantes.
			HuMoments(mu[i],inv);
			momentos[2] = inv[0];
			momentos[3] = inv[1];
			momentos[4] = inv[2];
			descriptores.push_back(momentos);		// Se añaden los descriptores.
		}
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
