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
void mostrarResultados();		// Método que muestra los resultados por pantalla.
Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
void dibujarBlops(int,Mat,string);			// Método que dibuja los blops.
void obtenerDescriptores(vector<vector<Point>>);	// Método que obtiene los descriptores.
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.

// Variables globales utilizadas.
const string fichObjetos = "objetos.yml";
Vec<float,5> media;			// Media de cada parámetro.
Vec<float,5> varianza;			// Varianza de cada parámetro.
const int numParametros = 5;		// Número de parámetros o momentos.
// Tipos de objetos a reconocer.
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
// Parámetros o descriptores de cada objeto.
vector<string> parametros = {"area", "perimetro", "invariante1", "invariante2","invariante3"};
vector<Vec<float,5>> descriptores;		// Vector con los descriptores de un objeto.
FileStorage fs;		// Filestorage para leer los objetos.
float alfa = 0.05;				// Variable para el test chi-cuadrado.
float valChi = 11.0705;			// Valor de la chi-cuadrado para 5 grados de libertad.
vector<string> tipoContorno;		// Vector con las clases que corresponden al contorno.
list<int> indicesBlop;		// Vector con los índices del blop.

#endif
