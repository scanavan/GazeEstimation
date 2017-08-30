#include "Image.h"
#include "SubjectData.h"
#include <opencv2/opencv.hpp>
#include <iostream>

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
void Image::PlotPoints(std::vector<Point>points, SubjectData &s)
{
	for (auto& point : points)
	{
		cv::circle(image, cv::Point(static_cast<int>(point.y)/3, static_cast<int>(point.x)/3), 1, cv::Scalar(0, 0, 255));
	}
	//save image w/ the classification
	size_t lastIndex = s.fileName.find_last_of(".");
	std::string new_name = s.fileName.substr(0, lastIndex);
	if(s.diagnosis == "low") {
		cv::imwrite("./GazeData/EyeGazeLow/" + new_name + ".jpg" , image);
	} else if(s.diagnosis == "medium") {
		cv::imwrite("./GazeData/EyeGazeMedium/" + new_name + ".jpg", image);
	} else if(s.diagnosis == "high") {
		cv::imwrite("./GazeData/EyeGazeHigh/" + new_name + ".jpg", image);
	} else if(s.diagnosis == "ASD") {
		cv::imwrite("./GazeData/EyeGazeASD/" + new_name + ".jpg", image);
	}
}