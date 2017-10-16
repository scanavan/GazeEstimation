#include "BatchWriter.h"
#include <iostream>
#include <fstream>


// batch file writer for the arff combination of features A-G + T-Z
void BatchWriter::arffBatchWriter()
{
	std::ofstream file;
	file.open("C:/SRITest/arff.bat");

	for (int i = 1; i < (1 << 14); ++i)
	{
		file << "java weka.filters.unsupervised.attribute.Remove -V -R ";

		if (i & (1 << 0)) file << "1,"; 
		if (i & (1 << 1)) file << "2,";
		if (i & (1 << 2)) file << "3,";
		if (i & (1 << 3)) file << "4,";
		if (i & (1 << 4)) file << "5,";
		if (i & (1 << 5)) file << "6,";
		if (i & (1 << 6)) file << "7-11,";
		if (i & (1 << 7)) file << "12-43,";
		if (i & (1 << 8)) file << "44-193,";
		if (i & (1 << 9)) file << "194-199,";
		if (i & (1 << 10)) file << "200-263,";
		if (i & (1 << 11)) file << "264-327,";
		if (i & (1 << 12)) file << "328-332,";
		if (i & (1 << 13)) file << "333-337,";
		
		file << "338 -i C:/SRITest/ABCDEFGZYXWVUT.arff -o C:/SRITest/ARFF/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "Z";
		if (i & (1 << 8)) file << "Y";
		if (i & (1 << 9)) file << "X";
		if (i & (1 << 10)) file << "W";
		if (i & (1 << 11)) file << "V";
		if (i & (1 << 12)) file << "U";
		if (i & (1 << 13)) file << "T";

		file << ".arff\n";

	}

}

void BatchWriter::selectiveARFFBatch(std::vector<int> test)
{
	std::ofstream file;
	file.open("C:/LeapAngles/arff.bat");
	bool run = false;
	for (int i = 1; i < (1 << 16); ++i)
	{
		run = false;
		for (int j = 0; j < test.size(); ++j)
		{
			if (i & (1 << test[j])) {
				run = true;
			}
		}
		if(run) {
			file << "java weka.filters.unsupervised.attribute.Remove -V -R ";

			if (i & (1 << 0)) file << "1,";
			if (i & (1 << 1)) file << "2,";
			if (i & (1 << 2)) file << "3,";
			if (i & (1 << 3)) file << "4,";
			if (i & (1 << 4)) file << "5,";
			if (i & (1 << 5)) file << "6,";
			if (i & (1 << 6)) file << "7-11,";
			if (i & (1 << 7)) file << "12-26,";
			if (i & (1 << 8)) file << "27-30,";
			if (i & (1 << 9)) file << "31-62,";
			if (i & (1 << 10)) file << "63-212,";
			if (i & (1 << 11)) file << "213-218,";
			if (i & (1 << 12)) file << "219-282,";
			if (i & (1 << 13)) file << "283-346,";
			if (i & (1 << 14)) file << "347-351,";
			if (i & (1 << 15)) file << "352-356,";

			file << "357 -i C:/Users/IASA-FRI/Desktop/ASL_Dataset/Combo.arff -o C:/LeapAngles/arff/";

			if (i & (1 << 0)) file << "A";
			if (i & (1 << 1)) file << "B";
			if (i & (1 << 2)) file << "C";
			if (i & (1 << 3)) file << "D";
			if (i & (1 << 4)) file << "E";
			if (i & (1 << 5)) file << "F";
			if (i & (1 << 6)) file << "G";
			if (i & (1 << 7)) file << "H";
			if (i & (1 << 8)) file << "I";
			if (i & (1 << 9)) file << "Z";
			if (i & (1 << 10)) file << "Y";
			if (i & (1 << 11)) file << "X";
			if (i & (1 << 12)) file << "W";
			if (i & (1 << 13)) file << "V";
			if (i & (1 << 14)) file << "U";
			if (i & (1 << 15)) file << "T";

			file << ".arff\n";
		}
			
	}

}

void BatchWriter::selectiveTestBatch(std::vector<int> test)
{
	std::ofstream file;
	file.open("C:/LeapAngles/RF.bat");
	bool run = false;
	for (int i = 1; i < (1 << 16); ++i)
	{
		run = false;
		for (int j = 0; j < test.size(); ++j)
		{
			if (i & (1 << test[j])) {
				run = true;
			}
		}
		if (run) {
			file << "java weka.classifiers.trees.RandomForest -t ";

			file << "C:/LeapAngles/arff/";

			if (i & (1 << 0)) file << "A";
			if (i & (1 << 1)) file << "B";
			if (i & (1 << 2)) file << "C";
			if (i & (1 << 3)) file << "D";
			if (i & (1 << 4)) file << "E";
			if (i & (1 << 5)) file << "F";
			if (i & (1 << 6)) file << "G";
			if (i & (1 << 7)) file << "H";
			if (i & (1 << 8)) file << "I";
			if (i & (1 << 9)) file << "Z";
			if (i & (1 << 10)) file << "Y";
			if (i & (1 << 11)) file << "X";
			if (i & (1 << 12)) file << "W";
			if (i & (1 << 13)) file << "V";
			if (i & (1 << 14)) file << "U";
			if (i & (1 << 15)) file << "T";
			file << ".arff > C:/LeapAngles/RF/";

			if (i & (1 << 0)) file << "A";
			if (i & (1 << 1)) file << "B";
			if (i & (1 << 2)) file << "C";
			if (i & (1 << 3)) file << "D";
			if (i & (1 << 4)) file << "E";
			if (i & (1 << 5)) file << "F";
			if (i & (1 << 6)) file << "G";
			if (i & (1 << 7)) file << "H";
			if (i & (1 << 8)) file << "I";
			if (i & (1 << 9)) file << "Z";
			if (i & (1 << 10)) file << "Y";
			if (i & (1 << 11)) file << "X";
			if (i & (1 << 12)) file << "W";
			if (i & (1 << 13)) file << "V";
			if (i & (1 << 14)) file << "U";
			if (i & (1 << 15)) file << "T";

			file << ".txt\n";
		}

	}
}

