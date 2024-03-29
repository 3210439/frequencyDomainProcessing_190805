#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void displayDFT(Mat& src)
{
	Mat image_array[2] = { Mat::zeros(src.size(), CV_32F),
								Mat::zeros(src.size(), CV_32F) };
	// 1. DFT 결과 영상을 2개의 영상으로 분리한다.
	split(src, image_array);

	Mat mag_image;
	// 2. 푸리에 변환 계수들의 절대값을 계산한다. 
	magnitude(image_array[0], image_array[1], mag_image);

	// 3. 푸리에 변환 계수들은 상당히 크기 때문에 로그 스케일로 변환한다. 
	// 0값이 나오지 않도록 1을 더해준다. 
	mag_image += Scalar::all(1);
	log(mag_image, mag_image);

	// 4. 0에서 255로 범위로 정규화한다.
	normalize(mag_image, mag_image, 0, 1, NORM_MINMAX);
	imshow("DFT", mag_image);
}

int main()
{
	Mat src = imread("./lenna.jpg", IMREAD_GRAYSCALE);
	Mat src_float;

	// 그레이스케일 영상을 실수 영상으로 변환한다. 
	src.convertTo(src_float, CV_32FC1, 1.0 / 255.0);
	Mat dft_image;
	dft(src_float, dft_image, DFT_COMPLEX_OUTPUT);
	displayDFT(dft_image);
	waitKey(0);
	return 1;
}