#include "trabajo2.hpp"

vector<vector<float>> descriptores;		// Descriptores del objeto.

void obtenerDescriptoresReconocer(vector<vector<Point>> contornos);

/*
 * Método que obtiene los descriptores de la imagen.
 */
void obtenerDescriptoresReconocer(vector<vector<Point>> contornos){

	vector<Moments> mu(contornos.size());	// Vector para los momentos.
	double inv[7];		// Array para guardar los momentos invariantes.
	vector<float> momentos;		// Momentos del objeto.

	// Se calculan los momentos para cada objeto.
	for(uint i = 0; i < contornos.size(); i++){
		mu[i] = moments(contornos[i], false);
	}

	// Se aplica filtro de área.
	for(int i = 0; i < contornos.size(); i++){
		// Se comprueba si es el contorno válido.
		if(contornos.size() == 1 || (contornos.size() > 1 && mu[i].m00 > 500)){
			momentos.push_back(mu[i].m00);	// Se obtiene el área.
			// Se calcula el perímetro.
			momentos.push_back(arcLength(contornos[i],true));

			// Se obtienen los momentos invariantes.
			HuMoments(mu[i],inv);
			momentos.push_back(inv[0]);
			momentos.push_back(inv[1]);
			momentos.push_back(inv[2]);
			descriptores.push_back(momentos);
		}

	}
}

int main(int argc, char *argv[]) {
	if(argc < 1) {
		trabajo2();
		return 1;
	}
	Mat imagen = imread(argv[0], CV_LOAD_IMAGE_GRAYSCALE);
	Mat imagen1 = umbralizarOtsu(imagen);		// Umbralizamos la imagen.
	vector<vector<Point>> contornos = obtenerBlops(imagen1);			// Obtenemos los blops.
	obtenerDescriptoresReconocer(contornos);
	calcularDatos();
}

