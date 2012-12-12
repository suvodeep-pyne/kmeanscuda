#include <stdlib.h>
#include <iostream>
#include "KMeans.h"

using namespace std;
using namespace KMG;

// Take any random k points
void KMeans::generateRandomCenters()
{
	srand ( (unsigned)time(NULL));
	cout<< "Retrieving Random Centers.." << endl;
	assert (nCenters < data.getNPoints());
	curr.setNCenters(nCenters);
	curr.init();

	for(int k = 0; k < nCenters; k++)
	{
		curr.getCenters()[k] = Point(data.centers[k]);
		//cout << "\t" << k+1 << "> " << curr.getCenters()[k].toString() << endl;
	}

	curr.printCenters();
}

CIdx KMeans::findClosestCenter(const Point& p)
{
	float dist = p.getDistance(curr.getCenters()[0]);
	
	float minDist = dist;
	Index minIdx = 0;

	for(int i = 1; i < nCenters; i++)
	{
		dist = p.getDistance(curr.getCenters()[i]);
		if(minDist > dist)
		{
			minDist = dist;
			minIdx = i;
		}
	}
	return minIdx;
}
