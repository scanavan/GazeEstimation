#include "Image.h"
#include "SubjectData.h"
#include <opencv2/opencv.hpp>
#include <iostream>

Image::Image(int w, int h, bool createBorder, bool addGrids) :
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
	if (addGrids)
	{

		cv::line(image,cv::Point((w/3),0), cv::Point(w/3, h), cv::Scalar(255,0,0), 2,8, 0);
		cv::line(image,cv::Point(((2*w)/3),0), cv::Point(((2*w)/3), h), cv::Scalar(255,0,0), 2,8, 0);
		cv::line(image,cv::Point(0,(h/3)), cv::Point(w,(h/3)), cv::Scalar(255,0,0), 2,8, 0);
		cv::line(image,cv::Point(0,((2*h)/3)), cv::Point(w,((2*h)/3)), cv::Scalar(255,0,0), 2,8, 0);
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
		if (cv::waitKey(33) == 'e')
		{
			cv::destroyWindow(title);
			exit(EXIT_SUCCESS);
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
