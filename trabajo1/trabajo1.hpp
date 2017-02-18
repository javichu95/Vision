/*
 * trabajo1.hpp
 *
 *  Created on: 18 feb. 2017
 *      Author: Jorge
 */

#ifndef TRABAJO1_TRABAJO1_HPP_
#define TRABAJO1_TRABAJO1_HPP_
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

cv::VideoCapture TheVideoCapturer;
cv::Mat bgrMap;
std::string snapshotFilename = "imagen";

int capturarImagen();


#endif /* TRABAJO1_TRABAJO1_HPP_ */
