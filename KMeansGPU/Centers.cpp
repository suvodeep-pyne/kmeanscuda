#include <stdio.h>
#include "Centers.h"

using namespace KMG;

void Centers::processLabel(const int* const label, const Data& data)
{
	int l;
	const Point* points = data.getPoints();
	const int nPoints = data.getNPoints();
	for(int i = 0; i < nPoints; i++)
	{
		l = label[i];
		assert (l >= 0 && l < nCenters);

		sumPoints[l].add(points[i]);
		countPerCenter[l]++;
	}
}

void Centers::update()
{
	updateCenters();
	updateDistMat();
	updateRidMat();
}

void Centers::updateCenters(bool flag, float* centers)
{
	if(flag)
	{
		for(CIdx i = 0; i < nCenters; i++)
		{
			getCenters()[i].moveToCentroid(getSumPoints()[i], countPerCenter[i], true, centers + i * Point::dim);
		}
	}
	else
	{
		for(CIdx i = 0; i < nCenters; i++)
		{
			getCenters()[i].moveToCentroid(getSumPoints()[i], countPerCenter[i]);
		}
	}

}

void Centers::updateDistMat() {
	for(int i = 0; i < nCenters; i++) {
		for(int j = 0; j < nCenters; j++) {
			distMat[i * nCenters + j] = centers[i].getDistance(centers[j]);
		}
	}
}

void Centers::updateRidMat() {
	float **parray = new float*[nCenters];
	for(int i = 0; i < nCenters; i++) {

		/* Assign each pointer to each element */
		for(int j = 0; j < nCenters; j++)
			parray[j] = &distMat[i * nCenters + j];

		/* Sort on the pointer */
		qsort(parray, nCenters, sizeof *parray, cmp);

		for(int j = 0; j < nCenters; j++)
			ridMat[i * nCenters + j] = parray[j] - &distMat[i * nCenters];
	}
	delete [] parray;
}

void Centers::print()
{
	printCenters();
	printf("Sum Points:\n");
	for(int i = 0; i < nCenters; i++) {
		printf("\t%d : %s \n", i, sumPoints[i].toString().c_str());
	}
	printf("Count per Center:\n");
	for(int i = 0; i < nCenters; i++) {
		printf("\t%d : %d \n", i, countPerCenter[i]);
	}
}

void Centers::printCenters()
{
	printf("No of Centers: %d\n", nCenters);
	printf("Centers:\n");
	for(int i = 0; i < nCenters; i++) {
		printf("\t%d : %s \n", i, centers[i].toString().c_str());
	}
}

void Centers::printDistMat()
{
	printf("Printing CID Matrix\n");
	for(int i = 0; i < nCenters; i++) {
		for(int j = 0; j < nCenters; j++) {
			printf("%5.3f ", distMat[i*nCenters + j]);
		}
		printf("\n");
	}
	printf("done.\n");
}

void Centers::printRidMat()
{
	printf("Printing RID Matrix\n");
	for(int i = 0; i < nCenters; i++) {
		for(int j = 0; j < nCenters; j++) {
			printf("%5d ", ridMat[i * nCenters + j]);
		}
		printf("\n");
	}
	printf("done.\n");
}
