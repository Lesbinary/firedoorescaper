/*
 * KVMachine.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#include "KVMachine.h"

KVMachine::KVMachine() {
	classifySuccesses = 0;
}

KVMachine::~KVMachine() {

}

void KVMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

bool KVMachine::isTrainingReady() {
	return (trainingSet.size() > 20);
}

bool KVMachine::isReadyToCross() {
	return classifySuccesses > 50;
}

void KVMachine::classifySample(Sample sample) {
	int nearest = 0;
	double nearestDistance = DBL_MAX;
	for(int i = 0; i < trainingSet.size(); i++){
		double tmp = std::abs((sample.input[0] - trainingSet[i].input[0]));
		if (tmp < nearestDistance){
			nearestDistance = tmp;
			nearest = i;
		}
	}
	if (trainingSet[nearest].burn == sample.burn){
		classifySuccesses++;
	}
}

bool KVMachine::isDoorOnFire(double input[]) {
	int nearest = 0;
	double nearestDistance = DBL_MAX;
	for(int i = 0; i < trainingSet.size(); i++){
		double tmp = std::abs((input[0] - trainingSet[i].input[0]));
		if (tmp < nearestDistance){
			nearestDistance = tmp;
			nearest = i;
		}
	}
//		std::cout << "El valor más cercano a " << input << " es " << trainingSet[nearest].input[0] << " y la puerta arde: " << trainingSet[nearest].burn << std::endl;

	return trainingSet[nearest].burn;
}

void KVMachine::clearTrainingSet() {
	trainingSet.clear();
	classifySuccesses = 0;
}

void KVMachine::pedirParametros() {
}
