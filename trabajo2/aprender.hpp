#ifndef SRC_APRENDER_APRENDER_HPP_
#define SRC_APRENDER_APRENDER_HPP_

#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>
#include <list>
#include <iostream>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Métodos para el aprendizaje.
void leerArchivos(string);	// Función que lee los archivos de un directorio.
void aprendizaje(string objeto); // Método que itera sobre diferentes objetos.
Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
void obtenerDescriptores(vector<vector<Point>>);	// Método que obtiene los descriptores.
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.
void calcularDatos(int);		// Método que calcula las medias y varianzas.
void escribirDatos(string,int); 		// Escribe los datos en el fichero.

// Variables globales utilizadas.
list<string> ficheros;		// Nombre de todos los ficheros del directorio.
const string fichObjetos = "objetos.yml";			// Variable con el nombre del fichero de objetos.
// Tipo enumerado para los parámetros.
enum{AREA = 0, PERIMETRO = 1, INV_1 = 2, INV_2 = 3, INV_3 = 4};
// Parámetros o descriptores de cada objeto.
vector<string> parametros = {"area", "perimetro", "invariante1", "invariante2","invariante3"};
const int numParametros = 5;		// Número de parámetros o momentos.
// Tipos de objetos a reconocer.
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
FileStorage fs;		// Filestorage para almacenar los objetos.
vector<Vec<float,5>> descriptores;		// Vector con los descriptores de un objeto.
Vec<float,5> media;			// Media de cada parámetro.
Vec<float,5> varianza;			// Varianza de cada parámetro.

#endif
