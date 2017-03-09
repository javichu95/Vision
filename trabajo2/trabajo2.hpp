#ifndef TRABAJO2_TRABAJO2_HPP_
#define TRABAJO2_TRABAJO2_HPP_
#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>
#include <list>

// Espacios de nombres.
using namespace cv;
using namespace std;

enum{AREA = 0, PERIMETRO = 1, INV_1 = 2, INV_2 = 3, INV_3 = 4};
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
string extension = ".pgm";

// Métodos para el aprendizaje y reconocimiento.
void leerArchivos(string);	// Función que lee los archivos de un directorio.
Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
Mat umbralizarAdaptativo(Mat);	// Método que umbraliza según el método de Adaptativo.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
void obtenerDescriptores(vector<vector<Point>>,int);	// Método que obtiene los descriptores.
void guardarObjeto(string objeto);				// Método para guardar los objetos.
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.
void aprendizaje(); //Metodo que itera sobre diferentes objetos.
void calcularMedia(int); //Metodo que calcula las medias de los parametros.
void calcularVarianza(int); //Metodo que calcula las varianzas de los parametros.

// Variables globales utilizadas.
list<string> ficheros;		// Nombre de todos los ficheros del directorio.
// Filestorage para almacenar los objetos.
FileStorage fs ("objetos.xml", FileStorage::WRITE);
vector<double[5]> parametros;
double media[5];
double varianza[5];

#endif
