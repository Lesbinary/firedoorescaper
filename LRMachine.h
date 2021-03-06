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
#include <vector>
#include "armadillo"
#include <lbfgs.h>

// Implementar Precision and Recall

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
	void pedirParametros();

private:
	std::vector<Sample> trainingSet;
	int classifySuccesses;
	int nFeatures;
	std::vector<std::vector<double> > X;
	std::vector<double> y;
	std::vector<double> theta;
	int iterTrain;
	double alphaTrain;
	int trainType;

	// Internal functions
	double sigmoid(double z);
	double cost(std::vector<double> theta, std::vector<std::vector<double> > X, std::vector<double> y);
	void grad(std::vector<double> tetha, std::vector<std::vector<double> > X, std::vector<double> y, std::vector<double> grad);
	void trainByGradient(int iter, double alpha);
	void trainByGradientAdvanced(int iter, double alpha);
	void trainByNormalEcuation();
	void upgradeParameters();

	// Auxiliar functions
	void fillX();
	void fillTheta();
	void fillY();

};

#endif /* LRMACHINE_H_ */
