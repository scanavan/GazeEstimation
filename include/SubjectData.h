#ifndef SUBJECT_DATA_H
#define SUBJECT_DATA_H
#include <string>
#include <vector>
#include "Point.h"

struct SubjectData
{
	//file names from test
	std::string fileName;
	std::string fileNameWithPath;
	//subject gender
	std::string gender;
	//autism diagnosis
	std::string diagnosis;

	//all gaze points
	std::vector<Point>avgGaze;

	//age of subject
	int age;

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
		return title;
	}
	friend std::ostream &operator<<(std::ostream& os, SubjectData& sd)
	{
		os << "Filename: " << sd.fileName << std::endl
			<< "Age: " << sd.age << std::endl
			<< "Gender: " << sd.gender << std::endl
			<< "Risk: " << sd.diagnosis << std::endl
			<< "Type: " << sd.type << std::endl
			<< "Type Info: " << sd.typeInfo << std::endl;
		return os;
	}
};
#endif
