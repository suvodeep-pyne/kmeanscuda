#ifndef POINT_H
#define POINT_H

#include "Header.h"

namespace KMG
{
	class Point
	{
	public:
		static int dim;
		float* x; // The coordinate

	public:
		float* getX() const {return x;}
		Point() 
		{
			if(dim > 0)
			{
				x = new float[dim];
				for(int i = 0; i < dim; i++)
				{
					x[i] = 0;
				}
			}
		}

		Point(const Point& p)
		{
			x = new float[dim];
			for(int i = 0; i < dim; i++)
			{
				x[i] = p.x[i];
			}
		}

		float getDistance(Point& p) const;
		void add(const Point& p)
		{
			for(int i = 0; i < dim; i++)
			{
				x[i] += p.x[i];
			}
		}

		void moveToCentroid (const Point& sumPoints, const int count, bool flag = false, float * center = 0)
		{
			for(int i = 0; i < dim; i++)
			{
				x[i] = sumPoints.x[i] / count;
				if(flag) 
					center[i] = x[i];
			}
		}
		std::string toString() const;

		static void setDim(int dim) { Point::dim = dim;}
		static int getDim() { return dim; }

		~Point()
		{
			if(!x) delete [] x;
		}
	};
}


#endif
