#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src, dst,graysrc;
	src = imread("D:/opencvfiles/girl.jpg");
	if (src.empty())
	{
		printf("image load error...");
		return -1;

	}
	namedWindow("input");

	imshow("input", src);

	GaussianBlur(src, dst, Size(3, 3), 0);
	cvtColor(dst, graysrc, COLOR_BGR2GRAY);
	imshow("gray", graysrc);

	Mat xgrad, ygrad;
	Scharr(graysrc, xgrad, -1, 1, 0, 3);
	Scharr(graysrc, ygrad, -1, 1, 0, 3);
	//Sobel(graysrc, xgrad,-1 , 1, 0, 3);//sobel«Ûµº
	//Sobel(graysrc, ygrad,-1 , 0, 1, 3);

	imshow("xgrad", xgrad);
	imshow("ygrad", ygrad);

	Mat xygrad = Mat(xgrad.size(), xgrad.type());
	int width = xgrad.cols;
	int height = xgrad.rows;
	for (int row=0;row<height;row++)
	{
		for (int col = 0; col < width; col++)
		{
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);
			

		}
	}

	//addWeighted(xgrad, 0.5, ygrad, 0.5, 0, xgrad);
	imshow("final", xygrad);

	
	waitKey(0);
	return 0;



}