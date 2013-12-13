/*
 * SVMachine.h
 *
 *  Created on: Dec 6, 2013
 *      Author: antonio
 */

#ifndef SVMACHINE_H_
#define SVMACHINE_H_

#include "../IMachine.h"
#include <iostream>
#include <vector>
#include <CGAL/MP_Float.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include "armadillo"
#include "IKernel.h"
#include "LinearKernel.h"
#include "PolynomialKernel.h"
#include "RBFKernel.h"

typedef std::vector<Sample> VSample;
typedef CGAL::MP_Float ET;
typedef arma::Mat<ET> mat;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
enum KernelType {Linear, Polynomial, RBF};

class SVMachine: public IMachine {
public:


	SVMachine();

	SVMachine(KernelType t);

	virtual ~SVMachine();

	void addTrainingSample(Sample sample);
	bool isTrainingReady();
	bool isReadyToCross();
	void classifySample(Sample sample);
	bool isDoorOnFire(double input[]);
	void clearTrainingSet();
	void pedirParametros();

private:
	VSample trainingSet;
	int classifySuccesses;
	int nFeatures;
	int m; // Un Suppor Vector
	arma::mat y;
	arma::mat X;
	arma::mat SupportVectors;
	ET b;
	IKernel* kernel;

	void quadraticSolution();
	void trainByQuadraticProgramming();
};

#endif /* SVMACHINE_H_ */
