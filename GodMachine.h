/*
 * GodMachine.h
 *
 *  Created on: 11/11/2013
 *      Author: leopoldo
 */

#ifndef GODMACHINE_H_
#define GODMACHINE_H_

#include <iostream>     // std::cout
#include <cmath>        // std::abs
#include <float.h>
#include "IMachine.h"
#include "KVMachine.h"
#include "LRMachine.h"
#include "NNMachine.h"
#include "SVMachine/SVMachine.h"

enum Machine {LogisticRegresion, KVecinos, neuralNetwork, SVM};

class GodMachine {
public:
	GodMachine(){
		machine = new LRMachine();
	}

	GodMachine(Machine m){
		switch(m){
			case LogisticRegresion: machine=new LRMachine();
				break;
			case KVecinos: machine=new KVMachine();
				break;
			case neuralNetwork: machine = new NNMachine();
				break;
			case SVM: machine = new SVMachine(Polynomial);
				break;
		}
	}

	virtual ~GodMachine(){}
	void pedirParametros(){
		machine->pedirParametros();
	}
	void addTrainingSample(Sample sample){
		machine->addTrainingSample(sample);
	}
	bool isTrainingReady(){
		return machine->isTrainingReady();
	}
	bool isReadyToCross(){
		return machine->isReadyToCross();
	}
	void classifySample(Sample sample){
		machine->classifySample(sample);
	}
	bool isDoorOnFire(double input[]){
		return machine->isDoorOnFire(input);
	}
	void clearTrainingSet(){
		machine->clearTrainingSet();
	}
private:
	IMachine* machine;
};


#endif /* GODMACHINE_H_ */
