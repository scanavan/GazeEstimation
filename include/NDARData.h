#ifndef NDAR_DATA_H
#define NDAR_DATA_H
#include <string>
#include <vector>
#include "boost/filesystem.hpp"
#include "EyeTrackingData.h"	//for Point structure
#include <boost/lexical_cast.hpp>

struct SmallData
{
	std::string fileName;
	std::string fileNameWithPath;
	std::vector<Point>avgGaze;
	int age;
	std::string gender;
	std::string diagnosis;
	int width;
	int height;
	float avgDistanceFromCentroid;
	std::vector<std::vector<Point>>clusters;

	SmallData() : fileName(""), fileNameWithPath(""), age(0), gender(""), diagnosis(""), width(640), height(512), avgDistanceFromCentroid(0.f)
	{
	}
	

	std::string GetTitle()
	{
		std::string title("File: ");
		title.append(fileName);
		title.append(" age: ");
		title.append(std::to_string(age));
		title.append(" gender: ");
		title.append(gender);
		title.append(" risk: ");
		title.append(diagnosis);
		return title;
	}
	friend std::ostream &operator<<(std::ostream& os, SmallData& data)
	{
		os << "FileName: " << data.fileName << std::endl
			<< "Autism Risk: " << data.diagnosis << std::endl
			<< "Gender: " << data.gender << std::endl
			<< "Age: " << data.age << std::endl
			<< "Average gaze distance from centroid: " << data.avgDistanceFromCentroid << std::endl;
		return os;
	}
};
struct AllData
{
	//all data from tsv files
	std::string fileNameWithPath;
	std::string path; 
	std::string fileName;

	std::vector<int>  timeStamp;
	std::vector<std::string> dateTimeStamp;
	std::vector<std::string> dateTimeStampStartOffset;

	std::vector<int> number;

	std::vector<Point> leftGaze;
	std::vector<Point> cameraLeft;
	std::vector<float> leftDistance;
	std::vector<float> leftPupil;
	std::vector<int> leftValidity;

	std::vector<Point> rightGaze;
	std::vector<Point> cameraRight;
	std::vector<float> rightDistance;
	std::vector<float> rightPupil;
	std::vector<int> rightValidity;

	std::vector<int> fixationIndex;
	std::vector<Point> averageGaze;

	std::vector<std::string> event;
	std::vector<int> eventKey;

	std::vector<int> data1;
	std::vector<int> data2;

	std::vector<std::string> descriptor;
	std::vector<std::string> stimuliName;
	std::vector<std::string> stimuliID;

	std::vector<int> mediaWidth;
	std::vector<int> mediaHeight;

	std::vector<Point> mediaPos;
	std::vector<Point> mappedFixationPoint;

	std::vector<int> fixationDuration;
	std::vector<int> aoilds;
	std::vector<std::string> aoiName;

	std::vector<std::string> webGroupImage;

	std::vector<Point> mappedGazeDataPoint;

	std::vector<int> microSecondTimeStamp;

	std::vector<int> absoluteMicroSecondTimeStamp;
};

class NDARData
{
public:
	NDARData(std::string tsvDirectory, std::string csvFile);
	size_t GetNumberOfSubjects() { return tsvData.size(); }
	void  DisplayGazeMap(int subject, std::string diagnosis="all");
	void ClusterGazeData(int subject=0);
	void DisplayClusterData(int subject, std::string title = "Cluster Data");
	void GetNewCentroids(Point& c1, Point& c2, Point& c3, Point& c4, std::vector<std::vector<Point>>&clusters);
	void GetAvgDistanceFromCentroid(int subject);
	SmallData at(size_t i)
	{
		return tsvData.at(i);
	}
private:
	bool NDARData::EyeMissing(std::vector<std::string>& data);
	void NDARData::PopulateTSVVectorWithSmallData(std::vector<std::string>& splitData, SmallData& data);
	void ReadCSVFile(std::string dir, std::string csvFile);
	void ParseTSVFile(SmallData& data);
	std::vector<SmallData> tsvData;

	float Distance(Point p1, Point p2);
};
#endif