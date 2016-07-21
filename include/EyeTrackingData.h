#ifndef EYE_TRACKING_DATA_H
#define EYE_TRACKING_DATA_H
#include <string>

struct Point
{
	Point(float _x, float _y) : x(_x), y(_y) {}
	Point() : x(0.f), y(0.f) {}
	float x;
	float y;
	friend std::ostream &operator<<(std::ostream& os, Point& point)
	{
		os << "(" << point.x << ", " << point.y << ")";
		return os;
	}
};
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
	float leftPupilDiameter;
	float rightPupilDiameter;
	float leftEyeDistance;
	float rightEyeDistance;
	Point leftEyePosition;
	Point rightEyePosition;

	void ParseInputString(std::string input);
};
#endif