#ifdef _MSC_VER // Compiling under Visual Studio
#include <Windows.h>
#endif

#include "KMeansCPU.h"
#include <iostream>
#include <time.h>

using namespace std;
using namespace KMG;

Centers& KMeansCPU::execute()
{
	cout<< "Running CPU version of K Means Algorithm.."<< endl;
	reset();

#ifdef _MSC_VER // Compiling under Visual Studio
	unsigned long startTime_, diffInMilliSec;
	startTime_ = GetTickCount();
#else
	struct timespec t_start, t_end;
	double elapsedTime;
	clock_gettime(CLOCK_REALTIME, &t_start);
#endif
	const Point* p = data.getPoints();

	for(int s = 1; s <= nStages; s++)
	{
		cout<< "Stage " << s << " starting..";
		curr.resetPerIteration();
		// curr.print();

		/* Assign to the closest centers */ 
		for(PIdx i = 0; i < data.getNPoints(); i++)
		{
			CIdx k = findClosestCenter(p[i]);

			clusterIdx[i] = k;
			curr.getSumPoints()[k].add(p[i]);
			curr.getCountPerCenter()[k]++;
			// curr.print();
		}

		/* Find new set of centers */
		curr.updateCenters();
		// curr.updateDistMat();
		// curr.updateRidMat();

		//curr.print();
		//curr.printDistMat();
		//curr.printRidMat();

		cout<< " done."<< endl;
	}

	cout<< "Completed K Means."<< endl;
#ifdef _MSC_VER // Compiling under Visual Studio
	diffInMilliSec = GetTickCount() - startTime_;
	printf("Time taken for KMeans on CPU : %10lu millisec\n", diffInMilliSec);
#else
	clock_gettime(CLOCK_REALTIME, &t_end);
	elapsedTime = (t_end.tv_sec - t_start.tv_sec)*1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec)/1000000.0;
	printf("time elapsed CPU TOTAL TIME %1f msec\n", elapsedTime);
#endif
	return curr;
}
