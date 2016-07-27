#ifndef NDAR_DATA_H
#define NDAR_DATA_H
#include <string>
#include <vector>
#include "boost/filesystem.hpp"
#include "EyeTrackingData.h"	//for Point structure
#include <boost/lexical_cast.hpp>


struct SmallData
{
	//just filename and some eye gaze data
	std::string fileNameWithPath;
	std::string path;
	std::string fileName;

	std::vector<Point>leftGaze;
	std::vector<Point>rightGaze;
	std::vector<Point>avgGaze;
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
	NDARData(std::string tsvDirectory);
	size_t GetNumberOfSubjects() { return tsvData.size(); }
	void  DisplayGazeMap(int subject);

private:
	void ParseTSVFile(std::string);
	void PopulateTSVVectorWithSmallData(std::vector<std::string>& splitData, SmallData& data);
	bool EyeMissing(std::vector<std::string>& data);
	//each vector is a file, each internal vector is a timestamp
	std::vector<SmallData> tsvData;
};
#endif