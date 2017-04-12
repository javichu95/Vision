#ifndef SRC_PANORAMA_HPP_
#define SRC_PANORAMA_HPP_

#include <opencv2/opencv.hpp>
#include <string>
#include <dirent.h>

// Espacios de nombres.
using namespace cv;
using namespace std;

// Variables utilizadas.
list<string> ficheros;		// Nombre de todos los ficheros del directorio.

// Métodos para el punto de fuga.
void menu();		// Método que muestra el menú por pantalla.
void leerArchivos(string);		// Método que lee las imágenes de un directorio.

#endif
