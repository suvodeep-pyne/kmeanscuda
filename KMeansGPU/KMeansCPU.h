#ifndef KMEANSCPU_H
#define KMEANSCPU_H

#include "KMeans.h"

namespace KMG
{

	class KMeansCPU : public KMeans
	{
	private:

	public:
		KMeansCPU(Data& data) : KMeans(data) {}
		Centers& execute();

	};
}
#endif
