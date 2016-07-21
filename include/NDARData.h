#ifndef NDAR_DATA_H
#define NDAR_DATA_H
#include <string>
#include <vector>
#include "boost/filesystem.hpp"

class NDARData
{
public:
	NDARData(std::string tsvDirectory);

protected:
	std::vector<std::string> tsvFiles;
};
#endif