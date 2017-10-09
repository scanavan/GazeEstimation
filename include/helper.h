#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/lexical_cast.hpp"
using namespace boost::posix_time;
using namespace boost::gregorian;

// Calculates the time in which a frame happened.
long getTimeInMs( std::string &time ){

	int minutes_frame(boost::lexical_cast<int>(time.substr(3,2)));
	int seconds_frame(boost::lexical_cast<int>(time.substr(6,2)));
	int millisec_frame(boost::lexical_cast<int>(time.substr(9,3)));

	date d(2002, Feb, 1);
	ptime t(d, hours(0) +  minutes(minutes_frame) + seconds(seconds_frame) + millisec(millisec_frame));
	time_duration t_duration(t.time_of_day());
	return t_duration.total_milliseconds();
}

// Calculates the time duration between two frames. 
long calculate_frame_duration(std::string& time1, std::string& time2) {

	int hours1 = boost::lexical_cast<int>(time1.substr(0,2));
	int minutes1 = boost::lexical_cast<int>(time1.substr(3,2));
	int seconds1 = boost::lexical_cast<int>(time1.substr(6,2));
	int millisec1 = boost::lexical_cast<int>(time1.substr(9,3));

	int hours2 = boost::lexical_cast<int>(time2.substr(0,2));
	int minutes2 = boost::lexical_cast<int>(time2.substr(3,2));
	int seconds2 = boost::lexical_cast<int>(time2.substr(6,2));
	int millisec2 = boost::lexical_cast<int>(time2.substr(9,3));

	date d(2002, Feb, 1);
	ptime t1(d, hours(hours1) + minutes(minutes1) + seconds(seconds1) + millisec(millisec1));
	ptime t2(d, hours(hours2) + minutes(minutes2) + seconds(seconds2) + millisec(millisec2));
	time_duration td = t2 - t1;
	return td.seconds();
}

// Function is a helper function to track that down possible corrupted data in TSV files. 
std::pair<int, int> findNegatives(std::vector<Vector2D> vector1){
	return std::pair<int, int>(count_if(vector1.begin(),vector1.end(), [](const Vector2D v){ if(v.x < 0) { return true; } else { return false; }}),
                                count_if(vector1.begin(),vector1.end(), [](const Vector2D v){ if(v.y < 0){ return true; } else { return false;}}));
}

// Function returns a vector of 2DVectors that simulates the screen as a 3x3 grid and computes the average X and Y gaze points at that moment
std::vector<Vector2D> screenGridAverages(std::vector<Vector2D> &v){

        std::vector<Vector2D>::iterator itr;
        std::vector<Vector2D> v2(9);

        int arr_size[9] = {0};

        int i(0);

        for(itr = v.begin(); itr != v.end(); ++itr, ++i){

                //Bottom Left fixed
         	if((v[i].x > -640 && v[i].x < -214) && (v[i].y > -512 && v[i].y < -171 )){
                	v2[0].x = v[i].x + v2[0].x;
                	v2[0].y = v[i].y + v2[0].y;
                	arr_size[0] += 1;
                //Left Middle
       		} else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > -171  && v[i].y < 171)){
                	v2[1].x = v[i].x + v2[1].x;
                	v2[1].y = v[i].y + v2[1].y;
                	arr_size[1] += 1;
                //Left Top
        	} else if((v[i].x > -640 && v[i].x < -214) && (v[i].y > 171  && v[i].y < 512)){
                	v2[2].x = v[i].x + v2[2].x;
                	v2[2].y = v[i].y + v2[2].y;
                	arr_size[2] += 1;
                //Middle Bottom
        	} else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > -512  && v[i].y < -171)){
                	v2[3].x = v[i].x + v2[3].x;
                	v2[3].y = v[i].y + v2[3].y;
                	arr_size[3] += 1;
                //Middle Middle
        	} else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > -171  && v[i].y < 171)){
                	v2[4].x = v[i].x + v2[4].x;
                	v2[4].y = v[i].y + v2[4].y;
                	arr_size[4] += 1;
                //Middle Top
        	} else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > 171  && v[i].y < 512)){
                	v2[5].x = v[i].x + v2[5].x;
                	v2[5].y = v[i].y + v2[5].y;
                	arr_size[5] += 1;
                //Right bottom
       		 } else if((v[i].x > 214 && v[i].x < 640 ) && (v[i].y > -512  && v[i].y < -171)){
                	v2[6].x = v[i].x + v2[6].x;
               		v2[6].y = v[i].y + v2[6].y;
                	arr_size[6] += 1;
                //Right Middle
       		 } else if((v[i].x > 214 && v[i].x < 640) && (v[i].y > -171  && v[i].y < 171)){
                	v2[7].x = v[i].x + v2[7].x;
                	v2[7].y = v[i].y + v2[7].y;
                	arr_size[7] += 1;
                //Right Top
        	} else if((v[i].x > 214 && v[i].x < 640) && (v[i].y > 171  && v[i].y < 512)){
                	v2[8].x = v[i].x + v2[8].x;
                	v2[8].y = v[i].y + v2[8].y;
                	arr_size[8] += 1;
        	}
        }

	// Computing the average. 
        for(int i = 0; i < v2.size(); i++){

            if(arr_size[i] == 0){
		v2[i].x = 0;
		v2[i].y = 0;
		continue;
            }
                v2[i].x = v2[i].x / arr_size[i];
                v2[i].y = v2[i].y / arr_size[i];
        }

        return v2;
}

// Function returns a vector with the frequency of occurance of each grid.
std::vector<int> findFreqency(std::vector<Vector2D> &v){
	   
	std::vector<int> arr_size(9,0);
	std::vector<Vector2D>::iterator itr;
	int i(0);

	for(itr = v.begin(); itr != v.end(); ++itr, ++i){
	
	         //Bottom Left
	         if((v[i].x > -640 && v[i].x < -214) && (v[i].y > -512 && v[i].y < -171 )){
	                arr_size[0] += 1;
	         //Left Middle
	        } else if((v[i].x > -640 && v[i].x < -214) && (v[i].y > -171  && v[i].y < 171)){
	                arr_size[1] += 1;
	         //Left Top
	        } else if((v[i].x > -640 && v[i].x < -214) && (v[i].y > 171  && v[i].y < 512)){
	                arr_size[2] += 1;
	        //Middle Bottom
	        } else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > -512  && v[i].y < -171)){
	                arr_size[3] += 1;
	        //Middle Middle
	        } else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > -171  && v[i].y < 171)){
	                arr_size[4] += 1;
	        //Middle Top
	        } else if((v[i].x > -214 && v[i].x < 214) && (v[i].y > 171  && v[i].y < 512)){
	                arr_size[5] += 1;
	        //Right bottom
	        } else if((v[i].x > 214 && v[i].x < 640 ) && (v[i].y > -512  && v[i].y < -171)){
	                arr_size[6] += 1;
	        //Right Middle
	        } else if((v[i].x > 214 && v[i].x < 640) && (v[i].y > -171  && v[i].y < 171)){
	                arr_size[7] += 1;
	        //Right Top
	        } else if((v[i].x > 214 && v[i].x < 640) && (v[i].y > 171  && v[i].y < 512)){
	                arr_size[8] += 1;
	        }
	}
	return arr_size;
}

// Function calculates the average distance from gaze to center of the screen.
float avgToCentroid(std::vector<Vector2D>& v)
{
        float running_sum(0);
        for(const auto & point : v)
        {
                running_sum += std::sqrt(std::pow(point.x, 2) + std::pow(point.y, 2));
        }
        return (running_sum/v.size());
}
