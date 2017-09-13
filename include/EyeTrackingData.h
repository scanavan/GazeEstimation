#ifndef EYE_TRACKING_DATA_H
#define EYE_TRACKING_DATA_H
#include <string>
#include "Vector2D.h"
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
	Vector2D leftGaze;
	Vector2D rightGaze;
	int leftPupilDiameter;
	int rightPupilDiameter;
	int leftEyeDistance;
	int rightEyeDistance;
	Vector2D leftEyePosition;
	Vector2D rightEyePosition;

	void ParseInputString(std::string input);
};
#endif