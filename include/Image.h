#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/opencv.hpp>
#include <string>
#include "Vector2D.h"
#include "SubjectData.h"

class Image
{
public:
	Image(int w, int h);
	void Display(std::string title="Image");
	void PlotVector2Ds(std::vector<Vector2D>vectors, SubjectData &subject);

private:
	cv::Mat image;
	int width;
	int height;
};
#endif