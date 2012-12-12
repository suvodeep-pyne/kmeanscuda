#include <iostream>
#include <fstream>
#include <sstream>

#include "Parser.h"

using namespace KMG;

void Parser :: read(std::vector < std::vector < float > > & dataset)
{
	int dim;

	std::cout<<"\tReading File: " << filename << std::endl;
	std::ifstream file(filename.c_str());
	if(!file.good())
	{
		std :: cerr << "Read/Write operation failure. Exiting.." << std :: endl;
		exit(EXIT_FAILURE);
	}
	std::string   line;

	bool flag = true;

	while(std::getline(file, line))
	{
		std::stringstream   linestream(line);
		float				value;

		int dimCount = 0;
		
		std::vector<float> point;
		while (linestream >> value)
		{
			point.push_back(value);

			/* Error checking */
			dimCount++;
		}

		/* Error checking */
		if(flag) dim = dimCount; flag = false;
		assert (dim == dimCount);

		if(dataset.size() > 9999 && dataset.size() % 10000 == 0)
			std::cout << "\tRead " << dataset.size() / 1000 << "k lines.." << std::endl;

		dataset.push_back(point);
	}
	std::cout << "\tDone reading file." << std::endl;
	std::cout << "\tDataset details: " << dim << " Dimensions, " << dataset.size() << " points." << std::endl;
}
