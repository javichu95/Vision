#ifndef SRC_APRENDER_RECONOCER_HPP_
#define SRC_APRENDER_RECONOCER_HPP_

#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>
#include <list>
#include <iostream>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Métodos para reconocimento.
void leerDatos(string objetos);	// Método que lee datos del fichero de objetos.
void reconocer(string fich);	// Reconoce los objetos de la imagen dada.
float mahalanobis(int);			// Método que calcula la distancia de mahalanobis.
Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
Mat umbralizarAdaptativo(Mat);	// Método que umbraliza según el método de Adaptativo.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
void obtenerDescriptores(vector<vector<Point>>,string);	// Método que obtiene los descriptores.
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.

// Variables globales utilizadas.
const string fichObjetos = "objetos.yml";
Vec<float,5> media;			// Media de cada parámetro.
Vec<float,5> varianza;			// Varianza de cada parámetro.
const int numParametros = 5;		// Númeto de parámetros o momentos.
// Tipos de objetos a reconocer.
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
// Parámetros o descriptores de cada objeto.
vector<string> parametros = {"area", "perimetro", "invariante1", "invariante2","invariante3"};
vector<Vec<float,5>> descriptores;		// Vector con los descriptores de un objeto.
FileStorage fs;		// Filestorage para almacenar los objetos.
float alfa = 0.05;				// Variable para el test chi-cuadrado.

#endif
