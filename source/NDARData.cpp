#include "NDARData.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lambda/bind.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

NDARData::NDARData(std::string tsvDirectory, std::string csvFile)
{
	//read csv file with age, gender, diagnosis, and tsv file name
	ReadCSVFile(tsvDirectory, csvFile);
	//parse tsv file based on input from csv file
	float percent(1.f);
	for (auto& data : tsvData)
	{
		std::cout << "Populating Gaze Data (" << static_cast<int>((percent / tsvData.size())*100) << "%)\r";
		ParseTSVFile(data);
		++percent;
	}
}
void NDARData::ReadCSVFile(std::string dir, std::string csvFile)
{
	std::string line;
	int lineCounter(0);
	std::ifstream in;
	in.open(csvFile);
	while (!in.eof() || in.peek() != EOF)
	{
		in >> std::ws;
		if (in.eof() || in.peek() == EOF)
		{
			break;
		}
		std::getline(in, line);
		if (lineCounter != 0)
		{
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(","));
			SmallData data;
			data.age = boost::lexical_cast<int>(split.at(0));
			data.gender = split.at(1);
			data.diagnosis = split.at(2);
			data.fileNameWithPath = dir+split.at(3);
			data.fileName = split.at(3);
			tsvData.push_back(data);
		}
		else
		{
			//don't get header row in file
			++lineCounter;
		}
	}
	in.close();
}
void NDARData::GetNewCentroids(Point& c1, Point& c2, Point& c3, Point& c4, std::vector<std::vector<Point>>&clusters)
{
	int c(0);
	for (auto& cluster : clusters)
	{
		Point avg(0, 0);
		for (auto& point : cluster)
		{
			avg += point;
		}
		avg /= cluster.size();
		if (c == 0)
		{
			c1 = avg;
		}
		else if (c == 1)
		{
			c2 = avg;
		}
		else if (c == 2)
		{
			c3 = avg;
		}
		else
		{
			c4 = avg;
		}
		++c;
	}
}
void NDARData::ClusterGazeData(int subject)
{
	int k(10);
	Point centroid1(0, 0);
	Point centroid2(1280, 0);
	Point centroid3(0, 1024);
	Point centroid4(1280, 1024);

	std::vector<std::vector<Point>>temp(4);
	for (int i = 0; i < k; ++i)
	{
		if (i != 0)
		{
			GetNewCentroids(centroid1, centroid2, centroid3, centroid4, temp);
			for (size_t j = 0; j < temp.size(); ++j)
			{
				temp.at(j).clear();
			}
		}
		for (auto& data : tsvData.at(subject).avgGaze)
		{
			//get distances to centroids
			float d1 = data.Distance(centroid1);
			float d2 = data.Distance(centroid2);
			float d3 = data.Distance(centroid3);
			float d4 = data.Distance(centroid4);

			int minIndex = 0;
			float min = d1;
			if (d2 < min)
			{
				minIndex = 1;
				min = d2;
			}
			if (d3 < min)
			{
				minIndex = 2;
				min = d3;
			}
			if (d4 < min)
			{
				minIndex = 3;
			}
			temp.at(minIndex).push_back(data);
		}
	}
	tsvData.at(subject).clusters = temp;
}
float NDARData::Distance(Point p1, Point p2)
{
	return std::sqrt(std::pow((p1.x - p2.x), 2.f) + std::pow((p1.y - p2.y), 2.f));
}
void NDARData::GetAvgDistanceFromCentroid(int subject)
{
	//get centroid
	Point centroid;
	for (auto& point : tsvData.at(subject).avgGaze)
	{
		centroid += point;
	}
	centroid /= tsvData.at(subject).avgGaze.size();

	float avg(0.f);
	for (auto& point : tsvData.at(subject).avgGaze)
	{
		avg += point.Distance(centroid);
	}
	avg /= tsvData.at(subject).avgGaze.size();
	tsvData.at(subject).avgDistanceFromCentroid = avg;
}
bool NDARData::EyeMissing(std::vector<std::string>& data)
{
	//there are some rows in the file that don't have data. 
	if (data.at(4).empty() || data.at(5).empty() || data.at(11).empty() || data.at(12).empty())
	{
		return true;
	}
	return false;
}
void NDARData::PopulateTSVVectorWithSmallData(std::vector<std::string>& splitData, SmallData& data)
{
	data.avgGaze.emplace_back(boost::lexical_cast<float>(splitData.at(19)), boost::lexical_cast<float>(splitData.at(20)));
}
void NDARData::ParseTSVFile(SmallData& data)
{
	std::ifstream in(data.fileNameWithPath);
	std::string line;
	int counter(0);
	//file contents
	while (!in.eof() || in.peek() != EOF)
	{
		in >> std::ws;
		if (in.eof() || in.peek() == EOF)
		{
			break;
		}
		std::getline(in, line);
		if (counter == 1)
		{
			//once we have the real data split the line based on tabs and save the data
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of("\t"));
			if (split.size() == 43)
			{
				if (!EyeMissing(split))
				{
					PopulateTSVVectorWithSmallData(split, data);
				}
			}
		}
		//this is the "header" line, the next line is the real data
		if (line.find("TimeStamp") != std::string::npos)
		{
			++counter;
		}
	}
	in.close();
}
void NDARData::DisplayClusterData(int subject, std::string title)
{
	title = tsvData.at(subject).GetTitle();
	cv::namedWindow(title);
	cv::Mat gazeMap = cv::Mat::zeros(tsvData.at(subject).width, tsvData.at(subject).height, CV_8UC3);
	int colorCount(0);
	cv::Scalar color(0, 0, 255);
	for (auto& clusters : tsvData.at(subject).clusters)
	{
		if (colorCount == 1)
		{
			color = cv::Scalar(0, 255, 0); 
		}
		else if (colorCount == 2)
		{
			color = cv::Scalar(255, 0, 0); 
		}
		else if(colorCount == 3)
		{
			color = cv::Scalar(255, 255, 0);
		}

		for (auto& point : clusters)
		{
			cv::circle(gazeMap, cv::Point(static_cast<int>(point.y / 2), static_cast<int>(point.x / 2)), 1, color);
		}
		++colorCount;
	}
	for (;;)
	{
		cv::imshow(title, gazeMap);
		if (cv::waitKey(33) == 'a')
		{
			cv::destroyWindow(title);
			break;
		}
	}
}
void NDARData::DisplayGazeMap(int subject, std::string diagnosis)
{
	//can show everything by default, or just diagnosis type
	if (tsvData.at(subject).diagnosis.compare(diagnosis) == 0 || diagnosis.compare("all") == 0)
	{
		//show specifc 
		std::string	title = tsvData.at(subject).GetTitle();
		cv::namedWindow(title);
		cv::Mat gazeMap = cv::Mat::zeros(tsvData.at(subject).width, tsvData.at(subject).height, CV_8UC3);
		for (auto& gaze : tsvData.at(subject).avgGaze)
		{
			cv::circle(gazeMap, cv::Point(static_cast<int>(gaze.y / 2), static_cast<int>(gaze.x / 2)), 1, cv::Scalar(0, 0, 255));
		}
		for (;;)
		{
			cv::imshow(title, gazeMap);
			if (cv::waitKey(33) == 'a')
			{
				cv::destroyWindow(title);
				break;
			}
		}
	}
}