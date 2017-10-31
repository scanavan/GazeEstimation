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
};
#endif
