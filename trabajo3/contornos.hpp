#ifndef SRC_CONTORNOS_HPP_
#define SRC_CONTORNOS_HPP_

#include <opencv2/opencv.hpp>
#include <string>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Variables utilizadas.
float umbral = 70.0;			// Valor umbral.

// Métodos para el punto de fuga.
Mat leerImagen(string);		// Método que lee la imagen.
void fugaImagen(Mat);		// Método para obtener punto de fuga en una imagen.
Mat aplicarFiltro(Mat, int, int, double, double);		// Método que aplica un filtro gaussiano.
void mostrarMatriz(Mat, string);		// Método que muestra una matríz por pantalla.
void mostrarPuntos(Mat, Mat);		// Muestra los puntos según el umbral.
// Método que calcula la transformada de Hough.
int transformada(Mat imagen, Mat orientacion, Mat modulo);
void votar(int [], int, int, int, int, float, Mat);		// Método que vota a una cierta recta.
float distEjes(float);		// Método que calcula la distancia al eje más cercano.
void fugaReal();		// Método para obtener punto de fuga en tiempo real.

#endif
