#ifndef ASD_CLASSIFICATION_H
#define ASD_CLASSIFICATION_H
#include <string>
#include <vector>

#include "Point.h"


class ASDClassification
{
public:
	ASDClassification();
	void ReadCSVFile(std::string csvFile);
	void ParseTSVFiles(std::string tsvDir);
	size_t GetNumberOfSubjects();
	void CreateDisplayImageOfGaze(size_t subject);

private:
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
	};
	std::vector<SubjectData> data;

	bool EyeMissing(std::vector<std::string>& data);
	void ParseTSVFile(SubjectData& data);
};
#endif
