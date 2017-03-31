#ifndef SRC_CONTORNOS_HPP_
#define SRC_CONTORNOS_HPP_

#include <opencv2/opencv.hpp>
#include <string>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Métodos para el punto de fuga.
void fugaImagen(string);		// Método para obtener punto de fuga en una imagen.
void fugaReal();		// Método para obtener punto de fuga en tiempo real.
Mat aplicarFiltro(Mat, int, int, double, double);		// Método que aplica un filtro gaussiano.
void mostrarMatriz(Mat, string);		// Método que muestra una matríz por pantalla.
void transformada(Mat imagen, Mat orientacion, Mat modulo);		// Método que calcula la transformada de Hough.

#endif
