#ifndef BATCHWRITER_H
#define BATCHWRITER_H

#include <string>
#include <vector>

class BatchWriter
{
public:
	BatchWriter() {}
	void arffBatchWriter();
	void RFWriter();
	void arffLeapBatchWriter();
	void LeapRFWriter();
	void LeapLibSVMWriter();
	void DirStruct(std::string home, int subjects);
	void selectiveARFFBatch(std::vector<int> test);
	void selectiveTestBatch(std::vector<int> test);
};
#endif