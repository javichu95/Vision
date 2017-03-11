#ifndef TRABAJO2_TRABAJO2_HPP_
#define TRABAJO2_TRABAJO2_HPP_
#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>
#include <list>
#include <iostream>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Métodos para el aprendizaje y reconocimiento.
void leerArchivos(string);	// Función que lee los archivos de un directorio.
Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
Mat umbralizarAdaptativo(Mat);	// Método que umbraliza según el método de Adaptativo.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
void obtenerDescriptores(vector<vector<Point>>,int);	// Método que obtiene los descriptores.
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.
void aprendizaje(); // Método que itera sobre diferentes objetos.
//void calcularDatos(); // Método que calcula las medias y varianzas de los parámetros.

// Variables globales utilizadas.
list<string> ficheros;		// Nombre de todos los ficheros del directorio.
// Tipo enumerado para los parámetros.
enum{AREA = 0, PERIMETRO = 1, INV_1 = 2, INV_2 = 3, INV_3 = 4};
// Tipos de objetos a reconocer.
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
// Filestorage para almacenar los objetos.
FileStorage fs ("objetos.yml", FileStorage::WRITE);
double media[5];			// Media de cada parámetro.
double varianza[5];			// Varianza de cada parámetro.

#endif
