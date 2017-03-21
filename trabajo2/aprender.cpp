#include "aprender.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa.
 */
int main(int argc, char *argv[]) {

	argc = 2;
	argv[0] = "aprender";
	argv[1] = "./imagenesT2";

	if(argc != 2) {			// Comprueba el número de argumentos.
		cout << "Usar: entrenar [directorio]" << endl;
		return 0;
	}

	leerArchivos("./imagenesT2");		// Se leen los archivos de la carpeta.

	// Filestorage para almacenar los objetos (modo escritura).
	fs = FileStorage(fichObjetos, FileStorage::WRITE);
	for(int i = 0; i< objetos.size(); i++) {
		aprendizaje(objetos.at(i));		// Se aprenden los distintos objetos.
	}

	fs.release();		// Se libera el fichero.
	return 0;

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
			elemento = readdir(directorio);	// Se lee el siguiente elemento.
		}
	} else{		// Si no se puede leer, se muestra el error.
		cout << "El directorio no se puede leer." << endl;
	}
	closedir(directorio);		// Se cierra el directorio.

}

/*
 * Método que aprende los distintos objetos.
 */
void aprendizaje(string objeto) {

	Mat imagen;		// Imagen umbralizada.
	vector<vector<Point>> contornos;	// Vector para los contornos.

	list<string>::iterator it;		// Iterador para recorrer los ficheros.
	int n = 0;			// Número de imágenes de un mismo tipo.
	for(it = ficheros.begin(); it != ficheros.end(); it++){		// Recorremos las imágenes.
		string nombre = *it;	// Nombre del fichero.
		// Se comprueba a que objeto corresponde.
		if(nombre.find(objeto) != string::npos){
			// Se lee la imagen.
			Mat imagen = imread(nombre, CV_LOAD_IMAGE_GRAYSCALE);
			if(!imagen.data){		// Se comprueba si se puede leer la imagen.
				cout <<  "No se puede abrir la imagen: " << nombre << endl ;
				exit(1);
			}

			mostrarHistograma("Histograma", imagen);		// Se muestra el histograma.
			imagen = umbralizarOtsu(imagen);		// Umbralizamos la imagen.
			contornos = obtenerBlops(imagen);			// Obtenemos los blops.
			obtenerDescriptores(contornos);			// Obtenemos los descriptores.
			n++;			// Se actualiza el número de ficheros de un mismo tipo.
			waitKey(0);

		}
	}

	calcularDatos(n);	// Se calculan las medias y varianzas.
	descriptores.clear();	// Se eliminan los parametros guardados.
	escribirDatos(objeto,n);		// Se escriben los datos en el fichero.

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
 * Método que obtiene los distintos blops de la imagen.
 */
vector<vector<Point>> obtenerBlops(Mat imagen){

	vector<vector<Point> > contornos;	// Vector para puntos del contorno.
	vector<Vec4i> jerarquia;		// Vector para la jerarquía.

	// Se obtienen los contornos.
	findContours(imagen, contornos, jerarquia,
			CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0, 0));

	// Se dibujan los contornos.
	RNG rng(12345);		// Variable para mostrar contornos.
	Mat drawing = Mat::zeros(imagen.size(), CV_8UC3);
	for(int i = 0; i< contornos.size(); i++){
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours(drawing, contornos, i, color, CV_FILLED, 8, jerarquia, 0, Point());
	}

	// Se muestra la imagen.
	namedWindow("Contornos", CV_WINDOW_AUTOSIZE);
	imshow("Contornos", drawing);

	return contornos;			// Se devuelven los contornos.

}

/*
 * Método que obtiene los descriptores de la imagen.
 */
void obtenerDescriptores(vector<vector<Point>> contornos){

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

/*
 * Método que recorre el fichero actualizando los datos y guardando
 * la media y la varianza.
 */
void calcularDatos(int num) {

	Vec<float,5> varParcial;	// Vector auxiliar para la varianza.
	// Se inicializan a 0 media y varianza.
	media = {0.0, 0.0, 0.0, 0.0, 0.0};
	varianza = {0.0, 0.0, 0.0, 0.0, 0.0};

	// Se calculan los valores para cada descriptor.
	for(int i = 0; i < descriptores.size(); i++) {
		media = media + descriptores.at(i);
	}

	media = media / num;		// Se calcula la media.

	// Se calculan los valores para cada descriptor.
	for(int i = 0; i < descriptores.size(); i++) {
		for(int j = 0; j<descriptores.at(i).rows; j++){
			// Se calcula la varianza.
			varParcial[j] = (descriptores.at(i)[j] - media[j]) *
					(descriptores.at(i)[j] - media[j]);
		}
		varianza = varianza + varParcial;
	}

	varianza = varianza / (num-1);		// Se calcula la varianza.

}

/*
 * Método que escribe los datos de medias y varianzas en el fichero.
 */
void escribirDatos(string objeto, int num) {

	// Escribe el número de objetos del tipo.
	fs << objeto + "_" + "numero" << "[";
	fs << num;
	fs << "]";
	for(int i = 0; i < numParametros; i++) {
		// Se escriben la media y varianza de cada descriptor.
		fs << objeto + "_" + parametros[i] + "_" + "media" << "[";
		fs << media[i];
		fs << "]";
		fs << objeto + "_" + parametros[i] + "_" + "varianza" << "[";
		fs << varianza[i];
		fs << "]";
	}

}
