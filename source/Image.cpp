#include "Image.h"
#include <opencv2/opencv.hpp>

Image::Image(int w, int h) :
	  width(w)
	, height(h)
{
	image = cv::Mat::zeros(width, height, CV_8UC3);
}
void Image::Display(std::string title)
{
	cv::namedWindow(title);
	for (;;)
	{
		cv::imshow(title, image);
		if (cv::waitKey(33) == 'a')
		{
			cv::destroyWindow(title);
			break;
		}
	}
}
void Image::PlotPoints(std::vector<Point>points)
{
	for (auto& point : points)
	{
		cv::circle(image, cv::Point(static_cast<int>(point.y), static_cast<int>(point.x)), 1, cv::Scalar(0, 0, 255));
	}
}