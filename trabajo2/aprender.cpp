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
	fsEstimada = FileStorage(fichObjetosEst, FileStorage::WRITE);
	for(uint i = 0; i< objetos.size(); i++) {
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
			obtenerDescriptores(contornos,descriptores,indicesBlop);			// Obtenemos los descriptores.
			n++;			// Se actualiza el número de ficheros de un mismo tipo.
			waitKey(0);

		}
	}

	calcularDatos(n);	// Se calculan las medias y varianzas.
	descriptores.clear();	// Se eliminan los parametros guardados.
	escribirDatos(objeto,n);		// Se escriben los datos en el fichero.

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
	varianzaEstimada = {0.0, 0.0, 0.0, 0.0, 0.0};

	// Se calculan los valores para cada descriptor.
	for(uint i = 0; i < descriptores.size(); i++) {
		media = media + descriptores.at(i);
	}

	media = media / num;		// Se calcula la media.

	// Se calculan los valores para cada descriptor.
	for(uint i = 0; i < descriptores.size(); i++) {
		for(int j = 0; j<descriptores.at(i).rows; j++){
			// Se calcula la varianza.
			varParcial[j] = (descriptores.at(i)[j] - media[j]) *
					(descriptores.at(i)[j] - media[j]);
		}
		varianza = varianza + varParcial;
	}

	varianza = varianza / (num-1);		// Se calcula la varianza.

	//Se calcula la varianza estimada.
	varianzaEstimada = (media*porcentaje);
	for(uint i = 0; i < numParametros; i++) {
			// Se calcula la varianza.
			varianzaEstimada[i] = varianzaEstimada[i]*varianzaEstimada[i];
	}

}

/*
 * Método que escribe los datos de medias y varianzas en el fichero.
 */
void escribirDatos(string objeto, int num) {

	// Escribe el número de objetos del tipo.
	fs << objeto + "_" + "numero" << "[";
	fs << num;
	fs << "]";
	fsEstimada << objeto + "_" + "numero" << "[";
	fsEstimada << num;
	fsEstimada << "]";
	for(int i = 0; i < numParametros; i++) {
		// Se escriben la media y varianza de cada descriptor.
		fs << objeto + "_" + parametros[i] + "_" + "media" << "[";
		fs << media[i];
		fs << "]";
		fs << objeto + "_" + parametros[i] + "_" + "varianza" << "[";
		fs << varianza[i];
		fs << "]";

		fsEstimada << objeto + "_" + parametros[i] + "_" + "media" << "[";
		fsEstimada << media[i];
		fsEstimada << "]";
		fsEstimada << objeto + "_" + parametros[i] + "_" + "varianza" << "[";
		fsEstimada << varianzaEstimada[i];
		fsEstimada << "]";
	}

}
