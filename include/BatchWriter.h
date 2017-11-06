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
	void bestAndWorstCombination();
	void splitArffWritter(int number_of_machines);
	void splitRFWritter(int number_of_machines);
	void getNFeatures(float best, float worst);
};
#endif
