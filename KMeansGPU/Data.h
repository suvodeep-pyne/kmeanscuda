#ifndef DATA_H
#define DATA_H

#include "Point.h"

namespace KMG
{
	class Data
	{
	private:
		int dim;
		int nPoints;
		Point* points;

	public:
		int nStages;
		int nCenters;
		Point* centers;

	public:
		Data(int dim, int nPoints, Point* points) : dim(dim), nPoints(nPoints), points(points) 
		{
			/* Defaults */
			nStages = 1;
			nCenters = 1;
		} 
		
		int		getDim() const {return dim;}
		void	setDim(int dim) {this->dim = dim;}
		
		int		getNPoints() const {return nPoints;}
		void	setNPoints(int nPoints) {this->nPoints = nPoints;}
		
		Point*	getPoints() const {return points;}
		void	setPoints(Point* points) {this -> points = points; }

		void generateRandomCenters();

		virtual ~Data()
		{
			if(!points) delete [] points;
			if(!centers) delete [] centers;
		}
	};
}

#endif
