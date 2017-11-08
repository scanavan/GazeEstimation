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
#include "helper.h"
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::filesystem;

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
		Image image(512, 512, true, false);
		image.PlotVector2Ds(data.at(i).avgGaze, data.at(i));
		image.Display(data.at(i).GetTitle(), data.at(i).diagnosis);

	}
	std::cout << std::endl;
}

void ASDClassification::CreateCollageOfImages()
{
	std::string path = "./output/images/";
	std::string paths_to_images[5];

	int i = 0;

	// Loop through the directory to find the path to the first 4 images.
	for (directory_iterator itr(path); itr != directory_iterator() && i < 5; ++itr, ++i)
	{
			if (i == 0)
			{
				continue;
			}
	    paths_to_images[i] = itr->path().string();
	}

		// New image is twice the height and width of our previous ones since we are stacking 2.
		int size = 1048;
		int subset_size = 524;

		// Initialize the collage image.
		cv::Mat image_collection;
		image_collection = cv::Mat::zeros(size, size, CV_8UC3);
		image_collection.setTo(cv::Scalar(255, 255, 255));

		// Initialize our already created image.
		cv::Mat subset_image;

		// Top left subset image
		subset_image = cv::imread(paths_to_images[1]);
		// Calling a constructor as a function :thinking: lol
		subset_image.copyTo(image_collection(cv::Rect(0,0, subset_image.cols, subset_image.rows)));

		// Top right subset image
		subset_image = cv::imread(paths_to_images[2]);
		subset_image.copyTo(image_collection(cv::Rect(size/2,0, subset_image.cols, subset_image.rows)));

		// Bottom left subset image
		subset_image = cv::imread(paths_to_images[3]);
		subset_image.copyTo(image_collection(cv::Rect(0,size/2, subset_image.cols, subset_image.rows)));

		// Bottom rigt subset image
		subset_image = cv::imread(paths_to_images[4]);
		subset_image.copyTo(image_collection(cv::Rect(size/2,size/2, subset_image.cols, subset_image.rows)));

		// Saving the new image we created
		std::string image_name = "gaze_collection_of_images.jpg";
		std::string path_to_image = "./output/images/collection/" + image_name;
		cv::imwrite(path_to_image, image_collection);

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
	std::string line;
	std::ifstream in(data.fileNameWithPath);

	int fixCounter(0);
	int tempFixationIndex(0);
	std::string time1;
	std::string time2;

	std::vector<std::string> split;
	std::getline(in, line);

	// Find our label row
	while (std::getline(in, line))
	{
		if(line.find("TimeStamp") != std::string::npos)
			break;
	}
	if(in.eof())
	{
		std::cout << "Label was not found in a file, can't parse TSV." << std::endl;
		std::cout.flush();
		exit(EXIT_FAILURE);
	}
	boost::split(split, line, boost::is_any_of("\t")); // Split is a vector of strings of the header line at this moment.

	// Find the offset of the columns that we will need and we make that our accesing indexes.
  int time_index =  std::find(split.begin(), split.end(), "DateTimeStampStartOffset") - split.begin();
	int X_index = std::find(split.begin(), split.end(), "GazePointX") - split.begin();
	int Y_index = std::find(split.begin(), split.end(), "GazePointY") - split.begin();
	int Fixation_index = std::find(split.begin(), split.end(), "FixationIndex") - split.begin();

	if(time_index >= split.size() || X_index >= split.size() || Y_index >= split.size() || Fixation_index >= split.size())
	{
			std::cout << "A TSV file did not have one of the columns, cannot parse files." << std::endl;
			std::cout.flush();
			exit(EXIT_FAILURE);
	}
	while (!in.eof() || in.peek() != EOF)
	{
			// We move to the next line first since we started at the header.
			std::getline(in, line);
			boost::split(split, line, boost::is_any_of("\t"));

			if (split.size() == 43)
			{
				if (!EyeMissing(split))
				{
					if (!split.at(Fixation_index).empty()) //make sure we actually have data
					{
							if ( boost::lexical_cast<int>(split.at(Y_index)) < 0 || boost::lexical_cast<int>(split.at(Y_index)) < 0 )
							{
								// We cannot have X or Y Gaze values negative, therefore we increment tracker and continue.
								++data.negativeGaze;
								continue;
							}

							data.avgGaze.emplace_back(boost::lexical_cast<int>(split.at(X_index)), boost::lexical_cast<int>(split.at(Y_index)));
							long time_in_ms = getTimeInMs(split.at(time_index));
							data.frameData.push_back(time_in_ms); // Store the time at which frame happened. -Diego
							data.allFrames.emplace_back(boost::lexical_cast<int>(split.at(X_index)), boost::lexical_cast<int>(split.at(Y_index)), time_in_ms );

							data.fixationIndex = boost::lexical_cast<int>(split.at(Fixation_index));
							if (fixCounter == 0) //gets initial data
							{
								time1 = split.at(2); //get time, need to convert time string into something we can add
								time2 = time1;
								tempFixationIndex = boost::lexical_cast<int>(split.at(Fixation_index));
								fixCounter++; //dont want if statement to repeat
							}
							else
							{
								if (boost::lexical_cast<int>(split.at(Fixation_index)) == tempFixationIndex)
								{
									time1 = split.at(2);
									data.saveTime += calculate_frame_duration(time1, time2);
								}
								else // we are at next fixation
								{
									data.timeVector.push_back(data.saveTime); // save accumulated time in a vector
									data.saveTime = 0;
									time1 = split.at(2);
									tempFixationIndex = boost::lexical_cast<int>(split.at(Fixation_index));
								}
							}
					} else {
					// If we get here it means we did not have fixation time in tsv file.
					++data.OutOfMonitor;
					}
				}
			}
	}
	in.close();
}
void ASDClassification::WriteArffGazeVectors(std::ostream& out)
{
	Vector2D sd;
	Vector2D mean;
	Vector2D velocity;
	float avgVel = 0;
	float avgMag = 0;
	float centroid = 0;

	for (auto& subject : data)
	{
		//if (subject.type == 3)
		{
			int gender = 1;
			if (subject.gender.compare("M") == 0)
			{
				gender = 0;
			}
			out /* << gender << "," */ << std::to_string(subject.age) << ",";
			int size(static_cast<int>(subject.avgGaze.size()));

			// std::vector<Vector2D> grid(screenGridAverages(subject.avgGaze));
			std::vector<int> frequency(findFreqency(subject.avgGaze));
			std::vector<std::vector<Frame>> separated_gaze(separateFrames(subject.allFrames));
			std::vector<float> velocity_per_Grid(velocityAtEachGrid(separated_gaze));
		//	centroid = avgToCentroid(subject.avgGaze);
/*
			for (int i = 0; i < size; ++i)
			{
				mean += subject.avgGaze.at(i);
				sd += (subject.avgGaze.at(i)*subject.avgGaze.at(i));

				if (i < size - 1)
				{
					avgVel += subject.avgGaze.at(i).Velocity_overall(subject.avgGaze.at(i + 1), (subject.frameData.at(i+1) - subject.frameData.at(i)) );
					avgMag += subject.avgGaze.at(i).Magnitude(subject.avgGaze.at(i + 1));
					velocity += subject.avgGaze.at(i).Velocity_points(subject.avgGaze.at(i + 1), (subject.frameData.at(i+1) - subject.frameData.at(i)));
				}
			}
*/
		//	mean /= size;
		//	avgVel /= size - 1;
		//	avgMag /= size - 1;
		//	sd.x -= (size*(mean.x*mean.x));
		//	sd.x /= (size - 1);
		//	sd.y -= (size*(mean.y*mean.y));
		//	velocity.x /= size - 1;
	//		velocity.y /= size - 1;
	//		out << mean.x << "," << mean.y << ",";
	//		out << avgMag << ",";
		//	out << avgVel << ",";
	//		out << velocity.x << ",";
	//		out << velocity.y << ",";
			out << subject.OutOfMonitor << ",";
//			out << centroid << ",";
			out << frequency.at(0) << ",";
      out << frequency.at(1) << ",";
      out << frequency.at(2) << ",";
      out << frequency.at(3) << ",";
      out << frequency.at(4) << ",";
      out << frequency.at(5) << ",";
      out << frequency.at(6) << ",";
      out << frequency.at(7) << ",";
      out << frequency.at(8) << ",";
	/*		out << grid.at(0).x << ",";
			out << grid.at(1).x << ",";
			out << grid.at(2).x << ",";
			out << grid.at(3).x << ",";
			out << grid.at(4).x << ",";
      out << grid.at(5).x << ",";
      out << grid.at(6).x << ",";
      out << grid.at(7).x << ",";
			out << grid.at(8).x << ",";
			out << grid.at(0).y << ",";
      out << grid.at(1).y << ",";
      out << grid.at(2).y << ",";
      out << grid.at(3).y << ",";
      out << grid.at(4).y << ",";
      out << grid.at(5).y << ",";
      out << grid.at(6).y << ",";
      out << grid.at(7).y << ",";
      out << grid.at(8).y << ",";
			 */
			out << velocity_per_Grid.at(0) << ",";
			out << velocity_per_Grid.at(1) << ",";
			out << velocity_per_Grid.at(2) << ",";
			out << velocity_per_Grid.at(3) << ",";
			out << velocity_per_Grid.at(4) << ",";
			out << velocity_per_Grid.at(5) << ",";
			out << velocity_per_Grid.at(6) << ",";
			out << velocity_per_Grid.at(7) << ",";
			out << velocity_per_Grid.at(8) << ",";
	//		out << subject.negativeGaze << ",";
			out << subject.timeVector.size() << ",";
			out << subject.diagnosis << std::endl;
		}
	}
	// std::cout << std::endl;
}
void ASDClassification::WriteArffFile(std::string file)
{
	std::cout << "Writing ARFF file header..." << std::endl;
	std::ofstream out;
	out.open(file);
	out << "% 1. Title: ASD Classification\n"
		<< "%\n"
		<< "% 2. Sources :\n"
		<< "% (a)Creator : Shaun Canavan with collaboration of Diego Fabiano \n"
		<< "% (b)Date : 2017\n"
		<< "%\n"
		<< "@RELATION asd\n"
		<< "\n"
//		<< "@ATTRIBUTE gender NUMERIC\n"
		<< "@ATTRIBUTE age NUMERIC\n";
	std::string meanX = "@ATTRIBUTE meanX NUMERIC";
	std::string meanY = "@ATTRIBUTE meanY NUMERIC";
	std::string sdX = "@ATTRIBUTE sdX NUMERIC";
	std::string sdY = "@ATTRIBUTE sdY NUMERIC";
	std::string mag = "@ATTRIBUTE mag NUMERIC";
	std::string avgVel = "@ATTRIBUTE avgVel NUMERIC";
	std::string velocityX = "@ATTRIBUTE velocityX NUMERIC";
	std::string velocityY = "@ATTRIBUTE velocityY NUMERIC";
	std::string outMonitor = "@ATTRIBUTE outMonitor NUMERIC";
	std::string centroid = "@ATTRIBUTE centroid NUMERIC";
	std::string fix = "@ATTRIBUTE fix NUMERIC";
	std::string bottonLeftFreq = "@ATTRIBUTE bottonLeftFreq NUMERIC";
  std::string leftMiddleFreq = "@ATTRIBUTE leftMiddleFreq NUMERIC";
  std::string leftTopFreq = "@ATTRIBUTE leftTopFreq NUMERIC";
  std::string bottonMiddleFreq = "@ATTRIBUTE bottonMiddleFreq NUMERIC";
  std::string midMiddleFreq = "@ATTRIBUTE midMiddleFreq NUMERIC";
  std::string topMiddleFreq = "@ATTRIBUTE topMiddleFreq NUMERIC";
  std::string bottomRightFreq = "@ATTRIBUTE bottomRightFreq NUMERIC";
  std::string midRightFreq = "@ATTRIBUTE midRightFreq NUMERIC";
  std::string topRightFreq = "@ATTRIBUTE topRightFreq NUMERIC";

	std::string bottonLeftX = "@ATTRIBUTE bottonLeftX NUMERIC";
	std::string leftMiddleX = "@ATTRIBUTE leftMiddleX NUMERIC";
	std::string leftTopX = "@ATTRIBUTE leftTopX NUMERIC";
	std::string bottonMiddleX = "@ATTRIBUTE bottonMiddleX NUMERIC";
	std::string midMiddleX = "@ATTRIBUTE midMiddleX NUMERIC";
	std::string topMiddleX = "@ATTRIBUTE topMiddleX NUMERIC";
	std::string bottomRightX = "@ATTRIBUTE bottomRightX NUMERIC";
	std::string midRightX = "@ATTRIBUTE midRightX NUMERIC";
	std::string topRightX = "@ATTRIBUTE topRightX NUMERIC";

	std::string bottonLeftY = "@ATTRIBUTE bottonLeftY NUMERIC";
  std::string leftMiddleY = "@ATTRIBUTE leftMiddleY NUMERIC";
  std::string leftTopY = "@ATTRIBUTE leftTopY NUMERIC";
  std::string bottonMiddleY = "@ATTRIBUTE bottonMiddleY NUMERIC";
  std::string midMiddleY = "@ATTRIBUTE midMiddleY NUMERIC";
  std::string topMiddleY = "@ATTRIBUTE topMiddleY NUMERIC";
  std::string bottomRightY = "@ATTRIBUTE bottomRightY NUMERIC";
  std::string midRightY = "@ATTRIBUTE midRightY NUMERIC";
  std::string topRightY = "@ATTRIBUTE topRightY NUMERIC";

	std::string bottonLeftVelocity = "@ATTRIBUTE bottonLeftVelocity NUMERIC";
	std::string leftMiddleVelocity = "@ATTRIBUTE leftMiddleVelocity NUMERIC";
	std::string leftTopVelocity = "@ATTRIBUTE leftTopVelocity NUMERIC";
	std::string bottonMiddleVelocity = "@ATTRIBUTE bottonMiddleVelocity NUMERIC";
	std::string midMiddleVelocity = "@ATTRIBUTE midMiddleVelocity NUMERIC";
	std::string topMiddleVelocity = "@ATTRIBUTE topMiddleVelocity NUMERIC";
	std::string bottomRighVelocity = "@ATTRIBUTE bottomRightVelocity NUMERIC";
	std::string midRightVelocity = "@ATTRIBUTE midRightVelocity NUMERIC";
	std::string topRighVelocity = "@ATTRIBUTE topRightVelocity NUMERIC";

	std::string negativeGaze = "@ATTRIBUTE negativeGaze NUMERIC";


/*	out << meanX << std::endl << meanY << std::endl;
	//out << sdX << std::endl << sdY << std::endl;
	out << mag << std::endl;
	out << avgVel << std::endl;
	out << velocityX << std::endl;
	out << velocityY << std::endl; */
	out << outMonitor << std::endl;
	//out << centroid << std::endl;

	out << bottonLeftFreq << std::endl;
  out << leftMiddleFreq << std::endl;
  out << leftTopFreq << std::endl;
  out <<  bottonMiddleFreq << std::endl;
  out <<  midMiddleFreq << std::endl;
  out <<  topMiddleFreq << std::endl;
  out <<  bottomRightFreq << std::endl;
  out <<  midRightFreq << std::endl;
  out <<  topRightFreq << std::endl;
/*
	out << bottonLeftX << std::endl;
  out << leftMiddleX << std::endl;
  out << leftTopX << std::endl;
  out <<  bottonMiddleX << std::endl;
  out <<  midMiddleX << std::endl;
  out <<  topMiddleX << std::endl;
  out <<  bottomRightX << std::endl;
  out <<  midRightX << std::endl;
  out <<  topRightX << std::endl;

  out <<  bottonLeftY << std::endl;
  out <<  leftMiddleY << std::endl;
  out <<  leftTopY << std::endl;
  out <<  bottonMiddleY << std::endl;
  out <<  midMiddleY << std::endl;
  out <<  topMiddleY << std::endl;
  out <<  bottomRightY << std::endl;
  out <<  midRightY << std::endl;
  out << topRightY << std::endl;
	*/
	out << bottonLeftVelocity << std::endl;
	out << leftMiddleVelocity << std::endl;
	out << leftTopVelocity << std::endl;
	out << bottonMiddleVelocity << std::endl;
	out << midMiddleVelocity << std::endl;
	out << topMiddleVelocity << std::endl;
	out << bottomRighVelocity << std::endl;
	out << midRightVelocity << std::endl;
	out << topRighVelocity << std::endl;

	//out << negativeGaze << std::endl;
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

		// if a specific row is -1 this participant should not be considered
		if (lineCounter != 0 && boost::lexical_cast<int>(split.at(4)) != -1  )
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
void ASDClassification::CreateSubsetOfData()
{
	//this function creates of subset of data that has same number of subjects for each class
	//and the exact same amount of gaze points
	std::cout << "Creating subset of data..." << std::endl;
	//get smallest count of class
	unsigned low(0), med(0), high(0), asd(0), minGaze(1000000);
	for (auto& subject : data)
	{
		if (subject.diagnosis.compare("low") == 0)
			low++;
		else if (subject.diagnosis.compare("medium") == 0)
			med++;
		else if (subject.diagnosis.compare("high") == 0)
			high++;
		else
			asd++;

		if (subject.avgGaze.size() < minGaze)
		{
			minGaze = subject.avgGaze.size();
		}
	}
	int min = std::min({ low, med, high, asd });
	//parse data and create new SubjectData
	std::vector<SubjectData> temp;
	low = 0;
	med = 0;
	high = 0;
	asd = 0;
	for (auto& subject : data)
	{
		std::vector<Vector2D> tempGaze;
		//get vector of random data to select - this is NOT efficient as there is potential to have an infinite loop...
		std::set<int> indices;
		while (indices.size() < std::min(400.f, static_cast<float>(minGaze)))
		{
			int random = rand() % minGaze;
			if (indices.find(random) == indices.end())
			{
				indices.insert(random);
			}
		}
		//chop gaze points
		for (unsigned i = 0; i<indices.size(); ++i)
		{
			//std::cout << *indices.begin() + i << " " << indices.size() << " " << minGaze << std::endl;
			tempGaze.push_back(subject.avgGaze.at(*indices.begin() + i));
		}
		subject.avgGaze.clear();
		subject.avgGaze = tempGaze;
		if (subject.diagnosis.compare("low") == 0)
		{
			if (low < min)
			{
				++low;
				temp.push_back(subject);
			}
		}
		else if (subject.diagnosis.compare("medium") == 0)
		{
			if (med < min)
			{
				++med;
				temp.push_back(subject);
			}
		}
		else if (subject.diagnosis.compare("high") == 0)
		{
			if (high < min)
			{
				++high;
				temp.push_back(subject);
			}
		}
		else
		{
			if (asd < min)
			{
				++asd;
				temp.push_back(subject);
			}
		}
	}
	data.clear();
	data = temp;
	std::cout << "Number of subjects in subset: " << data.size() << std::endl;
}
