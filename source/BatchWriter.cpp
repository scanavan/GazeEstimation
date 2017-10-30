#include "BatchWriter.h"
#include <iostream>
#include <fstream>


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
