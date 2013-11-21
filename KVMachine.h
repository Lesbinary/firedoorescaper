/*
 * KVMachine.h
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#ifndef KVMACHINE_H_
#define KVMACHINE_H_

#include <iostream>     // std::cout
#include <cmath>        // std::abs
#include <float.h>
#include "IMachine.h"

class KVMachine: public IMachine {
public:
	KVMachine();
	virtual ~KVMachine();

	void addTrainingSample(Sample sample);
	bool isTrainingReady();
	bool isReadyToCross();
	void classifySample(Sample sample);
	bool isDoorOnFire(double input);
	void clearTrainingSet();

private:
	std::vector<Sample> trainingSet;
	int classifySuccesses;
};

#endif /* KVMACHINE_H_ */
