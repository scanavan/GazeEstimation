#include "NDARData.h"

NDARData::NDARData(std::string tsvDirectory)
{
	//get all of the tsv files in the directory
	boost::filesystem::path tsvPath(tsvDirectory);
	boost::filesystem::directory_iterator tsvEnd;
	for (boost::filesystem::directory_iterator it(tsvDirectory); it != tsvEnd; ++it)
	{
		if (boost::filesystem::is_regular_file(it->path()) && it->path().extension() == ".tsv")
		{
			tsvFiles.emplace_back(it->path().string());
		}
	}
}