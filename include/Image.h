#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/opencv.hpp>
#include <string>
#include "Vector2D.h"
#include "SubjectData.h"

class Image
{
public:
	Image(int w, int h, bool createBorder = true, bool addGrids = true);
	
	void Display(std::string title="Image", std::string diagnosis="ASD");
	void PlotVector2Ds(std::vector<Vector2D>vectors, SubjectData &subject);

private:
	cv::Mat image;
	int width;
	int height;
};
#endif
