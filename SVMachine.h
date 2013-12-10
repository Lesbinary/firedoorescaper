/*
 * SVMachine.h
 *
 *  Created on: Dec 6, 2013
 *      Author: antonio
 */

#ifndef SVMACHINE_H_
#define SVMACHINE_H_

#include "IMachine.h"
#include <iostream>
#include <vector>
#include <CGAL/MP_Float.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include "armadillo"

typedef std::vector<Sample> VSample;

typedef CGAL::MP_Float ET;

//// program and solution types
//typedef CGAL::Quadratic_program_from_iterators
//<int**, // for A
//int*, // for b
//CGAL::Const_oneset_iterator<CGAL::Comparison_result>, // for r
//bool*, // for fl
//int*, // for l
//bool*, // for fu
//int*, // for u
//double**, // for D
//int*> // for c
//Program;
//typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

class SVMachine: public IMachine {
public:
	SVMachine();
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

	void quadraticSolution();
	void trainByQuadraticProgramming();
};

#endif /* SVMACHINE_H_ */
