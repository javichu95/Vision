
#ifndef TRABAJO1_TRABAJO1_HPP_
#define TRABAJO1_TRABAJO1_HPP_
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

VideoCapture TheVideoCapturer;
Mat bgrMap;
string snapshotFilename = "imagen";

int mostrarMenu();		// Función que muestra el menú por pantalla.
Mat mejorarContraste(Mat);	// Función que mejora el contraste.
Mat cambiarColor(Mat, int);		// Método que cambia el color.
int reducirColores();	// Método que reduce el número de colores.

#endif
