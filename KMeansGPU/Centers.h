#ifndef CENTERS_H
#define CENTERS_H

#include "Data.h"

namespace KMG
{
	class Centers
	{
	public:
		int nCenters;
		Point* centers;
		Point* sumPoints; // Vector sum of points
		int* countPerCenter; // number of points per center

		float *distMat;
		CIdx *ridMat;

	public:
		void init()
		{
			centers = new Point[nCenters];
			sumPoints = new Point[nCenters];
			countPerCenter = new int[nCenters];

			distMat = new float[nCenters * nCenters];
			ridMat = new int[nCenters * nCenters];
		}

		void print();
		void printCenters();
		void printDistMat();
		void printRidMat();

		int getNCenters() const {return nCenters; }
		void setNCenters(int nCenters) { this->nCenters = nCenters; }
		Point* getCenters() {return centers; }
		Point* getSumPoints() {return sumPoints; }
		int* getCountPerCenter() {return countPerCenter; }

		void resetPerIteration()
		{
			for(CIdx i = 0; i < nCenters; i++)
			{
				sumPoints[i] = Point();
				countPerCenter[i] = 0;
			}
		}

		void processLabel(const int* const label, const Data& data);

		void update();

		void updateCenters(bool flag = false, float* centers = 0);
		void updateDistMat();
		void updateRidMat();

		~Centers()
		{
			if(!centers) delete [] centers;
			if(!sumPoints) delete [] sumPoints;
			if(!countPerCenter) delete [] countPerCenter;

			if(!distMat) {
				delete [] distMat;
			}

			if(!ridMat) {
				delete [] ridMat;
			}
		}
	};
}

#endif
