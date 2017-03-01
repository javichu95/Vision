
#ifndef TRABAJO1_TRABAJO1_HPP_
#define TRABAJO1_TRABAJO1_HPP_
#include <iostream>
#include <ctype.h>
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
bool primeroRed = true;		// Booleano para indicar que es la primera vez que se entra.
bool primeroCoj = true;		// Booleano para indicar que es la primera vez que se entra.
bool primeroBar = true;		// Booleano para indicar que es la primera vez que se entra.
bool primeroBin = true;		// Booleano para indicar que es la primera vez que se entra
bool primeroSim = true;		// Booleano para indicar que es la primera vez que se entra
int numColores;		// Número de colores para la imagen.
int coeficiente;	// Coeficiente de distorsión de la imagen.
// Matrices para realizar el remap.
Mat coordXCojin, coordYCojin, coordXBarril, coordYBarril,
		coordXInv, coordYInv, coordXRot, coordYRot,
		coordXSimX, coordYSimX, coordXSimY, coordYSimY;
double maxBinaria = 255.0; 	// Valor máximo de una imagen binaria.
double thresVal = 0.0;	// Valor mínimo de una imagen binaria.
string eje;			// Variable para el eje.

int mostrarMenu();		// Función que muestra el menú por pantalla.
Mat ecualizar(Mat);	// Función que mejora el contraste ecualizando el histograma.
Mat mejorarContraste(Mat);	// Función que mejora el contraste.
Mat cambiarColor(Mat, int);		// Método que cambia el color.
Mat reducirColores(Mat);	// Método que reduce el número de colores.
Mat distorsionCojin(Mat);	// Función que aplica distorsión de cojín.
Mat distorsionBarril(Mat);	// Función que aplica la distorsión de barril.
Mat invertir(Mat);		// Función que invierte la imagen.
Mat rotar(Mat);			// Función que rota la imagen 180 grados.
Mat escalaGrises(Mat);		// Función que convierte la imagen a escala de grises.
Mat simetrica(Mat);		// Función que hace la simétrica de la imagen respecto a un eje.
Mat binaria(Mat);		// Función que convierte la imagen a binaria.
void calcularCoordenadas();
void mostrarHistograma(String, Mat);

#endif
