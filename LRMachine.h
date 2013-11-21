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
	bool isDoorOnFire(double input);
	void clearTrainingSet();

private:
	std::vector<Sample> trainingSet;
	int classifySuccesses;

	// Internal functions
	double sigmoid(double z);
	double cost(double tetha[], int sizeT, double X[][100], double y[], int sizeY);
	void grad(double tetha[], int sizeT, double X[][100], double y[], int sizeY, double grad[]);



};

#endif /* LRMACHINE_H_ */
