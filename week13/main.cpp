//#include<opencv2/opencv.hpp>
//#include<iostream>
//
//using namespace std;
//using namespace cv;
//
//int main() {
//	cv::Mat refMat;
//	cv::Mat resultMat;
//	cv::Mat frame;
//	cv::Mat tempMat;
//	int cnt = 0;
//
//	VideoCapture cap;
//	cap.open(0);
//	if (!cap.isOpened()) {//打开失败
//		std::cout << "不能打开摄像头" << std::endl;
//		return -1;
//	}
//	
//	while (1) {
//		cap >> frame;
//
//		if (cnt == 0) {
//			Rect2d r;
//			r = selectROI(frame, true);
//			tempMat = frame(r);
//			tempMat.copyTo(refMat);
//			destroyAllWindows();
//		}
//		int match_method = 0;
//		matchTemplate(frame, refMat, resultMat, match_method);
//		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
//		double minVal; double maxVal; Point minLoc; Point maxLoc;
//		Point matchLoc;
//
//		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//
//		cv::rectangle(frame, minLoc, Point(minLoc.x + refMat.cols, minLoc.y + refMat.rows), Scalar(255, 255, 0), 2, 8);
//		cnt++;
//		cv::imshow("result", frame);
//		waitKey(30);
//		}
//	return 0;
//}