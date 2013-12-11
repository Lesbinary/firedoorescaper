/*
 * IKernel.h
 *
 *  Created on: Dec 11, 2013
 *      Author: antonio
 */

#ifndef IKERNEL_H_
#define IKERNEL_H_

#include "armadillo"

class IKernel{
public:
	virtual void K(arma::mat X, arma::mat X2) = 0;
};



#endif /* IKERNEL_H_ */
