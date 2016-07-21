#include "NDARData.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

NDARData::NDARData(std::string tsvDirectory)
{
	//get each tsv file and parse the data
	boost::filesystem::path tsvPath(tsvDirectory);
	boost::filesystem::directory_iterator tsvEnd;
	for (boost::filesystem::directory_iterator it(tsvDirectory); it != tsvEnd; ++it)
	{
		if (boost::filesystem::is_regular_file(it->path()) && it->path().extension() == ".tsv")
		{
			ParseTSVFile(it->path().string());
		}
	}
}
void NDARData::ParseTSVFile(std::string fileName)
{
	std::ifstream in(fileName);
	std::string line;
	int counter(0);
	Data data;
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
			for (auto& i : split)
			{
				PopulateTSVVector(split, data);
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
void NDARData::PopulateTSVVector(std::vector<std::string>& splitData, Data& data)
{
	data.timeStamp.push_back(boost::lexical_cast<int>(splitData.at(0)));
	//data.dateTimeStamp.push_back(splitData.at(1));
	//data.dateTimeStampStartOffset.push_back(splitData.at(2));
	//data.number.push_back(boost::lexical_cast<int>(splitData.at(3)));

	//data.leftGaze.emplace_back(boost::lexical_cast<float>(splitData.at(4)), boost::lexical_cast<float>(splitData.at(5)));
	//data.cameraLeft.emplace_back(boost::lexical_cast<float>(splitData.at(6)), boost::lexical_cast<float>(splitData.at(7)));
	//data.leftDistance.push_back(boost::lexical_cast<float>(splitData.at(8)));
	//data.leftPupil.push_back(boost::lexical_cast<float>(splitData.at(9)));
	//data.leftValidity.push_back(boost::lexical_cast<int>(splitData.at(10)));

	//data.rightGaze.emplace_back(boost::lexical_cast<float>(splitData.at(11)), boost::lexical_cast<float>(splitData.at(12)));
	//data.cameraRight.emplace_back(boost::lexical_cast<float>(splitData.at(13)), boost::lexical_cast<float>(splitData.at(14)));
	//data.rightDistance.push_back(boost::lexical_cast<float>(splitData.at(15)));
	//data.rightPupil.push_back(boost::lexical_cast<float>(splitData.at(16)));
	//data.rightValidity.push_back(boost::lexical_cast<int>(splitData.at(17)));

	//data.fixationIndex.push_back(boost::lexical_cast<int>(splitData.at(18)));
	//data.averageGaze.emplace_back(boost::lexical_cast<float>(splitData.at(19)), boost::lexical_cast<float>(splitData.at(20)));
}