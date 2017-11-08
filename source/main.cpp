#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/asio/read.hpp>
#include "EyeTrackingData.h"
#include "ASDClassification.h"
#include "BatchWriter.h"
#include <time.h>
#include <stdio.h>
#include <chrono>
//run either real time with iMotions or load NDAR data to analyze
void RealTime();
void NDAR();

int main()
{
	try
	{
		//RealTime();
		NDAR();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
void RealTime()
{
	boost::asio::io_service io_service;

	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), "localhost", std::to_string(8088));
	boost::asio::ip::tcp::resolver::iterator endVector2D_iterator = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end;

	boost::asio::ip::tcp::socket socket(io_service);
	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error && endVector2D_iterator != end)
	{
		socket.close();
		socket.connect(*endVector2D_iterator++, error);
	}
	if (error)
	{
		throw boost::system::system_error(error);
	}
	std::vector<EyeTrackingData> eyeTrackingDataVec;
	for (;;)
	{
		if (socket.available() > 0)
		{
			std::vector<char> buf(socket.available());
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
			{
				break;
			}
			else if (error)
			{
				throw boost::system::system_error(error);
			}
			eyeTrackingDataVec.emplace_back(EyeTrackingData(std::string(buf.begin(), buf.end())));
			std::cout << eyeTrackingDataVec.at(0) << std::endl;
			eyeTrackingDataVec.clear();
		}
	}
}
void NDAR()
{
	char input;
	ASDClassification classify;
	std::cout << "Do you want to read CSV and TSV files? (y/n): ";
	std::cin >> input;
	if (input == 'y')
	{
		classify.ReadCSVFile("./GazeData/SubjectData.csv");
		classify.ParseTSVFiles("./GazeData/tsvData/");

		// Ask the user if they want to create a subset
		std::cout << "Do you want to make a subset of all of the data? (y/n): ";
		std::cin >> input;
		if (input == 'y')
		{
			classify.CreateSubsetOfData();
		}


		classify.WriteArffFile("./output/AllFeatures.arff");
	}

	BatchWriter writer;
	// Ask the user if they want to create batch file
	std::cout << "Do you want to make the batch/ssh files? (y/n): ";
	std::cin >> input;
	if(input == 'y'){
		std::cout << "Writting ARFF and RF writer... " << std::endl;
		writer.arffBatchWriter();
		writer.RFWriter();
	}

	// Ask the user if they want to separate files
	std::cout << "Do you want to separate the batch/ssh files? (y/n): ";
	std::cin >> input;
	if(input == 'y'){
		std::cout << "Please enter the number of machines to split on:";
		int number;
		std::cin >> number;
		std::cout << "Separating Files... " << std::endl;
		writer.splitArffWritter(number);
	}

	// Ask the user if they want to looking for the write combination
	std::cout << "Do you want to calculate the best and worst accuracies? (y/n): ";
	std::cin >> input;
	if(input == 'y')
	{
		std::cout << "Calculating the best and worst accuracies... " << std::endl;
		writer.bestAndWorstCombination();
	}
	// Ask The user if they want to display/create the images.
	std::cout << "Do you want to display Images? (y/n): ";
	std::cin >> input;
	if(input == 'y')
	{
		classify.CreateDisplayImageOfGaze();
	}

	std::cout << "Do you want to create a collage with 4 images? You can only do this if you saved 4 images? (y/n): ";
	std::cin >> input;
	if(input == 'y')
	{
		classify.CreateCollageOfImages();
	}
}
