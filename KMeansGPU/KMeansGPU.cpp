#include <iostream>
#include "KMeansGPU.h"

using namespace std;
using namespace KMG;

Centers& KMeansGPU::execute()
{
	cout<< "Running GPU version of K Means Algorithm.."<< endl;
	reset();

	gpu_kernel(*this);
	return curr;
}
