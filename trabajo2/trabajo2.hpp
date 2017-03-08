#ifndef TRABAJO2_TRABAJO2_HPP_
#define TRABAJO2_TRABAJO2_HPP_
#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>
#include <list>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Métodos para el aprendizaje y reconocimiento.
void leerArchivos(string);	// Función que lee los archivos de un directorio.
Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
Mat umbralizarAdaptativo(Mat);	// Método que umbraliza según el método de Adaptativo.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
void obtenerDescriptores(vector<vector<Point>>);	// Método que obtiene los descriptores.
void guardar();				// Método para guardar los objetos.
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.

// Variables globales utilizadas.
list<string> ficheros;		// Nombre de todos los ficheros del directorio.
// Filestorage para almacenar los objetos.
FileStorage fs ("objetos.xml", FileStorage::WRITE);

#endif
