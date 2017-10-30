#include "Image.h"
#include "SubjectData.h"
#include <opencv2/opencv.hpp>
#include <iostream>

Image::Image(int w, int h, bool createBorder) :
	  width(w)
	, height(h)
{
	image = cv::Mat::zeros(width, height, CV_8UC3);
	image.setTo(cv::Scalar(255, 255, 255));
	if (createBorder)
	{
		for (int i = 0; i < image.rows; ++i)
		{
			for (int j = 0; j < image.cols; ++j)
			{
				if (i == 0 || i == image.rows - 1 || j == 0 || j == image.cols-1)
				{
					image.at<cv::Vec3b>(i, j)[0] = 0;
					image.at<cv::Vec3b>(i, j)[1] = 0;
					image.at<cv::Vec3b>(i, j)[2] = 0;
				}
			}
		}
	}
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
void Image::PlotVector2Ds(std::vector<Vector2D>vectors, SubjectData &subject)
{
	for (auto& Vector2D : vectors)
	{
		cv::circle(image, cv::Point(static_cast<int>(Vector2D.y)/3, static_cast<int>(Vector2D.x)/3), 1, cv::Scalar(0, 0, 0));
	}
	//save image w/ the classification
	size_t lastIndex = subject.fileName.find_last_of(".");
	std::string new_name = subject.fileName.substr(0, lastIndex);
	if(subject.diagnosis == "low") {
		cv::imwrite("./GazeData/EyeGazeLow/" + new_name + ".jpg" , image);
	} else if(subject.diagnosis == "medium") {
		cv::imwrite("./GazeData/EyeGazeMedium/" + new_name + ".jpg", image);
	} else if(subject.diagnosis == "high") {
		cv::imwrite("./GazeData/EyeGazeHigh/" + new_name + ".jpg", image);
	} else if(subject.diagnosis == "ASD") {
		cv::imwrite("./GazeData/EyeGazeASD/" + new_name + ".jpg", image);
	}
}