// batch file writer for random forest tests of features A-H + T-Z
void BatchWriter::RFWriter()
{
	std::ofstream file;
	file.open("C:/SRITest/RF_ASL.bat");

	for (int i = 1; i < (1 << 15); ++i)
	{
		file << "java weka.classifiers.trees.RandomForest -t ";

		file << "C:/ASL_ARFF/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "Z";
		if (i & (1 << 9)) file << "Y";
		if (i & (1 << 10)) file << "X";
		if (i & (1 << 11)) file << "W";
		if (i & (1 << 12)) file << "V";
		if (i & (1 << 13)) file << "U";
		if (i & (1 << 14)) file << "T";
		file << ".arff > C:/RF_ASL/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "Z";
		if (i & (1 << 9)) file << "Y";
		if (i & (1 << 10)) file << "X";
		if (i & (1 << 11)) file << "W";
		if (i & (1 << 12)) file << "V";
		if (i & (1 << 13)) file << "U";
		if (i & (1 << 14)) file << "T";

		file << ".txt\n";
	}

}

// batch file writer for arff files for all the leap features
void BatchWriter::arffLeapBatchWriter() {
	std::ofstream file;
	file.open("C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/BatchFiles/createARFF.bat");

	for (int i = 1; i < (1 << 9); ++i)
	{
		file << "java weka.filters.unsupervised.attribute.Remove -V -R ";

		if (i & (1 << 0)) file << "1,";
		if (i & (1 << 1)) file << "2,";
		if (i & (1 << 2)) file << "3,";
		if (i & (1 << 3)) file << "4,";
		if (i & (1 << 4)) file << "5,";
		if (i & (1 << 5)) file << "6,";
		if (i & (1 << 6)) file << "7-11,";
		if (i & (1 << 7)) file << "12-16,";
		if (i & (1 << 8)) file << "17-21,";

		file << "22 -i C:/Users/IASA-FRI/Desktop/SRI/test.arff -o C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/AllLeapFeatures/arffFiles/Leap/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";

		file << ".arff\n";

	}
}

// batch file writer for random forest tests of all the leap features
void BatchWriter::LeapRFWriter()
{
	std::ofstream file;
	file.open("C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/BatchFiles/RandomForest.bat");

	for (int i = 1; i < (1 << 9); ++i)
	{
		file << "java weka.classifiers.trees.RandomForest -t ";

		file << "C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/AllLeapFeatures/arffFiles/Leap/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";

		file << ".arff > C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/AllLeapFeatures/RandomForest/Leap/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";

		file << ".txt\n";
	}

}

// batch file writer for LibSVM tests of all leap features
void BatchWriter::LeapLibSVMWriter() {
	std::ofstream file;
	file.open("C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/BatchFiles/LibSVM.bat");

	for (int i = 1; i < (1 << 9); ++i)
	{
		file << "java weka.classifiers.functions.LibSVM -t ";

		file << "C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/AllLeapFeatures/arffFiles/Leap/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";

		file << ".arff > C:/Users/IASA-FRI/Desktop/SRI/GestureRecognition/Data/AllLeapFeatures/LibSVM/Leap/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";

		file << ".txt\n";
	}
}

// batch file writer to create the directory structure for a dataset
void BatchWriter::DirStruct(std::string home, int subjects) {
	std::string tmp1, tmp2;
	std::ofstream file;
	file.open("createDir.bat");
	
	file << "if not exist \"" << home << "\" mkdir \"" << home << "\"\n";

	for (int i = 1; i <= subjects; ++i)
	{
		if (i < 10) {
			tmp1 = home + "/P0" + std::to_string(i);
		}
		else {
			tmp1 = home + "/P" + std::to_string(i);
		}
		file << "if not exist \"" << tmp1 << "\" mkdir \"" << tmp1 << "\"\n";
		for (int j = 1; j <= 24; ++j)
		{
			if (j < 10) {
				tmp2 = tmp1 + "/G0" + std::to_string(j);
			}
			else {
				tmp2 = tmp1 + "/G" + std::to_string(j);
			}
			file << "if not exist \"" << tmp2 << "\" mkdir \"" << tmp2 << "\"\n";
		}
	}
}