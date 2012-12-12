#ifndef DATAFACTORY_H
#define DATAFACTORY_H

#include <vector>
#include "Data.h"

namespace KMG
{
	class DataFactory
	{
	private:
		Data* dataptr;
		std::vector < std::vector < float > > dataset;

	public:
		std::vector < std::vector < float > > & getDataset() {return dataset;}
		void createData();
		void trimData();
		Data& getData() {return *dataptr;}

		~DataFactory()
		{
			if(!dataptr) delete dataptr;
		}
	};
}
#endif
