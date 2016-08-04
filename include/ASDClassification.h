#ifndef ASD_CLASSIFICATION_H
#define ASD_CLASSIFICATION_H
#include <string>
#include <vector>

#include "SubjectData.h"

class ASDClassification
{
public:
	ASDClassification();
	void ReadCSVFile(std::string csvFile);
	void ParseTSVFiles(std::string tsvDir);
	size_t GetNumberOfSubjects();
	void CreateDisplayImageOfGaze(size_t subject);

private:
	std::vector<SubjectData> data;

	bool EyeMissing(std::vector<std::string>& data);
	void ParseTSVFile(SubjectData& data);
};
#endif
