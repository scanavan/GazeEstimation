#include "EyeTrackingData.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/all.hpp>
#include <vector>
#include <iostream>

EyeTrackingData::EyeTrackingData(std::string incStreamData)
{
	try
	{
		ParseInputString(incStreamData);
	}
	catch (const boost::bad_lexical_cast& /*e*/)
	{
		//boost can throw an error if the data from iMotions is not 100% correct.
		//this catch just ignores that throw and continues on, otherwise it would exit the program
		//the exception is happening after the class is populated
	}
}
void EyeTrackingData::ParseInputString(std::string input)
{
	std::vector<std::string> splitStringVec;
	boost::split(splitStringVec, input, boost::is_any_of(";"));
	
	for (unsigned i = 6; i < splitStringVec.size(); ++i)
	{
		//get ride of trailing whitespace and/or newline
		boost::algorithm::trim_right(splitStringVec.at(i));
		//check string position and populate correct parameter
		switch (i)
		{
		case 6:
			leftGaze.x = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 7:
			leftGaze.y = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 8:
			rightGaze.x = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 9:
			rightGaze.y = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 10:
			leftPupilDiameter = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 11:
			rightPupilDiameter = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 12:
			leftEyeDistance = boost::lexical_cast<int>(splitStringVec.at(i));;
			break;
		case 13:
			rightEyeDistance = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 14:
			leftEyePosition.x = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 15:
			leftEyePosition.y = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 16:
			rightEyePosition.x = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		case 17:
			rightEyePosition.y = boost::lexical_cast<int>(splitStringVec.at(i));
			break;
		}
	}
	
}