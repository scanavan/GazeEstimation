#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/opencv.hpp>
#include <string>
#include "Point.h"

class Image
{
public:
	Image(int w, int h);
	void Display(std::string title="Image");
	void PlotPoints(std::vector<Point>points);

private:
	cv::Mat image;
	int width;
	int height;
};
#endif