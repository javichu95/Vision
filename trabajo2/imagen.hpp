#ifndef VISION_IMAGEN_HPP_
#define VISION_IMAGEN_HPP_

#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>
#include <list>
#include <iostream>

// Espacios de nombres.
using namespace cv;
using namespace std;


Mat umbralizarOtsu(Mat);		// Método que umbraliza según el método Otsu.
vector<vector<Point>> obtenerBlops(Mat);		// Método que obtiene los blops.
// Método que obtiene los descriptores.
void obtenerDescriptores(vector<vector<Point>>,vector<Vec<float,5>>&,list<int>&);
void mostrarHistograma(string,Mat);	// Método que muestra el histograma por pantalla.
void dibujarBlops(int,Mat,string);			// Método que dibuja los blops.


const int numParametros = 5;		// Número de parámetros o momentos.


#endif /* IMAGEN_HPP_ */
