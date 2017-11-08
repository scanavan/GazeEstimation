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

	// Thickness of the border (1.25% of the screen(image) size)
	float constant_offset = 0.0125;

	if (createBorder)
	{
		cv::copyMakeBorder( image, image, (int) (constant_offset*image.rows), // top
											(int) (constant_offset*image.rows), // bottom
		 									(int) (constant_offset*image.cols), (int) (constant_offset*image.cols), // left and right
											 cv::BORDER_CONSTANT, cv::Scalar(0,0,0) );
	}
	if (addGrids && createBorder)
	{

		// Top left grid line
		cv::line(image,cv::Point((w/3), (0 + constant_offset*image.rows )), cv::Point(w/3,(h + constant_offset*image.rows - 1.5 )), cv::Scalar(255,0,0), (constant_offset*image.rows)/3 ,8, 0);
		// Top right grid line
		cv::line(image,cv::Point(((2*w)/3), (0 + constant_offset*image.rows)), cv::Point(((2*w)/3),(h + constant_offset*image.rows - 1.5)), cv::Scalar(255,0,0), (constant_offset*image.rows)/3,8, 0);
		// Left upper grid line
		cv::line(image,cv::Point( (0 + constant_offset*image.cols)  ,(h/3)), cv::Point((w + constant_offset*image.cols - 1.5),(h/3)), cv::Scalar(255,0,0), (constant_offset*image.rows)/3,8, 0);
		// Left lower grid line
		cv::line(image,cv::Point( (0 + constant_offset*image.cols),((2*h)/3)), cv::Point( (w + constant_offset*image.cols - 1.5) ,((2*h)/3)), cv::Scalar(255,0,0), (constant_offset*image.rows)/3,8, 0);

	}
	 // If no border is desired.
	 else if (addGrids)
	{
		cv::line(image,cv::Point((w/3),0), cv::Point(w/3, h), cv::Scalar(255,0,0), 2,8, 0);
		cv::line(image,cv::Point(((2*w)/3),0), cv::Point(((2*w)/3), h), cv::Scalar(255,0,0), 2,8, 0);
		cv::line(image,cv::Point(0,(h/3)), cv::Point(w,(h/3)), cv::Scalar(255,0,0), 2,8, 0);
		cv::line(image,cv::Point(0,((2*h)/3)), cv::Point(w,((2*h)/3)), cv::Scalar(255,0,0), 2,8, 0);

	}
}

void Image::Display(std::string title, std::string diagnosis)
{
	cv::namedWindow(title);
	for (;;)
	{
		cv::imshow(title, image);
		char key = cv::waitKey(33);
		if (key == 'a')
		{
			cv::destroyWindow(title);
			break;
		}
		// Saves the image
		if(key == 's')
		{
			std::string image_name = "gaze_" + diagnosis + ".jpg";
			std::string path_to_image = "./output/images/" + image_name;
			cv::imwrite(path_to_image, image);
			std::cout << path_to_image << std::endl;
		}
		// There is no current feature to exit out of the caller loop, so we just end the whole program
		if (key == 'e')
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
