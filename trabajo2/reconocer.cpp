#include "reconocer.hpp"

/*
 * Método principal que lanza todo el proceso para el reconocimiento
 * de imágenes.
 */
int main(int argc, char *argv[]) {

	argc = 2;
	argv[0] = "reconocer";
	argv[1] = "./clasificarT2/reco1.pgm";

	if(argc != 2) {			// Comprueba el número de argumentos.
		cout << "Usar: reconocer [fichero]" << endl;
		return 0;
	}

	string fichero = argv[1];		// Se obtiene el nombre del fichero.
	reconocer(fichero);			// Se realiza el reconocimiento.
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
		n = fs[objeto + "_" + parametros[i] + "media"];
		media[i] = (float)*(n.begin());		// Insetamos el parámetro.
		n = fs[objeto + "_" + parametros[i] + "varianza"];
		varianza[i] = (float)*(n.begin());		// Insertamos el parámetro.
	}

}

/*
 * Reconoce los objetos de una imagen.
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

	for(int i = 0; i < objetos.size(); i++) {		// Se recorren los objetos.
		leerDatos(objetos.at(i));
		for(int j = 0; j < descriptores.size();j++) {
			float distM = mahalanobis(j);
			cout << distM << endl;
			//COMPROBAR PARA CADA OBJETO SI ALGUNO PASA EL TEST.
		}
	}

}

/*
 * Método que calcula la distancia de mahalanobis de uno de los objetos.
 */
float mahalanobis(int contorno) {

	//Se obtienen los parámetros.
	Vec<float,numParametros> parametros = descriptores.at(contorno);
	float mahalanobis = 0.0;		// Variables para la distancia.
	cout << parametros.cols << endl << endl;
	cout << parametros.rows << endl << endl;
	//Se calcula la distancia de mahalanobis.
	for(int i = 0; i < parametros.cols; i++) {
		mahalanobis += (pow(parametros[i]-media[i],2))/varianza[i];
	}

	return mahalanobis;

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
void obtenerDescriptores(vector<vector<Point>> contornos, string nombre){

	vector<Moments> mu(contornos.size());	// Vector para los momentos.
	double inv[7];		// Array para guardar los momentos invariantes.
	Vec<float,numParametros> momentos;		// Momentos del objeto.

	// Se calculan los momentos para cada objeto.
	for(int i = 0; i < contornos.size(); i++){
		mu[i] = moments(contornos[i], false);
	}

	for(int i = 0; i < contornos.size(); i++){
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