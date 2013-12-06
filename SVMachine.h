/*
 * SVMachine.h
 *
 *  Created on: Dec 6, 2013
 *      Author: antonio
 */

#ifndef SVMACHINE_H_
#define SVMACHINE_H_

#include "IMachine.h"
#include <QuadProg++.hh>

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
};

#endif /* SVMACHINE_H_ */
