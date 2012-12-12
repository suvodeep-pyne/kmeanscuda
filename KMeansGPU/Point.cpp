#include <iostream>
#include <sstream>
using namespace std;

#include "Point.h"

using namespace KMG;

int Point::dim;

float Point::getDistance(Point& p) const
{
	float distance = 0;
	for(int i = 0; i < getDim(); i++)
	{
		distance += (x[i] - p.x[i]) * (x[i] - p.x[i]);
	}
	// printf("getDistance - [%s, %s] = %5.3f\n", this->toString().c_str(), p.toString().c_str(), sqrt(distance));
	return sqrt(distance);
}

string Point::toString() const
{
	ostringstream oss (ostringstream::out);

	oss << "Point(" << x[0];
	for(int i = 1; i < dim; i++) {
		oss << ", " << x[i];
	}
	oss << ")";
	return oss.str();
}
