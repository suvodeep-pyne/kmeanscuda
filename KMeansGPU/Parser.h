#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "DataFactory.h"

namespace KMG
{
	class Parser
	{
	private:
		std::string filename;
		
	public:
		Parser(std::string filename) : filename(filename) {}
		void read(std::vector < std::vector < float > > & dataset);
	};
}
#endif
