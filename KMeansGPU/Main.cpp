#include "Parser.h"
#include "DataFactory.h"
#include "KMeansCPU.h"
#include "KMeansGPU.h"
#include <vector>
#include <iostream>

using namespace KMG;
using namespace std;

int main(int argc, char** argv)
{
	DataFactory df;

	string filename("KDDCUP04Bio Small.txt");
	// string filename("Temp2.txt");
	switch (argc)
	{
	case 0:
		cerr << "argc is not expected to have 0 value" << endl; exit(EXIT_FAILURE);
	case 1:
		cout << "Using default dataset : " << filename << endl; break; 
	case 2:
		filename = argv[1];
		cout << "Using dataset : " << filename << endl; break; 
	default:
		cerr << "Incorrect Number of arguments." << endl;
	}

	/* Beginning of the program */
	cout << "Started K Means Clustering.." << endl;

	/* Parse and feed file data into dataset */
	cout << "Using Data from file: " << filename << endl;
	Parser parser(filename);
	parser.read(df.getDataset());

	/* Create the data structure */
	cout<< "Entering Data Factory.."<< endl;
	df.trimData();
	df.createData();
	Data& data = df.getData();

	/* Generate the set of random centers */ 
	data.nCenters = 5;
	data.nStages = 5;
	data.generateRandomCenters();

	cout<< "Running K Means CPU .."<< endl;
	KMeansCPU kMeansCPU(data);
	Centers& finalCpu = kMeansCPU.execute();
	cout << "Final Result from CPU KMeans: " << endl;
	finalCpu.print();

	for(int q = 0; q < 30; q++, cout << "-"); cout << endl;

	cout<< "Running K Means GPU.."<< endl;
	KMeansGPU kMeansGPU(data);
	Centers& finalGpu = kMeansGPU.execute();
	cout << "Final Result from GPU KMeans: " << endl;
	finalGpu.print();

	cout<<"Exiting Program" << endl;
	// system("pause");
}

int cmp(const void *v1, const void *v2)
{
	const float i1 = **(const float **)v1;
	const float i2 = **(const float **)v2;

	return i1 < i2 ? -1 : ( i1 > i2 );
}
