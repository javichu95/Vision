#ifndef SRC_CONTORNOS_HPP_
#define SRC_CONTORNOS_HPP_

#include <opencv2/opencv.hpp>
#include <string>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Variables utilizadas.
float umbralSobel = 60.0;			// Valor umbral para sobel.
float umbralScharr = 140.0;			// Valor umbral para scharr.
float umbral = umbralSobel;
int numPixeles = 5;		// Valor para la votación de píxeles.

// Métodos para el punto de fuga.
Mat leerImagen(string);		// Método que lee la imagen.
void fugaImagen(Mat);		// Método para obtener punto de fuga en una imagen.
Mat aplicarFiltro(Mat, int, int, double, double);		// Método que aplica un filtro gaussiano.
void mostrarMatriz(Mat, string);		// Método que muestra una matríz por pantalla.
void mostrarPuntos(Mat, Mat);		// Muestra los puntos según el umbral.
// Método que calcula la transformada de Hough.
int transformada(Mat imagen, Mat orientacion, Mat modulo);
void votar(int [], int, int, int, int, float, Mat);		// Método que vota a una cierta recta.
void dibujarX(int, int, Mat);	// Método que dibuja una X en el punto de fuga.
void fugaReal();		// Método para obtener punto de fuga en tiempo real.
void votarPuntos(vector<vector<int>>&, float , float, Mat);		// Método que vota los puntos de las rectas.
void reInicializarVotacion(vector<vector<int>>&, Mat);	// Método que reinicializa la votación de los puntos.

#endif
