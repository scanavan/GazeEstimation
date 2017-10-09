#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/asio/read.hpp>
#include "EyeTrackingData.h"
#include "ASDClassification.h"
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
	auto start = std::chrono::system_clock::now();	
	ASDClassification classify;
	classify.ReadCSVFile("./GazeData/SubjectData.csv");
	auto start_parse = std::chrono::system_clock::now();
	classify.ParseTSVFiles("./GazeData/tsvData/");
	auto end_parse = std::chrono::system_clock::now();
	classify.WriteArffFile("./output/VelocityTest.arff");
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds_parse = end_parse-start_parse;
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout<< "Overall program took: " << elapsed_seconds.count() << std::endl;
	std::cout << "Program used to take: 275s" << std::endl;

	std::cout << "TSV Files took: " << elapsed_seconds_parse.count() <<std::endl;
	std::cout << "TSV Files used to take: 273s" << std::endl;
//	classify.CreateDisplayImageOfGaze();
}
