#ifndef KMEANS_H
#define KMEANS_H

#include "Centers.h"
#include "Data.h"

namespace KMG
{
	class KMeans
	{
	private:

	public:
		int nStages;
		int nCenters;

		const Data& data;
		Centers curr;	// The current solution
		
		CIdx* clusterIdx;

		virtual void reset() // reset everything
		{				
			generateRandomCenters();			// generate random centers
			for(int i = 0; i < data.getNPoints(); i++)
			{
				clusterIdx[i] = 0;
			}
		}

		void generateRandomCenters();
		CIdx findClosestCenter(const Point& p);
		
	public:
		KMeans(Data& data) : data(data) 
		{
			nStages = data.nStages;
			nCenters = data.nCenters;
			clusterIdx = new CIdx[data.getNPoints()];
		}

		virtual ~KMeans()
		{
			if(!clusterIdx) delete [] clusterIdx;
		}
	};
}
#endif
