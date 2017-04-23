#ifndef SRC_PANORAMA_HPP_
#define SRC_PANORAMA_HPP_

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d.hpp>
#include <string>
#include <dirent.h>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Variables utilizadas.
list<Mat> ficheros;		// Nombre de todos los ficheros del directorio.
int camara = 0;		// Variable para seleccionar la cámara.
int totalFotos = 5;		// Número total de fotos a capturar de forma automática.
int tiempo = 10000;		// Tiempo para sacar las fotos de forma automática.
Mat panorama;			// Matriz con el panorama completo.

// Métodos para crear el panorama.
void menu();					// Método que muestra el menú por pantalla.
int leerArchivos(string);		// Método que lee las imágenes de un directorio.
void capturarDirectorio();		// Método que crea el panorama con las imágenes del directorio.
void capturarTeclado();			// Método para capturar imágenes por el teclado.
void capturarAutomatica();		// Método que captura imágenes de manera automática.
void construirPanorama(Mat);	// Método que construye el panorama con la nueva imagen.

#endif
