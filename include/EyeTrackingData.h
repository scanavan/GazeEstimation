#ifndef EYE_TRACKING_DATA_H
#define EYE_TRACKING_DATA_H
#include <string>
#include "Point.h"
#include <iostream>

class EyeTrackingData
{
public:
	EyeTrackingData(std::string incStreamData);
	friend std::ostream &operator<<(std::ostream &os, EyeTrackingData& data)
	{
		os << "Left Gaze: " << data.leftGaze << std::endl
			<< "Right Gaze: " << data.rightGaze << std::endl
			<< "Left Pupil Diameter: " << data.leftPupilDiameter << std::endl
			<< "Right Pupil Diameter: " << data.rightPupilDiameter << std::endl
			<< "Left Eye Distance: " << data.leftEyeDistance << std::endl
			<< "Right Eye Distance: " << data.rightEyeDistance << std::endl
			<< "Left Eye Position: " << data.leftEyePosition << std::endl
			<< "Right Eye Position: " << data.rightEyePosition << std::endl;

		return os;
	}

private:
	Point leftGaze;
	Point rightGaze;
	int leftPupilDiameter;
	int rightPupilDiameter;
	int leftEyeDistance;
	int rightEyeDistance;
	Point leftEyePosition;
	Point rightEyePosition;

	void ParseInputString(std::string input);
};
#endif