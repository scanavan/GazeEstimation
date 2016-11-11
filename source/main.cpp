#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/asio/read.hpp>
#include "EyeTrackingData.h"
#include "ASDClassification.h"

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
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end;

	boost::asio::ip::tcp::socket socket(io_service);
	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error && endpoint_iterator != end)
	{
		socket.close();
		socket.connect(*endpoint_iterator++, error);
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
	ASDClassification classify;
	std::cout << "testing" << std::endl;
	classify.ReadCSVFile("./TestData/SubjectData.csv");
	classify.ParseTSVFiles("./TestData/tsvData/");
	classify.WriteArffFile("./TestData/asd_mean_sd.arff", "./TestData/out.txt");
	for (size_t i = 0; i < classify.GetNumberOfSubjects(); ++i)
	{
		classify.CreateDisplayImageOfGaze(i);
	}
}