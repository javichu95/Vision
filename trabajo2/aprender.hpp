#ifndef VISION_APRENDER_HPP_
#define VISION_APRENDER_HPP_

#include "imagen.hpp"

// Métodos para el aprendizaje.
void leerArchivos(string);	// Función que lee los archivos de un directorio.
void aprendizaje(string objeto); // Método que itera sobre diferentes objetos.
void calcularDatos(int);		// Método que calcula las medias y varianzas.
void escribirDatos(string,int); 		// Escribe los datos en el fichero.

// Variables globales utilizadas.
list<string> ficheros;		// Nombre de todos los ficheros del directorio.
const string fichObjetos = "objetos.yml";			// Variable con el nombre del fichero de objetos.
const string fichObjetosEst = "objetosEstimado.yml";			// Variable con el nombre del fichero de objetos con varianza estimada.
// Tipo enumerado para los parámetros.
enum{AREA = 0, PERIMETRO = 1, INV_1 = 2, INV_2 = 3, INV_3 = 4};
// Parámetros o descriptores de cada objeto.
vector<string> parametros = {"area", "perimetro", "invariante1", "invariante2","invariante3"};
// Tipos de objetos a reconocer.
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
FileStorage fs;		// Filestorage para almacenar los objetos.
FileStorage fsEstimada;		// Filestorage para almacenar los objetos con varianza estimada.
Vec<float,5> media;			// Media de cada parámetro.
Vec<float,5> varianza;			// Varianza de cada parámetro.
Vec<float,5> varianzaEstimada;			// Varianza estimada de cada parámetro.
vector<Vec<float,5>> descriptores;		// Vector con los descriptores de un objeto.
list<int> indicesBlop;					// Vector con los índices del blop.
double porcentaje = 0.03;				// Porcentaje con el que estimar la varianza.

#endif
