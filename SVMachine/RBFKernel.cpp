/*
 * RBFKernel.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: antonio
 */

#include "RBFKernel.h"

RBFKernel::RBFKernel() {
	// TODO Auto-generated constructor stub
	this->sigma = 1.0;
}

RBFKernel::~RBFKernel() {
	// TODO Auto-generated destructor stub
}

CGAL::MP_Float RBFKernel::K(arma::vec X1, arma::vec X2) {
	CGAL::MP_Float value(std::exp(computeGamma()*squaredEuclidean(X1, X2)));
	return value;
}

double RBFKernel::computeGamma() {
	return -1.0/2*std::pow(sigma, 2);
}

double RBFKernel::squaredEuclidean(arma::vec X1, arma::vec X2) {
	double sum = 0.0;
	for(int i=0; i< X1.size(); i++){
		sum+=std::pow(X1(i)-X2(i),2);
		std::cout << "Para el elemento " << i << " la distancia suma: " << sum << std::endl;
	}
	return sum;
}
