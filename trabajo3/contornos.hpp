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
void transformada(Mat);		// Método que calcula la transformada de Hough.


#endif
