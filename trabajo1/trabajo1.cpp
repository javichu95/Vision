#include "trabajo1.hpp"


int main(int argc, char *argv[]) {
	int captura = capturarImagen();

	if(captura == 0) {
		Mat img = cv::imread(snapshotFilename + ".png", CV_LOAD_IMAGE_COLOR);
		namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
		imshow("MyWindow", img);
		char key = 0;
		cout << "Pulsa 'c' para aplicar contraste a la imagen." << endl;
		cout << "Pulsa 'r' para cambiar el color a rojo." << endl;
		cout << "Pulsa 'a' para cambiar el color a azul." << endl;
		cout << "Pulsa 'v' para cambiar el color a verde." << endl;
		cout << "Pulsa la flecha inferior para reducir el número de colores." << endl;
		cout << "Pulsa 'b' para aplicar distorsion de barril." << endl;
		cout << "Pulsa 'd' para aplicar distorsion de cojin." << endl;
		cout << "Pulsa 'esc' para terminar." << endl;
		while(key != 27) {

			key = waitKey(30);
		}
	}
}


	/*
	 * Captura una imagen con la camara.
	 */
  int capturarImagen() {

	  string snapshotFilename = "imagen";

	  TheVideoCapturer.open(0);

	  if (!TheVideoCapturer.isOpened()) {
	    cerr<<"Could not open video"<<std::endl;
	    return -1;
	  }
	    TheVideoCapturer.retrieve(bgrMap);
	    imwrite(snapshotFilename + ".png", bgrMap);
	    return 0;

  }
