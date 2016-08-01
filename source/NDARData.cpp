#include "NDARData.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lambda/bind.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

NDARData::NDARData(std::string tsvDirectory, std::string csvFile)
{
	float percent(1.f);
	ReadCSVFile(tsvDirectory, csvFile);
	for (auto& data : tsvData)
	{
		std::cout << "Populating Gaze Data (" << static_cast<int>((percent / tsvData.size())*100) << "%)\r";
		ParseTSVFile(data);
		++percent;
	}
	//std::cout << "Populating Gaze Data (100%)\r";
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
void NDARData::DisplayGazeMap(int subject, std::string diagnosis)
{
	//can show everything by default, or just diagnosis type
	if (tsvData.at(subject).diagnosis.compare(diagnosis) == 0 || diagnosis.compare("all") == 0)
	{
		//show specifc 
		std::string	title = tsvData.at(subject).GetTitle();
		cv::namedWindow(title);
		cv::Mat gazeMap = cv::Mat::zeros(640, 512, CV_8UC3);
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