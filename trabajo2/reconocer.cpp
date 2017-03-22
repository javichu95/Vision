#include "reconocer.hpp"

/*
 * Método principal que lanza todo el proceso para el reconocimiento
 * de imágenes.
 */
int main(int argc, char *argv[]) {

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

	// Se lee la imagen.
	Mat img = imread(fich,CV_LOAD_IMAGE_GRAYSCALE);
	if(!img.data){		// Se comprueba si se puede leer la imagen.
		cout <<  "No se puede abrir la imagen: " << fich << endl ;
		exit(1);
	}

	imgUm = umbralizarOtsu(img);		// Umbralizamos la imagen.
	contornos = obtenerBlops(imgUm);			// Obtenemos los blops.
	obtenerDescriptores(contornos,descriptores, indicesBlop);		// Obtenemos los descriptores.

	for(uint i = 0; i < descriptores.size(); i++) {		// Se recorren los descriptores.
		tipoContorno.clear();			// Se vacía el vector.
		for(uint j = 0; j < objetos.size(); j++) {		// Se recorren los objetos.
			leerDatos(objetos.at(j));		// Se leen los datos del objeto.
			float distM = mahalanobis(i);		// Se calcula la distancia a ese objeto.
			if(distM <= valChi){		// Si cumple el criterio.
				tipoContorno.push_back(objetos.at(j));		// Se añade a la lista.
			}
		}
		int indiceBlop = indicesBlop.front();		// Se saca el índice del blop.
		indicesBlop.pop_front();			// Se elimina el índice de la lista.
		dibujarBlops(indiceBlop,imgUm,"blop");		// Se dibuja el blop.
		mostrarResultados();		// Se muestran los resultados.
		waitKey(0);
	}

}

/*
 * Método que lee los datos del fichero de objetos (media y varianza de cada momento).
 */
void leerDatos(string objeto) {

	fs = FileStorage(fichObjetos, FileStorage::READ);		// Se abre el fichero para lectura.

	for(int i = 0; i < numParametros; i++) {		// Se recorren los parámetros.
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
