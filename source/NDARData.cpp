#include "NDARData.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lambda/bind.hpp>
#include <opencv2/opencv.hpp>

NDARData::NDARData(std::string tsvDirectory)
{
	//get each tsv file and parse the data
	boost::filesystem::path tsvPath(tsvDirectory);
	boost::filesystem::directory_iterator tsvEnd;

	//count tsv files in directory
	float numFiles(0.f);
	for (boost::filesystem::directory_iterator it(tsvDirectory); it != tsvEnd; ++it)
	{
		if (boost::filesystem::is_regular_file(it->path()) && it->path().extension() == ".tsv")
		{
			++numFiles;
		}
	}
	//iterate over directory of tsv files and parse data into class
	float percentDone(0);
	for (boost::filesystem::directory_iterator it(tsvDirectory); it != tsvEnd; ++it)
	{
		if (boost::filesystem::is_regular_file(it->path()) && it->path().extension() == ".tsv")
		{
			std::cout << "Loading TSV data from " << tsvDirectory << " (" << static_cast<int>((percentDone / numFiles) * 100.f) << "%).\r";
			ParseTSVFile(it->path().string());
			++percentDone;
		}
	}
	std::cout << "Loading TSV data from " << tsvDirectory << " (100%)." << std::endl
		      << tsvData.size() << " subjects loaded." << std::endl;
}
void NDARData::DisplayGazeMap(int subject)
{
	cv::namedWindow("Gaze Map");
	cv::Mat gazeMap = cv::Mat::zeros(1280, 1024, CV_8UC3);

	for (auto& gaze : tsvData.at(subject).avgGaze)
	{
		//negative/0 values are bad data
		if (gaze.x > 0 && gaze.y > 0)
		{
			cv::circle(gazeMap, cv::Point(static_cast<int>(gaze.y), static_cast<int>(gaze.x)), 1, cv::Scalar(0, 0, 255));
		}
	}
	for (;;)
	{
		cv::imshow("Gaze Map", gazeMap);
		if (cv::waitKey(33) == 'a')
		{
			break;
		}
	}
}
void NDARData::ParseTSVFile(std::string fileName)
{
	std::ifstream in(fileName);
	std::string line;
	int counter(0);
	SmallData data;
	data.fileName = fileName;

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
	tsvData.push_back(data);
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
	data.leftGaze.emplace_back(boost::lexical_cast<float>(splitData.at(4)), boost::lexical_cast<float>(splitData.at(5)));
	data.rightGaze.emplace_back(boost::lexical_cast<float>(splitData.at(11)), boost::lexical_cast<float>(splitData.at(12)));
	data.avgGaze.emplace_back(boost::lexical_cast<float>(splitData.at(19)), boost::lexical_cast<float>(splitData.at(20)));
}