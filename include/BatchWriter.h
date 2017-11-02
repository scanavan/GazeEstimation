#ifndef BATCHWRITER_H
#define BATCHWRITER_H
#include <utility>
#include <string>
class BatchWriter
{
public:
	BatchWriter() {}
	void arffBatchWriter();
	void RFWriter();
	std::pair<std::string, double> bestCombination();
	void splitArffWritter(int number_of_machines);
	void splitRFWritter(int number_of_machines);
};
#endif
