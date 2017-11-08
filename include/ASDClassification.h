#ifndef ASD_CLASSIFICATION_H
#define ASD_CLASSIFICATION_H
#include <string>
#include <vector>

#include "SubjectData.h"

class ASDClassification
{
public:
	ASDClassification();
	void ReadCSVFile(std::string csvFile, bool removeOutliers=false);
	void ParseTSVFiles(std::string tsvDir);
	size_t GetNumberOfSubjects();
	void CreateDisplayImageOfGaze();
	void WriteArffFile(std::string file);
	void CreateSubsetOfData();
	void CreateCollageOfImages();

private:
	std::vector<SubjectData> data;

	bool EyeMissing(std::vector<std::string>& data);
	void ParseTSVFile(SubjectData& data);
	void WriteArffGazeVectors(std::ostream& out);
};
#endif
