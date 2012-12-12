#include "DataFactory.h"
#include <iostream>

using namespace std;
using namespace KMG;

void DataFactory::createData()
{
	cout<< "\tCreating Data Object.."<< endl;
	int nPoints = dataset.size();
	assert (nPoints > 0);
	
	int dim = dataset[0].size();
	assert (dim > 0);

	Point::setDim(dim);

	Point* points = new Point[nPoints];
	for(int i = 0 ; i < nPoints; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			points[i].getX()[j] = dataset[i][j];
		}
	}

	dataptr = new Data(dim, nPoints, points);
	cout<< "\tData Object created with "<< nPoints << " points ( " << dim << " dimensions)" << endl;
}

void DataFactory::trimData()
{
	int acceptableSize = (dataset.size() / THREADS_PER_BLOCK) * THREADS_PER_BLOCK;
	cout << "Trimming data set to a multiple of " << THREADS_PER_BLOCK << endl;
	cout << "Changing Dataset size from " << dataset.size() << " to " << acceptableSize << endl;

	if(acceptableSize == 0)
	{
		cout << "Dataset too small for GPU computation.\nExiting.." << endl;
		system("pause");
		exit(EXIT_SUCCESS);
	}
	dataset.resize(acceptableSize);
}
