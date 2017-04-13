#include "panorama.hpp"

/*
 * Método principal que lanza la ejecución de todo el programa para detectar
 * el punto de fuga.
 */
int main(int argc, char *argv[]) {

	if(argc > 1 ) {			// Comprueba el número de argumentos.
		cout << "Número de parámetros incorrecto." << endl;
		return 0;
	}

	char key = 0;		// Variable para la tecla pulsada.
	string ruta;	// Variable para la ruta de las imágenes.
	bool finalizado = false;		// Booleano para indicar que se ha terminado.

	while(!finalizado){	// Bucle para indicar cuando terminar el programa.

		menu();			// Se muestra el menú.
		cin >> key;		// Se lee la tecla pulsada.

		switch(key){		// Se realiza una acción dependiendo de la tecla.
		case 49:		// Se lee las imágenes desde un directorio.
			cout << "Escriba la ruta: ";	// Se escribe la ruta de las imágenes.
			cin >> ruta;	// Se lee la ruta de las imágenes.
			leerArchivos(ruta);		// Se leen las imágenes y se guardan en una lista.
			break;
		case 50:		// Se toma imágenes por teclado.
			cout << "Capturando del teclado..." << endl;
			capturarTeclado();		// Se captura del teclado.
			break;
		case 51:		// Se toma imágenes en directo.
			cout << "Capturando fotos (automáticamente) cada " << tiempo/1000 << " segundos..." << endl;
			capturarAutomatica();		// Se obtienen las fotos de forma automática.
			break;
		case 52:		// Se indica que se ha salido.
			finalizado = true;
			break;
		default:
			cout << "Opción incorrecta." << endl;
		}

	}

}

/*
 * Método que muestra el menú de operaciones para elegir si coger imágenes
 * de disco o directamente desde la cámara.
 */
void menu(){

	// Se muestra el menú.
	cout << endl;
	cout << " ----------------------------------" << endl;
	cout << "|       MENÚ DE OPERACIONES        |" << endl;
	cout << " ----------------------------------" << endl;
	cout << "| 1.- Imágenes de disco            |" << endl;
	cout << "| 2.- Toma de imágenes por teclado |" << endl;
	cout << "| 3.- Toma de imágenes automática  |" << endl;
	cout << "| 4.- Salir.                       |" << endl;
	cout << "-----------------------------------" << endl;

	cout << endl << "Escriba la opción: ";

}

/*
 * Método que lee los archivos de un cierto directorio y los
 * guarda en una lista.
 */
int leerArchivos(string dir){

	DIR * directorio;			// Se crea el puntero para el directorio.
	struct dirent * elemento;	// Estructura para el elemento.
	string elem;		// Nombre del elemento.
	Mat img;			// Matriz para la imagen.

	directorio = opendir(dir.c_str());	// Se abre el directorio.
	if(directorio != NULL){		// Se comprueba si se puede leer.
		elemento = readdir(directorio);	// Se leen los elementos.

		while(elemento != NULL){
			elem = elemento -> d_name;
			// Se comprueba si es elemento correcto.
			if(elem.compare(".") != 0 && elem.compare("..") != 0){
				cout << "Leyendo fichero: " << dir << "/" << elem << endl;
				// Se lee la imagen.
				Mat img = imread(dir+"/"+elem, CV_LOAD_IMAGE_GRAYSCALE);
				if(!img.data){		// Se comprueba si se puede leer la imagen.
					cout <<  "No se puede abrir la imagen: " << elem << endl ;
					return 0;
				}
				// Se redimensiona

				/*
				 * ESTO HABRÁ QUE MIRARLO PARA EL TEMA REDIMENSIONAR
				 * A QUÉ TAMAÑO
				 */
				resize(img, img, Size(512,384), 0, 0, INTER_LINEAR);
				ficheros.push_back(img);		// Se guarda la matriz en la lista.
			}
			elemento = readdir(directorio);	// Se lee el siguiente elemento.
		}

	} else{		// Si no se puede leer, se muestra el error.
		cout << "El directorio no se puede leer." << endl;
	}
	closedir(directorio);		// Se cierra el directorio.

	return 1;

}

/*
 * Método que captura las imágenes con el teclado.
 */
void capturarTeclado(){

	char key = 0;		// Variable para lo pulsado por teclado.
	VideoCapture TheVideoCapturer;		// Objeto para la cámara.
	Mat bgrMap;		// Matríz para lo leído de la cámara.

	TheVideoCapturer.open(camara);	// Se abre la cámara.
	namedWindow("Camara", cv::WINDOW_AUTOSIZE);		// Se crea la ventana.

	if (!TheVideoCapturer.isOpened()) {	// Se comprueban posibles errores.
		cerr << "No se puede abrir la cámara." << endl;
		exit(0);
	}

	TheVideoCapturer.grab();

	while(key != 27 && TheVideoCapturer.grab()) {		// Mientras sea distinto de ESC...

		TheVideoCapturer.retrieve(bgrMap);		// Obtenemos la imagen.
		imshow("Camara", bgrMap);	// Se muestra lo visto por la cámara.

		switch(key){
		case 32:		// Si es espacio, se captura la imagen.
			imshow("Foto", bgrMap);
			break;
		default:		// Si es cualquier otra tecla...
			break;
		}

		key = waitKey(200);				// Leemos la tecla pulsada.

	}

}

/*
 * Método que caputura imágenes automáticamante cada cierto tiempo.
 */
void capturarAutomatica(){

	int numFotos = 0;		// Variable para lo pulsado por teclado.
	VideoCapture TheVideoCapturer;		// Objeto para la cámara.
	Mat bgrMap;		// Matríz para lo leído de la cámara.
	char key = 0;		// Variable de lo leído por teclado.

	TheVideoCapturer.open(camara);	// Se abre la cámara.
	namedWindow("Foto", cv::WINDOW_AUTOSIZE);		// Se crea la ventana.

	if (!TheVideoCapturer.isOpened()) {	// Se comprueban posibles errores.
		cerr << "No se puede abrir la cámara." << endl;
		exit(0);
	}

	TheVideoCapturer.grab();

	cout << "Pulse espacio para empezar..." << endl;

	while(key != 32){
		key = waitKey(20);		// Se espera a que pulse espacio.
	}

	while(numFotos != totalFotos && TheVideoCapturer.grab()) {		// Mientras falten fotos...

		TheVideoCapturer.retrieve(bgrMap);		// Obtenemos la imagen.
		imshow("Foto", bgrMap);		// Se muestra la foto tomada.

		waitKey(tiempo);				// Se espera el tiempo.

		numFotos++;			// Se actualiza el número de fotos tomadas.

	}
}

/*
 * Método que va construyendo el panorama con cada imagen que recibe.
 */
void construirPanorama(Mat nuevaImagen){

	// Va recibiendo en cada llamada la matríz con la nueva imagen
	// y la añade a la variable global panorama.
}
