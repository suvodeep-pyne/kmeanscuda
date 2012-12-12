#include <stdlib.h>
#include <iostream>
#include "Data.h"

using namespace std;
using namespace KMG;


int generateRandom(int n)
{
	// cout << "generateRandom: "<< n << "  "<< rand() << endl;
	assert ( n > 0);
	if(RAND_MAX < 32768)
		return ((rand() << 16 | rand()) % n);
	else
		return rand() % n;
}

// Take any random k points
void Data::generateRandomCenters()
{
	srand ( (unsigned)time(NULL));
	cout<< "Generating Random Centers.." << endl;
	assert (nCenters < nPoints);

	PIdx* pidxArray = new PIdx[nPoints];
	for(int i = 0; i < getNPoints(); i++)
	{
		pidxArray[i] = i;
	}

	cout << "\tChoosing " << nCenters << " centers randomly from the dataset." << endl;
	centers = new Point[nCenters];
	for(int k = 0; k < nCenters; k++)
	{
		int randIdx = k + generateRandom(getNPoints() - k);
		// cout << "RandIdx: " << randIdx <<endl;
		assert (randIdx >= 0 && randIdx < getNPoints());

		int temp = pidxArray[k];
		pidxArray[k] = pidxArray[randIdx];
		pidxArray[randIdx] = temp;

		centers[k] = Point(getPoints()[pidxArray[k]]);
	}
	cout << "done." << endl;
	delete [] pidxArray;
}