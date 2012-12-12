#ifndef KMEANSGPU_H
#define KMEANSGPU_H

#include "KMeans.h"

namespace KMG
{
	class KMeansGPU : public KMeans
	{
	private:


	public:
		KMeansGPU(Data& data) : KMeans(data) {}
		Centers& execute();

	};
}


 int gpu_kernel(KMG::KMeansGPU& kmeansGpu);

#endif
