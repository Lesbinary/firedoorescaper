/*
 * NNMachine.cpp
 *
 *  Created on: 27/11/2013
 *      Author: alvaro
 */

#include "NNMachine.h"

NNMachine::NNMachine() {
	// TODO Auto-generated constructor stub
	nFeatures = 4;
	classifySuccesses = 0;
	iterTrain = 1000;
	alphaTrain = 0.001;
	trainType = 1; //1 normal, 2 gradiente
}

NNMachine::~NNMachine() {
	// TODO Auto-generated destructor stub
}

void NNMachine::pedirParametros() {

	std::cout << "1.Normal" << std::endl;
	std::cout << "2.Descenso por gradiente" << std::endl;
	std::cout << "Elige el modo de calculo del error: ";
	std::cin >> trainType;

	system("cls");
	if(trainType == 2){
		std::cout << "Introduce el valor de alpha: ";
		std::cin >> alphaTrain;
		system("cls");
		std::cout << "Introduce el numero de iteraciones: ";
		std::cin >> iterTrain;
		system("cls");
	 }
}


void NNMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}


bool NNMachine::isTrainingReady() {
}

bool NNMachine::isReadyToCross() {
	return classifySuccesses > 10;
}

void NNMachine::classifySample(Sample sample) {
}

bool NNMachine::isDoorOnFire(double input[]) {
}

void NNMachine::clearTrainingSet() {
	trainingSet.clear();
	classifySuccesses=0;
}


