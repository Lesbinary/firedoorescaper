/*
 * LRMachine.h
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#ifndef LRMACHINE_H_
#define LRMACHINE_H_

#include "IMachine.h"

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
};

#endif /* LRMACHINE_H_ */
