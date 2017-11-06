#include "BatchWriter.h"
#include <iostream>
#include <fstream>
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/trim.hpp"
#include <boost/range/algorithm/count.hpp>

// batch file writer for the arff combination of features A-G + T-Z
void BatchWriter::arffBatchWriter()
{
	std::ofstream file;
	file.open("./ALLTest/arff.bat");

	for (int i = 1; i < (1 << 21); ++i)
	{
		file << "@java weka.filters.unsupervised.attribute.Remove -V -R ";

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

	for (int i = 1; i < (1 << 21); ++i)
	{
		file << "@java weka.classifiers.trees.RandomForest -t ";

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

void BatchWriter::splitArffWritter(int number_of_machines)
{
	std::ofstream output_file;
	std::ifstream input_file;
	std::string line = "";
	std::string original_batch_file = "./ALLTest/arff.bat";
	std::string destination_file;

	input_file.open(original_batch_file);

	int line_number_original = 0;

	// We need to figure out the number of line on the original file so we can can get the amount,
	// of iterations per file
	while (std::getline(input_file, line))
	{
		++line_number_original;
	}
	std::cout << "Total: " << line_number_original << std::endl;
	input_file.close();

	// Number of iterations per file
	int number_of_lines_per_file = line_number_original/number_of_machines;
	std::cout << "Commands per file: " << number_of_lines_per_file << std::endl;
	// Need to open file one more time to start copying.
	input_file.open(original_batch_file);

	// We will create as many files as machines are.
	for(int i = 1; i <= number_of_machines; ++i  )
	{
		// Calculating the starting point of the loop.
		int starting_point = (number_of_lines_per_file * i) - number_of_lines_per_file;

			// we need unique file names
			destination_file = "./ALLTest/arff_devided_" + std::to_string(i) + ".bat";

			// Open output file
			output_file.open(destination_file);
			// now that the file is where it's supposed to be, we can start copying.
			int line_number = 0;
			for (int j = starting_point; j <= (starting_point + number_of_lines_per_file); ++j)
			{
				// Read line
				std::getline(input_file, line);
				// Put it in destination
				output_file << line << std::endl;
				++line_number;

			}
			line_number = 0;
			// Close output file, we need to open a new one.
			output_file.close();
	}
	input_file.close();
	BatchWriter::splitRFWritter(number_of_machines);
}

void BatchWriter::splitRFWritter(int number_of_machines)
{
	std::cout << "RF Writter starts" << std::endl;
	std::ofstream output_file;
	std::ifstream input_file;
	std::string line = "";
	std::string original_batch_file = "./ALLTest/ALLRandomForest.bat";
	std::string destination_file;

	input_file.open(original_batch_file);

	int line_number_original = 0;

	// We need to figure out the number of line on the original file so we can can get the amount,
	// of iterations per file
	while (std::getline(input_file, line))
	{
		++line_number_original;
	}
	std::cout << "Total: " << line_number_original << std::endl;
	input_file.close();

	// Number of iterations per file
	int number_of_lines_per_file = line_number_original/number_of_machines;
	std::cout << "Commands per file: " << number_of_lines_per_file << std::endl;
	// Need to open file one more time to start copying.
	input_file.open(original_batch_file);

	// We will create as many files as machines are.
	for(int i = 1; i <= number_of_machines; ++i  )
	{
		// Calculating the starting point of the loop.
		int starting_point = (number_of_lines_per_file * i) - number_of_lines_per_file;

			// we need unique file names
			destination_file = "./ALLTest/ALLRandomForest_devided_" + std::to_string(i) + ".bat";

			// Open output file
			output_file.open(destination_file);
			// now that the file is where it's supposed to be, we can start copying.
			int line_number = 0;
			for (int j = starting_point; j <= (starting_point + number_of_lines_per_file); ++j)
			{
				// Read line
				std::getline(input_file, line);
				// Put it in destination
				output_file << line << std::endl;
				++line_number;

			}
			line_number = 0;
			// Close output file, we need to open a new one.
			output_file.close();
	}
	input_file.close();
}

void BatchWriter::bestAndWorstCombination()
{
	std::ifstream file_input;
	std::string path = "./ALLTest/RFWRITER/";
	std::string specific_file = "";
	std::string full_path = "";

	std::pair<std::string, double> best;
	float global_max = -1.f;
	float global_min = 100.f;
	std::string path_to_best, path_to_worst;
	for (int i = 1; i < (1 << 21); ++i)
	{
		int lineCount(0);
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
		full_path.append(".txt");
		file_input.open(full_path);

		if(!file_input.is_open())
		{
			file_input.close();
			continue;
		}


		std::string line;

		// Find our label row
		while (std::getline(file_input, line))
		{
			++lineCount;
			if(lineCount==45)
				break;
		}
		// split line
		if (line.length() > 0)
		{
			line = line.substr(57, 8);

			//remove leading and traling whitespace
			boost::algorithm::trim_left(line);
			boost::algorithm::trim_right(line);
			float local_max = boost::lexical_cast<float>(line);
			float local_min = boost::lexical_cast<float>(line);

			if (local_max > global_max)
			{
				global_max = local_max;
				path_to_best = full_path;
			}
			if ( local_min < global_min)
			{
				global_min = local_min;
				path_to_worst = full_path;
			}
		}
		else
		{
			std::cout << "Line 45 in " << full_path << " had a length of 0." << std::endl;
		}
		file_input.close();
	}
	// Done looping through every .txt file
	std::cout << "Best combination at: " << path_to_best << " with " << global_max << " %" <<std::endl;
	std::cout << "Worst combination at: " << path_to_worst << " with " << global_min << " %" <<std::endl;
	BatchWriter::getNFeatures(global_max, global_min);
}

void BatchWriter::getNFeatures(float best_accuracy, float worst_accuracy)
{
	  // File pointers for reading/writing
		std::ifstream file_input;
		std::ofstream output_file_best;
		std::ofstream output_file_worst;

		// Initializing variables to be used for path generation
		std::string path = "./ALLTest/RFWRITER/";
		std::string outputBestPath = "./ALLTest/RESULTS/best_accuracies.txt";
		std::string outputWorstPath = "./ALLTest/RESULTS/worst_accuracies.txt";
		std::string specific_file = "";
		std::string full_path = "";
		std::string path_to_best, path_to_worst;


		output_file_best.open(outputBestPath);
		output_file_best << "This shows all the combinations that yielded to: " << best_accuracy << " %" << std::endl << std::endl;

		output_file_worst.open(outputWorstPath);
		output_file_worst << "This shows all the combinations that yielded to: " << worst_accuracy << " %" << std::endl << std::endl;

		int equal_counter_max(0);
		int equal_counter_min(0);

		// Need 2 arrays to keep track of occurance of our Features.
		int feature_occurarance_max[22] = {0};
		int feature_occurarance_min[22] = {0};

		// This will loop 2 ^ 21 times and find all the possible paths.
		for (int i = 1; i < (1 << 21); ++i)
		{
			int lineCount(0);
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

			// Building the specifc path to the file.
			full_path.append(path);
			full_path.append(specific_file);
			full_path.append(".txt");
			file_input.open(full_path);

			// If file not there, continue to next iteration.
			if(!file_input.is_open())
			{
				file_input.close();
				continue;
			}


			std::string line;

			// Move pointer to line 45 (The accuracy is always at this line)
			while (std::getline(file_input, line))
			{
				++lineCount;
				if(lineCount == 45)
					break;
			}

			// split line
			if (line.length() > 0)
			{
				line = line.substr(57, 8);

				// remove leading and traling whitespace
				boost::algorithm::trim_left(line);
				boost::algorithm::trim_right(line);
				float local_max = boost::lexical_cast<float>(line);
				float local_min = boost::lexical_cast<float>(line);

				// If found matches best, we want to know which features.
				if (local_max == best_accuracy)
				{
					path_to_best = full_path;

					// Intended not to put next line chracter, we will put which features let to this
					output_file_best << ++equal_counter_max << " Located max at: " << path_to_best << "with features: ";

					char letter = 'A';
					for(int i = 0; i < 22; ++i, ++letter)
					{
						int occurance = boost::count(specific_file,letter);
						feature_occurarance_max[i] += occurance;

						if (occurance > 0)
						{
							output_file_best << letter;
						}
					}
					// When for loop is done it means that we added all the features we used to the file.
					output_file_best << std::endl;
				}

				// If found matchest worst, we want to know which features
				if ( local_min == worst_accuracy)
				{
					path_to_worst = full_path;

					output_file_worst << ++equal_counter_min << " Located min at: " << path_to_best << "with features: ";

					char letter = 'A';
					for(int i = 0; i < 22; ++i, ++letter)
					{
						int occurance = boost::count(specific_file,letter);
						feature_occurarance_min[i] += occurance;

						if(occurance > 0)
						{
							output_file_worst << letter;
						}
					}
					output_file_worst << std::endl;
				}
			}
			file_input.close();
		}

		// Just for a little formatting.
		output_file_best << std::endl;

		char letter = 'A';
		for(int i = 0; i < 22; ++i, ++letter)
		{
			output_file_best << "feature " << letter << " occured a total of "  << feature_occurarance_max[i] << " times in our best features calculations" << std::endl;
		}

		output_file_worst << std::endl;

		letter = 'A';
		for(int i = 0; i < 22; ++i, ++letter)
		{
			output_file_worst << "feature " << letter << " occured a total of "  << feature_occurarance_min[i] << " times in our worst features calculations" << std::endl;
		}

		output_file_best.close();
		output_file_worst.close();
}
