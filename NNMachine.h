/*
 * NNMachine.h
 *
 *  Created on: 27/11/2013
 *      Author: alvaro
 */

#ifndef NNMACHINE_H_
#define NNMACHINE_H_

#include "IMachine.h"
#include <cmath>
#include <iostream>

class NNMachine : public IMachine {
public:
	NNMachine();
	virtual ~NNMachine();

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

};

#endif /* NNMACHINE_H_ */
