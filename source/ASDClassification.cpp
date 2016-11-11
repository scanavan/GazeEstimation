#include "ASDClassification.h"
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lambda/bind.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "Image.h"
#include "boost/date_time/posix_time/posix_time.hpp"
using namespace boost::posix_time;
using namespace boost::gregorian;

ASDClassification::ASDClassification()
{

}
size_t ASDClassification::GetNumberOfSubjects()
{
	return data.size();
}
void ASDClassification::CreateDisplayImageOfGaze(size_t subject)
{
	Image image(1280, 1024);
	image.PlotPoints(data.at(subject).avgGaze, data.at(subject));
	image.Display(data.at(subject).GetTitle());
}
void ASDClassification::ParseTSVFiles(std::string tsvDir)
{
	float percent(1.f);
	for (auto& d : data)
	{
		d.fileNameWithPath = tsvDir + d.fileName;
		std::cout << "Parsing TSV Files (" << static_cast<int>((percent / data.size()) * 100) << "%)\r";
		ParseTSVFile(d);
		++percent;
	}
	std::cout << std::endl;
}
void ASDClassification::ParseTSVFile(SubjectData& data)
{
	std::ifstream in2(data.fileNameWithPath);
	std::string line;
	int counter(0);
	//file contents

int numLines = 0;

	while (!in2.eof() || in2.peek() != EOF)
	{
		in2 >> std::ws;
		if (in2.eof() || in2.peek() == EOF)
		{
			break;
		}
		std::getline(in2, line);
		numLines ++;
	}
in2.close();
std::ifstream in(data.fileNameWithPath);
int counter2 = 0;

int fixCounter = 0;
int tempFixationIndex = 0;
std::string time1;
std::string time2;

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
					data.avgGaze.emplace_back(boost::lexical_cast<int>(split.at(19)), boost::lexical_cast<int>(split.at(20)));
					data.GazePointXR = boost::lexical_cast<float>(split.at(11));
					data.GazePointYR = boost::lexical_cast<float>(split.at(12));
					data.GazePointXL = boost::lexical_cast<float>(split.at(4));
					data.GazePointYL = boost::lexical_cast<float>(split.at(5));


					if(!split.at(18).empty()) //make sure we actually have data
					{
						data.fixationIndex = boost::lexical_cast<int>(split.at(18));
						if(fixCounter == 0) //gets initial data
						{
						time1 = split.at(2); //get time, need to convert time string into something we can add
						time2 = time1;
						tempFixationIndex = boost::lexical_cast<int>(split.at(18));
						fixCounter ++; //dont want if statement to repeat
						}
						else 
						{
						if(boost::lexical_cast<int>(split.at(18)) == tempFixationIndex)
						{
						time1 = split.at(2); //need to figure out how to do this
						int hours1 = boost::lexical_cast<int>(time1.at(0)+time1.at(1));
						int minutes1 = boost::lexical_cast<int>(time1.at(3)+time1.at(4));
						int seconds1 = boost::lexical_cast<int>(time1.at(6));

						int hours2 = boost::lexical_cast<int>(time2.at(0)+time2.at(1));
						int minutes2 = boost::lexical_cast<int>(time2.at(3)+time2.at(4));
						int seconds2 = boost::lexical_cast<int>(time2.at(6));

						date d(2002, Feb, 1);
						ptime t1(d, hours(hours1)+minutes(minutes1)+seconds(seconds1)+millisec(0));
						ptime t2(d, hours(hours2)+minutes(minutes2)+seconds(seconds2)+millisec(0));
						time_duration td = t2 - t1;
						data.saveTime += td.seconds(); 
						}
						else // we are at next fixation
						{
						data.timeVector.push_back(data.saveTime); // save accumulated time in a vector
						data.saveTime = 0;
						time1 = split.at(2);
						tempFixationIndex = boost::lexical_cast<int>(split.at(18));
						}
					}
				}
			}
		}
		counter2 ++;
		if (counter2 == numLines)
		{
			data.DateTime = split.at(2);
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
void ASDClassification::WriteArffGazePoints(std::ostream& out, int size)
{
	float sdX(0);
	float sdY(0);
	float meanX(0);
	float meanY(0);
	int count(0);
	for (auto& subject : data)
	{
		//if (subject.type == 3)
		{
			int gender = 1;
			if (subject.gender.compare("M") == 0)
			{
				gender = 0;
			}
			out << gender << "," << std::to_string(subject.age) << ",";
			for (int i = 0; i < 100000; ++i)
			{
				out << std::to_string(subject.avgGaze.at(i).x) << "," << std::to_string(subject.avgGaze.at(i).y) << ",";
				meanX += subject.avgGaze.at(i).x;
				meanY += subject.avgGaze.at(i).y;
				sdX += (subject.avgGaze.at(i).x * subject.avgGaze.at(i).x);
				sdY += (subject.avgGaze.at(i).y * subject.avgGaze.at(i).y);
			}
			//add mean feature here
			meanX = meanX/size;
			meanY = meanY/size;
			sdX = sdX - (size*(meanX*meanX));
			sdX = sdX/(size-1);
			sdY = sdY - (size*(meanY*meanY));
			sdY = sdY/(size-1);
			out << meanX << "," << meanY << ",";
			out << sdX << "," << sdY << ",";
			out << subject.diagnosis << std::endl;
		}
		++count;
	}
	std::cout << count << std::endl;
}
void ASDClassification::WriteArffFile(std::string file, std::string file2)
{
	std::ofstream out;
	std::ofstream out2;
	out2.open(file2);
	out.open(file);
	out << "% 1. Title: ASD Classification\n"
		<< "%\n"
		<< "% 2. Sources :\n"
		<< "% (a)Creator : NIH and Binghamton SRI 2016\n"
		<< "% (b)Date : Fall 2016\n"
		<< "%\n"
		<< "@RELATION asd\n"
		<< "\n"
		<< "@ATTRIBUTE gender NUMERIC\n"
		<< "@ATTRIBUTE age NUMERIC\n";
		//going to add a new feature here at the end

	//out2 << "Here is a test to see if anything is being written to file " << std::endl;
	int size(100000);
	for (auto& subject : data)
	{
		out2 << subject.fileName << " " << subject.age << std::endl;
		if (subject.avgGaze.size() < size)
		{
			size = static_cast<int>(subject.avgGaze.size());
			//out2 << subject.fileName << std::endl;
		}
	}
std::cout<<size<<std::endl;

	for (int i = 0; i < 100000; ++i)
	{
		std::string gazeX = "gazeX_" + std::to_string(i);
		std::string gazeY = "gazeY_" + std::to_string(i);
		std::string gazeXLine = "@ATTRIBUTE " + gazeX + " NUMERIC";
		std::string gazeYLine = "@ATTRIBUTE " + gazeY + " NUMERIC";
		out << gazeXLine << std::endl << gazeYLine << std::endl;
	}
	//going to add a new feature here at the end
	std::string meanX = "@ATTRIBUTE meanX NUMERIC";
	std::string meanY = "@ATTRIBUTE meanY NUMERIC";
	std::string sdX = "@ATTRIBUTE sdX NUMERIC";
	std::string sdY = "@ATTRIBUTE sdY NUMERIC";
	out << meanX << std::endl << meanY << std::endl;
	out << sdX << std::endl << sdY << std::endl;
	out << "@ATTRIBUTE class { low, medium, high, ASD }\n"
		<< "\n@DATA\n";
	WriteArffGazePoints(out, 100000);
	out.close();
	out2.close();
}
bool ASDClassification::EyeMissing(std::vector<std::string>& data)
{
	//there are some rows in the file that don't have data. 
	if (data.at(4).empty() || data.at(5).empty() || data.at(11).empty() || data.at(12).empty())
	{
		return true;
	}
	return false;
}
void ASDClassification::ReadCSVFile(std::string csvFile)
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
		std::vector<std::string> split;
		std::getline(in, line);
		boost::split(split, line, boost::is_any_of(","));
		if (lineCounter != 0 && boost::lexical_cast<int>(split.at(0)) < 64)
		{
			SubjectData sd;
			sd.age = boost::lexical_cast<int>(split.at(0));
			sd.gender = split.at(1);
			sd.diagnosis = split.at(2);
			sd.fileNameWithPath = split.at(3);
			sd.fileName = split.at(3);
			sd.type = boost::lexical_cast<int>(split.at(4));
			sd.typeInfo = split.at(5);
			data.push_back(sd);
		}
		else
		{
			//don't get header row in file
			++lineCounter;
		}
	}
	in.close();
}