#ifndef VISION_RECONOCER_HPP_
#define VISION_RECONOCER_HPP_

#include "imagen.hpp"

// Métodos para reconocimento.
void leerDatos(string objetos);	// Método que lee datos del fichero de objetos.
void reconocer(string fich);	// Reconoce los objetos de la imagen dada.
float mahalanobis(int);			// Método que calcula la distancia de mahalanobis.
void mostrarResultados();		// Método que muestra los resultados por pantalla.

// Variables globales utilizadas.
const string fichObjetos = "objetosEstimado.yml";
Vec<float,5> media;			// Media de cada parámetro.
Vec<float,5> varianza;			// Varianza de cada parámetro.
// Tipos de objetos a reconocer.
vector<string> objetos = {"circulo", "rectangulo", "rueda", "triangulo","vagon"};
// Parámetros o descriptores de cada objeto.
vector<string> parametros = {"area", "perimetro", "invariante1", "invariante2","invariante3"};
FileStorage fs;		// Filestorage para leer los objetos.
float alfa = 0.05;				// Variable para el test chi-cuadrado.
float valChi = 11.0705;			// Valor de la chi-cuadrado para 5 grados de libertad.
vector<string> tipoContorno;		// Vector con las clases que corresponden al contorno.

vector<Vec<float,5>> descriptores;		// Vector con los descriptores de un objeto.
list<int> indicesBlop;		// Vector con los índices del blop.


#endif
