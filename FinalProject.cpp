#include "pch.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat reference = imread("E:\\van_gogh.jpg");
Mat image = reference.clone();
Mat temp = image.clone();
String selectedTool = "None";
Mat brightness_dst;

int beta = 50;
int alpha = 50;
int const max_beta = 100;
int const max_alpha = 100;

void mouse_callback(int event, int x, int y, int flags, void* param) {

	if (event == 1)
	{
		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == 2)
	{
		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == 3)
	{
		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == 0)
	{
		//cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

	}

}

void BrightnessContrast(int, void*)
{
	float alpha2 = (float)alpha / 50;
	float beta2 = beta - 50;
	Mat element = Mat::zeros(image.size(), image.type());
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < image.channels(); c++) {
				element.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha2*image.at<Vec3b>(y, x)[c] + beta2);
			}
		}
	}
	brightness_dst = element;
	imshow("Ajust Brightness and Contrast", brightness_dst);


}

void brightness_tool() {

	alpha = 50;
	beta = 50;

	String windowName = "Ajust Brightness and Contrast";
	namedWindow(windowName, WINDOW_AUTOSIZE);

	moveWindow("Ajust Brightness and Contrast", image.cols, 0);
	createTrackbar("Brightness :\n ", "Ajust Brightness and Contrast",
		&beta, max_beta,
		BrightnessContrast);
	createTrackbar("contrast :\n ", "Ajust Brightness and Contrast",
		&alpha, max_alpha,
		BrightnessContrast);

	BrightnessContrast(0, 0);

	int k = 0;
	while (k != 27) {

		//2490368 = Haut
		//2424832 = Gauche
		//2621440 = Bas
		//2555904 = Droite

		k = waitKeyEx(20);

		if (k == 27) { //ESC
			break;
		}

		if (k == 115) { //S
			brightness_dst.copyTo(image);
			break;
		}

		
		
	}

	cout << "Back to Menu" << endl;
	destroyWindow(windowName);
	
}

void resize_tool() {

	double addX = 0;
	double addY = 0;

	int k = 0;
	while (k != 27) {

		Mat aff = image.clone();
		String windowName = "Resize Tool";
		namedWindow(windowName);
		imshow(windowName, aff);


		k = waitKeyEx(0);
		
		if (k == 2490368) {
			addY += 0.1;
		}

		if (k == 2621440) {
			addY -= 0.1;
		}

		if (k == 2555904) {
			addX += 0.1;
		}

		if (k == 2424832) {
			addX -= 0.1;
		}

		if (k == 27) { //ESC
			break;
		}

		if (k == 115) { //S
			aff.copyTo(image);
			break;
		}
		destroyWindow(windowName);
		cout << addX << " / " << addY << endl;
		resize(image, aff, aff.size(), 1 + addX, 1 + addY, INTER_LINEAR);
	}

	cout << "Back to Menu" << endl;
	//destroyWindow(windowName);
}

int cropAndResize_students() {

	Mat scaleD, scaleU;

	double scaleX = 0.6;
	double scaleY = 0.6;

	// Scaling down the image 0.6 times
	resize(image, scaleD, scaleD.size(), scaleX, scaleY, INTER_LINEAR);

	// Scaling up the image 1.8 times
	resize(image, scaleU, scaleU.size(), scaleX * 2, scaleY * 2, INTER_LINEAR);

	Mat crop = image;
	Range(crop.rows / 2, crop.cols / 2);

	String windowName = "Original";
	String windowName2 = "x0.6";
	String windowName3 = "x1.8";
	String windowName4 = "Cropped";

	namedWindow(windowName);
	namedWindow(windowName2);
	namedWindow(windowName3);
	namedWindow(windowName4);

	imshow(windowName, image);
	imshow(windowName2, scaleD);
	imshow(windowName3, scaleU);
	imshow(windowName4, crop);

	waitKey(0);

	destroyWindow(windowName);
	destroyWindow(windowName2);
	destroyWindow(windowName3);
	destroyWindow(windowName4);

	return 0;

}

void clear() {

	reference.copyTo(image);
}

int main(int argc, char** argv)
{

	if (reference.empty())
	{
		cout << "Could not open or find the image" << endl;
		system("pause");
		return -1;
	}

	String windowName = "Original";
	namedWindow(windowName, WINDOW_AUTOSIZE);

	setMouseCallback(windowName, mouse_callback, 0);

	int k = 0;

	while (k != 27) {

		imshow(windowName, image);
		//putText(temp, "ESC to exit / c to clear", Point(10, 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 2);
		k = waitKeyEx(20);
		//cout << k << endl;
		if (k == 99) { //C
			cout << "Image cleared" << endl;
			clear();
		}

		if (k == 98) { //B
			cout << "Tool: Brightness selected" << endl;
			brightness_tool();
		}

		if (k == 114) { //R
			cout << "Tool: Resize selected" << endl;
			resize_tool();
		}
	}

	cout << "Finish" << endl;
}