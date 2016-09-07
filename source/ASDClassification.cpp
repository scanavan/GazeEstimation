#include "ASDClassification.h"
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lambda/bind.hpp>
#include <iostream>
#include "Image.h"

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
	image.PlotPoints(data.at(subject).avgGaze);
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
					data.avgGaze.emplace_back(boost::lexical_cast<int>(split.at(19)), boost::lexical_cast<int>(split.at(20)));
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
void ASDClassification::WriteArffGazePoints(std::ostream& out, int size)
{
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
			for (int i = 0; i < size; ++i)
			{
				out << std::to_string(subject.avgGaze.at(i).x) << "," << std::to_string(subject.avgGaze.at(i).y) << ",";
			}
			out << subject.diagnosis << std::endl;
		}
		++count;
	}
	std::cout << count << std::endl;
}
void ASDClassification::WriteArffFile(std::string file)
{
	std::ofstream out;
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
	int size(100000);
	for (auto& subject : data)
	{
		if (subject.avgGaze.size() < size)
		{
			size = static_cast<int>(subject.avgGaze.size());
		}
	}
	for (int i = 0; i < size; ++i)
	{
		std::string gazeX = "gazeX_" + std::to_string(i);
		std::string gazeY = "gazeY_" + std::to_string(i);
		std::string gazeXLine = "@ATTRIBUTE " + gazeX + " NUMERIC";
		std::string gazeYLine = "@ATTRIBUTE " + gazeY + " NUMERIC";
		out << gazeXLine << std::endl << gazeYLine << std::endl;
	}
	out << "@ATTRIBUTE class { low, medium, high, ASD }\n"
		<< "\n@DATA\n";
	WriteArffGazePoints(out, size);
	out.close();
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
		std::getline(in, line);
		if (lineCounter != 0)
		{
			std::vector<std::string> split;
			boost::split(split, line, boost::is_any_of(","));
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