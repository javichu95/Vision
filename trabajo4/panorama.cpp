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

		primera = true;
		menu();			// Se muestra el menú.
		cin >> key;		// Se lee la tecla pulsada.

		switch(key){		// Se realiza una acción dependiendo de la tecla.
		case 49:		// Se lee las imágenes desde un directorio.
			cout << "Escriba la ruta: ";	// Se escribe la ruta de las imágenes.
			cin >> ruta;	// Se lee la ruta de las imágenes.
			leerArchivos(ruta);		// Se leen las imágenes y se guardan en una lista.
			capturarDirectorio();	// Se crea el panorama con las imágenes del directorio.
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
				Mat img = imread(dir+"/"+elem, CV_LOAD_IMAGE_COLOR);
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
 * Método que crea el panorama con las imágenes que se han obtenido del
 * directorio.
 */
void capturarDirectorio(){

	int longitud = ficheros.size();		// Número de imágenes.

	for(int i=0; i<longitud; i++){		// Recorremos las imágenes.

		Mat imagen = ficheros.front();
		ficheros.pop_front();		// Se saca la imagen de la lista.
		cvtColor(imagen, imagen, CV_BGR2GRAY);		// Se pasa a escala de grises.

		if(primera){		// Se comprueba si es la primera imagen.
			primera = false;
			crearPrimera(imagen);		// Se crea la primera imagen.
		} else{
			construirPanorama(imagen);		// Se construye el panorama.
		}


	}

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
			cvtColor(bgrMap, bgrMap, CV_BGR2GRAY);		// Se pasa a escala de grises.

			if(primera){		// Se comprueba si es la primera imagen.
				primera = false;
				crearPrimera(bgrMap);		// Se crea la primera imagen.
			} else{
				construirPanorama(bgrMap);		// Se añade al panorama.
			}

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
		cvtColor(bgrMap, bgrMap, CV_BGR2GRAY);		// Se pasa a escala de grises.

		if(primera){		// Se comprueba si es la primera imagen.
			primera = false;
			crearPrimera(bgrMap);		// Se crea la primera imagen.
		} else{
			construirPanorama(bgrMap);		// Se añade al panorama.
		}

		waitKey(tiempo);				// Se espera el tiempo.

		numFotos++;			// Se actualiza el número de fotos tomadas.

	}

}

/*
 * Método que añade la primera imagen del panorama.
 */
void crearPrimera(Mat imagen){

	panorama = imagen;

	// Vector para los puntos de interés.
	vector<KeyPoint> keyptsPano;

	// Obtenemos los puntos de interés.
	surf->detect(panorama,keyptsPano,noArray());

	// Matriz para los descriptores.
	Mat descPano;

	// Obtenemos los descriptores.
	surf->compute(panorama, keyptsPano, descPano);
	//surf->detectAndCompute(panorama, noArray(), keyptsPano, descPano);

	// Matriz para dibujar los puntos.
	Mat img_kptsPano;

	// Se dibujan los puntos.
	drawKeypoints(panorama, keyptsPano, img_kptsPano, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT );
	imshow("Puntos de interes panorama",img_kptsPano);

	waitKey(0);

}

/*
 * Método que va construyendo el panorama con cada imagen que recibe.
 */
void construirPanorama(Mat nuevaImagen){

	// Vector para los puntos de interés.
	vector<KeyPoint> keyptsNueva, keyptsPano;

	// Obtenemos los puntos de interés.
	surf->detect(nuevaImagen,keyptsNueva,noArray());
	surf->detect(panorama,keyptsPano,noArray());

	// Matriz para los descriptores.
	Mat descNueva, descPano;

	// Obtenemos los descriptores.
	surf->compute(nuevaImagen, keyptsNueva, descNueva);
	surf->compute(panorama, keyptsPano, descPano);
	//surf->detectAndCompute(nuevaImagen, noArray(), keyptsNueva, descNueva);
	//surf->detectAndCompute(panorama, noArray(), keyptsPano, descPano);

	// Matriz para dibujar los puntos.
	Mat img_kptsNueva, img_kptsPano;

	// Se dibujan los puntos.
	drawKeypoints(nuevaImagen, keyptsNueva, img_kptsNueva, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT );
	imshow("Puntos de interes nueva",img_kptsNueva);
	drawKeypoints(panorama, keyptsPano, img_kptsPano, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT );
	imshow("Puntos de interes panorama",img_kptsPano);

	waitKey(0);

	// Se declara el comparador por fuerza bruta.
	Ptr<BFMatcher> bf = BFMatcher::create(NORM_L2);
	vector<vector<DMatch>> matches;			// Vector de vectores con los matches.

	// Se obtienen los dos vecinos más cercanos.
	bf->knnMatch(descNueva, descPano, matches, 2);

	// Se obtienen los emparejamientos buenos con el ratio 0,8.
	vector<cv::DMatch> matchesCorrec;
	for (int i = 0; i < matches.size(); ++i){
		// Se comprueba si cumplen el ratio.
		if (matches[i][0].distance < diff * matches[i][1].distance){
			matchesCorrec.push_back(matches[i][0]);
		}
	}

	Mat img_matches;			// Matriz para mostrar los matches.

	// Se dibujan los matches correctos.
	drawMatches(nuevaImagen, keyptsNueva, panorama, keyptsPano, matchesCorrec, img_matches);
	imshow("Matches",img_matches);

	waitKey(0);

}
