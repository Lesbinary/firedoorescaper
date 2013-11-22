/*
 * LRMachine.h
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#ifndef LRMACHINE_H_
#define LRMACHINE_H_

#include "IMachine.h"
#include <cmath>
#include <iostream>

class LRMachine : public IMachine {
public:
	LRMachine();
	virtual ~LRMachine();

	void addTrainingSample(Sample sample);
	bool isTrainingReady();
	bool isReadyToCross();
	void classifySample(Sample sample);
	bool isDoorOnFire(double input[]);
	void clearTrainingSet();

private:
	std::vector<Sample> trainingSet;
	int classifySuccesses;
	int nFeatures;
	double X[1000][100];
	double y[1000];
	double theta[1000];

	// Internal functions
	double sigmoid(double z);
	double cost(double tetha[], int sizeT, double X[][100], double y[], int sizeY);
	void grad(double tetha[], int sizeT, double X[][100], double y[], int sizeY, double grad[]);
	void trainByGradient(int iter, double alpha);

	// Auxiliar functions
	void fillX(double X[][100]);
	void fillTheta(double theta[]);
	void fillY(double y[]);



};

#endif /* LRMACHINE_H_ */
