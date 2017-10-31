#include "BatchWriter.h"
#include <iostream>
#include <fstream>
#include "boost/lexical_cast.hpp"


// batch file writer for the arff combination of features A-G + T-Z
void BatchWriter::arffBatchWriter()
{
	std::ofstream file;
	file.open("./ALLTest/arff.bat");

	for (int i = 1; i < (1 << 22); ++i)
	{
		file << "start java weka.filters.unsupervised.attribute.Remove -V -R ";

		if (i & (1 << 0)) file << "1,";
		if (i & (1 << 1)) file << "2,";
		if (i & (1 << 2)) file << "3,";
		if (i & (1 << 3)) file << "4,";
		if (i & (1 << 4)) file << "5,";
		if (i & (1 << 5)) file << "6,";
		if (i & (1 << 6)) file << "7,";
		if (i & (1 << 7)) file << "8,";
		if (i & (1 << 8)) file << "9,";
		if (i & (1 << 9)) file << "10,";
		if (i & (1 << 10)) file << "11,";
		if (i & (1 << 11)) file << "12,";
		if (i & (1 << 12)) file << "13,";
		if (i & (1 << 13)) file << "14,";
		if (i & (1 << 14)) file << "15,";
		if (i & (1 << 15)) file << "16,";
		if (i & (1 << 16)) file << "17,";
		if (i & (1 << 17)) file << "18,";
		if (i & (1 << 18)) file << "19,";
		if (i & (1 << 19)) file << "20,";
		if (i & (1 << 20)) file << "21,";

		file << "22 -i ./output/Allfeatures.arff -o ./ALLTest/ARFF/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";
		if (i & (1 << 9)) file << "J";
		if (i & (1 << 10)) file << "K";
		if (i & (1 << 11)) file << "L";
		if (i & (1 << 12)) file << "M";
		if (i & (1 << 13)) file << "N";
		if (i & (1 << 14)) file << "O";
		if (i & (1 << 15)) file << "P";
		if (i & (1 << 16)) file << "Q";
		if (i & (1 << 17)) file << "R";
		if (i & (1 << 18)) file << "S";
		if (i & (1 << 19)) file << "T";
		if (i & (1 << 20)) file << "U";
		file << "V";
		file << ".arff\n";

	}
	file.close();
}


// batch file writer for random forest tests of features A-H + T-Z
void BatchWriter::RFWriter()
{
	std::ofstream file;
	file.open("./ALLTest/ALLRandomForest.bat");

	for (int i = 1; i < (1 << 22); ++i)
	{
		file << "start java weka.classifiers.trees.RandomForest -t ";

		file << "./ALLTest/ARFF/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";
		if (i & (1 << 9)) file << "J";
		if (i & (1 << 10)) file << "K";
		if (i & (1 << 11)) file << "L";
		if (i & (1 << 12)) file << "M";
		if (i & (1 << 13)) file << "N";
		if (i & (1 << 14)) file << "O";
		if (i & (1 << 15)) file << "P";
		if (i & (1 << 16)) file << "Q";
		if (i & (1 << 17)) file << "R";
		if (i & (1 << 18)) file << "S";
		if (i & (1 << 19)) file << "T";
		if (i & (1 << 20)) file << "U";
		 file << "V";

		file << ".arff > ./ALLTest/RFWRITER/";

		if (i & (1 << 0)) file << "A";
		if (i & (1 << 1)) file << "B";
		if (i & (1 << 2)) file << "C";
		if (i & (1 << 3)) file << "D";
		if (i & (1 << 4)) file << "E";
		if (i & (1 << 5)) file << "F";
		if (i & (1 << 6)) file << "G";
		if (i & (1 << 7)) file << "H";
		if (i & (1 << 8)) file << "I";
		if (i & (1 << 9)) file << "J";
		if (i & (1 << 10)) file << "K";
		if (i & (1 << 11)) file << "L";
		if (i & (1 << 12)) file << "M";
		if (i & (1 << 13)) file << "N";
		if (i & (1 << 14)) file << "O";
		if (i & (1 << 15)) file << "P";
		if (i & (1 << 16)) file << "Q";
		if (i & (1 << 17)) file << "R";
		if (i & (1 << 18)) file << "S";
		if (i & (1 << 19)) file << "T";
		if (i & (1 << 20)) file << "U";
		file << "V";

		file << ".txt\n";
	}
	file.close();
}

std::pair <std::string, double> BatchWriter::bestCombination()
{
	std::ifstream file_input;
	std::string path = "./ALLTest/RFWRITER/";
	std::string specific_file = "";
	std::string full_path = "";

	std::pair<std::string, double> best;
	double global_max = -1.0;
	std::string path_to_best;

	for (int i = 1; i < (1 << 22); ++i)
	{
		specific_file = "";
		full_path = "";

		if (i & (1 << 0)) specific_file.append("A");
		if (i & (1 << 1)) specific_file.append("B");
		if (i & (1 << 2)) specific_file.append("C");
		if (i & (1 << 3)) specific_file.append("D");
		if (i & (1 << 4)) specific_file.append("E");
		if (i & (1 << 5)) specific_file.append("F");
		if (i & (1 << 6)) specific_file.append("G");
		if (i & (1 << 7)) specific_file.append("H");
		if (i & (1 << 8)) specific_file.append("I");
		if (i & (1 << 9)) specific_file.append("J");
		if (i & (1 << 10)) specific_file.append("K");
		if (i & (1 << 11)) specific_file.append("L");
		if (i & (1 << 12)) specific_file.append("M");
		if (i & (1 << 13)) specific_file.append("N");
		if (i & (1 << 14)) specific_file.append("O");
		if (i & (1 << 15)) specific_file.append("P");
		if (i & (1 << 16)) specific_file.append("Q");
		if (i & (1 << 17)) specific_file.append("R");
		if (i & (1 << 18)) specific_file.append("S");
		if (i & (1 << 19)) specific_file.append("T");
		if (i & (1 << 20)) specific_file.append("U");
		specific_file.append("V");

		full_path.append(path);
		full_path.append(specific_file);

		file_input.open(full_path);
		std::string line;

		std::getline(file_input, line);

		// Find our label row
		while (std::getline(file_input, line))
		{
			if(line.find("Correctly Classified Instances") != std::string::npos)
				break;
		}
		// split at 56 to 66
		line = line.substr(56,10);
		double local_max = boost::lexical_cast<double>(line);
		if(local_max > global_max)
		{
			global_max = local_max;
			path_to_best = full_path;
		}
	}

	// Done looping through every .txt file
	return std::pair<std::string, double>(path_to_best,global_max);
}
