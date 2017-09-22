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
void ASDClassification::CreateDisplayImageOfGaze()
{
	for (size_t i = 0; i < data.size(); ++i)
	{	
		// Added this for display purposes; this way we know when it is done parsing as well. Used manual flush as well as described in ParseTSVFile() -Diego
		std::cout << "Displaying Image " << i << "\r";
		std::cout.flush();
		Image image(512, 512);
		image.PlotVector2Ds(data.at(i).avgGaze, data.at(i));
		image.Display(data.at(i).GetTitle());
		
	}
	std::cout << std::endl;
}
void ASDClassification::ParseTSVFiles(std::string tsvDir)
{
	float percent(1.f);
	for (auto& d : data)
	{
		d.fileNameWithPath = tsvDir + d.fileName;
		std::cout << "Parsing TSV Files (" << static_cast<int>((percent / data.size()) * 100) << "%)\r";
		std::cout.flush(); // Manual flush is required to push contents from cout buffer. 
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
		numLines++;
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
					if (!split.at(18).empty()) //make sure we actually have data
					{
					// Moved this fragment to inner loop, since it says here is when we have actual data, tried it classifying with both placements before adding velocity, and it yielded to same results - Diego
					data.avgGaze.emplace_back(boost::lexical_cast<int>(split.at(19)), boost::lexical_cast<int>(split.at(20)));
                                        data.GazeVector2DXR = boost::lexical_cast<float>(split.at(11));
                                        data.GazeVector2DYR = boost::lexical_cast<float>(split.at(12));
                                        data.GazeVector2DXL = boost::lexical_cast<float>(split.at(4));
                                        data.GazeVector2DYL = boost::lexical_cast<float>(split.at(5));
					
					std::string time = split.at(2);
					// See comment in the next else, inside of the if statement to see how this works -Diego 
                                        int minutes_frame = boost::lexical_cast<int>(time.substr(3,2) );
                                        int seconds_frame = boost::lexical_cast<int>(time.substr(6,2));
					int millisec_frame = boost::lexical_cast<int>(time.substr(9,3));

					date d2(2002, Feb, 1);
					ptime t(d2, hours(0) + minutes(minutes_frame) + seconds(seconds_frame) + millisec(millisec_frame));
					time_duration t_duration = t.time_of_day(); // DateTimeStampStartOffset in the Database - Diego
					long frameTime = t_duration.total_milliseconds(); // Time in milliseconds -Diego

					data.frameData.push_back(frameTime); // Store in the vector the time at which each frame happened -Diego			
										
						data.fixationIndex = boost::lexical_cast<int>(split.at(18));
						if (fixCounter == 0) //gets initial data
						{
							time1 = split.at(2); //get time, need to convert time string into something we can add
							time2 = time1;
							tempFixationIndex = boost::lexical_cast<int>(split.at(18));
							fixCounter++; //dont want if statement to repeat
						}
						else
						{
							if (boost::lexical_cast<int>(split.at(18)) == tempFixationIndex)
							{
								time1 = split.at(2); //need to figure out how to do this
								/* In contrast to the method used above, .at() returns a character, adding time.at(X) with time.at(Y)
								 returns the sum of the 2 ASCII values, then that is parsed into an Integer. Example, the first parsed row from
								the TSV file (pathTo/tsvData/316s09v01-All-Data.tsv) is row 241, the time offset for this is 00:00:03.513, 
								which is the value of time1, 
								 Example, 
								minutes1 = grabs time1.at(3) + time.at(4) which we can see that corresponds to 0 and 0
								however .at() returns a character,
								so we have '0' + '0' which correspond to ASCII value of 48, so it will give 96 and that will get parsed. 	
								I did not touch any of this code below, but at first I tried to use this method, and this is what I found out.
								Using substr() which returns a str will make the summation concatenate the strings. 
								This can be testing printing out t_duration, and frameTime, and looking at row 241 of the mentioned file.
								-Diego 
								*/
								int hours1 = boost::lexical_cast<int>(time1.at(0) + time1.at(1));	
								int minutes1 = boost::lexical_cast<int>(time1.at(3) + time1.at(4));
								int seconds1 = boost::lexical_cast<int>(time1.at(6));

								int hours2 = boost::lexical_cast<int>(time2.at(0) + time2.at(1));
								int minutes2 = boost::lexical_cast<int>(time2.at(3) + time2.at(4));
								int seconds2 = boost::lexical_cast<int>(time2.at(6));

								date d(2002, Feb, 1);
								ptime t1(d, hours(hours1) + minutes(minutes1) + seconds(seconds1) + millisec(0));
								ptime t2(d, hours(hours2) + minutes(minutes2) + seconds(seconds2) + millisec(0));
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
			counter2++;
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
void ASDClassification::WriteArffGazeVectors(std::ostream& out)
{
	Vector2D sd;
	Vector2D mean;
	float avgVel;
	float avgMag;
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
			int size(static_cast<int>(subject.avgGaze.size()));
			for (int i = 0; i < size; ++i)
			{
				mean += subject.avgGaze.at(i);
				sd += (subject.avgGaze.at(i)*subject.avgGaze.at(i));
				if (i < size - 1)
				{
					// We pass the other vector and the difference of the time in which the frame happened to our velocity function, which will calculate 
					// The velocity from one frame to the other. -Diego
					avgVel += subject.avgGaze.at(i).Velocity(subject.avgGaze.at(i + 1), (subject.frameData.at(i+1) - subject.frameData.at(i)) ); 
					avgMag += subject.avgGaze.at(i).Magnitude(subject.avgGaze.at(i + 1));
				}
			}
			mean /= size;
			avgVel /= size;
			avgMag /= size - 1;
			sd.x -= (size*(mean.x*mean.x));
			sd.x /= (size - 1);
			sd.y -= (size*(mean.y*mean.y));
			sd.y /= (size - 1);
			out << mean.x << "," << mean.y << ",";
			out << sd.y << "," << sd.y << ",";
			out << avgMag << ",";
			out << avgVel << ",";
			out << subject.timeVector.size() << ",";
			out << subject.diagnosis << std::endl;
		}
	}
	//std::cout << count << std::endl;
}
void ASDClassification::WriteArffFile(std::string file)
{
	std::cout << "Writing ARFF file header..." << std::endl;
	std::ofstream out;
	out.open(file);
	out << "% 1. Title: ASD Classification\n"
		<< "%\n"
		<< "% 2. Sources :\n"
		<< "% (a)Creator : Shaun Canavan\n"
		<< "% (b)Date : 2017\n"
		<< "%\n"
		<< "@RELATION asd\n"
		<< "\n"
		<< "@ATTRIBUTE gender NUMERIC\n"
		<< "@ATTRIBUTE age NUMERIC\n";
	std::string meanX = "@ATTRIBUTE meanX NUMERIC";
	std::string meanY = "@ATTRIBUTE meanY NUMERIC";
	std::string sdX = "@ATTRIBUTE sdX NUMERIC";
	std::string sdY = "@ATTRIBUTE sdY NUMERIC";
	std::string mag = "@ATTRIBUTE mag NUMERIC";
	std::string velocity = "@ATTRIBUTE velocity NUMERIC";
	std::string fix = "@ATTRIBUTE fix NUMERIC";
	out << meanX << std::endl << meanY << std::endl;
	out << sdX << std::endl << sdY << std::endl;
	out << mag << std::endl;
	out << velocity << std::endl;
	out << fix << std::endl;
	out << "@ATTRIBUTE class { low, medium, high, ASD }\n"
		<< "\n@DATA\n";
	std::cout << "Writing gaze vectors to ARFF file..." << std::endl;
	WriteArffGazeVectors(out);
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
void ASDClassification::ReadCSVFile(std::string csvFile, bool removeOutliers)
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
		if (lineCounter != 0)
		{
			if (removeOutliers)
			{
				if (boost::lexical_cast<int>(split.at(0)) >= 64)
				{
					continue;
				}
			}
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
