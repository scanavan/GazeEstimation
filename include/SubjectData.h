#ifndef SUBJECT_DATA_H
#define SUBJECT_DATA_H
#include <string>
#include <vector>
#include "Vector2D.h"
#include "Frame.h"
#include <iostream>

struct SubjectData
{
	//file names from test
	std::string fileName;
	std::string fileNameWithPath;
	//subject gender
	std::string gender;
	//autism diagnosis	--> classification
	std::string diagnosis;

	//all gaze Vector2Ds
	std::vector<Vector2D>avgGaze;

	std::vector<time_t> timeVector;
	// Vector to store the time at which frame happened -Diego
	std::vector<long> frameData;
	// All frames, needed to calculate velocity at each grid, we need to remember the time when they happened. -Diego
	std::vector<Frame> allFrames;

	// Number of times subject looked outside of the monitor
	long OutOfMonitor = 0;

	// Number of times negative value is found tand we have fixation time.
	long negativeGaze = 0;

	time_t saveTime = 0;

	//age of subject
	int age;

	//participant number
	int participantNumber;

	//Time of Test
	std::string DateTime;

	//X Gaze Vector2D Right Eye
	float GazeVector2DXR;

	//Y Gaze Vector2D Right Eye
	float GazeVector2DYR;

	//X Gaze Vector2D Left Eye
	float GazeVector2DXL;

	//Y Gaze Vector2D LEft Eye
	float GazeVector2DYL;

	//Fixation Number
	int fixationIndex;

	//type of video/image watched
	int type;
	std::string typeInfo;

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
		title.append(" type: ");
		title.append(std::to_string(type));
		title.append(" Test Length: ");
		title.append(DateTime);
		title.append(" Number of Fixations: ");
		title.append(std::to_string(fixationIndex));
		title.append(" Participant Number: ");
		title.append(std::to_string(participantNumber));
		return title;
	}
	friend std::ostream &operator<<(std::ostream& os, SubjectData& sd)
	{
		os << "Filename: " << sd.fileName << std::endl
			<< "Age: " << sd.age << std::endl
			<< "Gender: " << sd.gender << std::endl
			<< "Risk: " << sd.diagnosis << std::endl
			<< "Type: " << sd.type << std::endl
			<< "Type Info: " << sd.typeInfo << std::endl
			<< "Test Length: " << sd.DateTime << std::endl
			<< "Number of Fixations: " << sd.fixationIndex << std::endl
			<< "Participant Number: " << sd.participantNumber << std::endl;
		return os;
	}
};
#endif
