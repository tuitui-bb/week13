#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

float norml2(float* a, float* b, int n) {
	float dis = 0;
	for (int i = 0; i < n; i++) {
		dis = (a[i] - b[i]) * (a[i] - b[i]);
	}
	return sqrt(dis);
}


int calcHog(Mat src, float* hist, int nAngle, int cellSize) {
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);
	Rect roi;
	roi.height = cellSize;
	roi.width = cellSize;
	int nX = src.cols / cellSize;
	int nY = src.rows / cellSize;
	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			Mat roiMat, roiMag, roiAgl;
			roi.x = j * cellSize;
			roi.y = i * cellSize;
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			int head = (i * nX + j) * nAngle;
			for (int n = 0; n < roiMat.rows; n++) {
				for (int m = 0; m < roiMat.cols; m++) {
					hist[head + (int)roiAgl.at<float>(n, m) / (360 / nAngle)] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}

int main() {
	int cellSize = 16;
	int nAngle = 8;
	Mat src = imread("D:\\18.jpg");
	Mat cell = imread("D:\\19.jpg");
	Mat comp;
	Rect dstRect;
	float distanceMin = 0;

	

	while (1) {
		int nX = cell.cols / cellSize;
		int nY = cell.rows / cellSize;
		int bins = nX * nY * nAngle;
		float* cell_hist = new float[bins];
		memset(cell_hist, 0, sizeof(float) * bins);
		calcHog(cell, cell_hist, nAngle, cellSize);

		
		for (int j = 0; j < src.rows - cell.rows; j++)
		{
			for (int i = 0; i < src.cols - cell.cols; i++)
			{
				Rect rect(i, j, cell.cols, cell.rows);
				comp = src(rect);
				
				float* compare_hist = new float[bins];
				memset(compare_hist, 0, sizeof(float) * bins);

				calcHog(comp, compare_hist, nAngle, cellSize);
				float distance = 0;
				distance = norml2(cell_hist, compare_hist, bins);

				if (j == 0) {
					distanceMin = distance;
				}
				else if (distance < distanceMin) {
					distanceMin = distance;
					dstRect = rect;
				}

				delete[] compare_hist;
				
			}
		}
		delete[] cell_hist;
		rectangle(src, dstRect, Scalar(0, 0, 255));
		cv::imshow("cell", cell);
		cv::imshow("src", src);
		waitKey(0);
	}
	return 0;
}

