
#ifndef TRABAJO1_TRABAJO1_HPP_
#define TRABAJO1_TRABAJO1_HPP_
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

// Espacios de nombres.
using namespace cv;
using namespace std;

VideoCapture TheVideoCapturer;		// Objeto para la cámara.
Mat bgrMap;		// Matriz de lo obtenido de la cámara.
bool primero = true;		// Booleano para indicar que es la primera vez que se entra.
int numColores;		// Número de colores para la imagen.

int mostrarMenu();		// Función que muestra el menú por pantalla.
Mat mejorarContraste(Mat);	// Función que mejora el contraste.
Mat cambiarColor(Mat, int);		// Método que cambia el color.
Mat reducirColores(Mat);	// Método que reduce el número de colores.

#endif
