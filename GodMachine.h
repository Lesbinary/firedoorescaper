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


struct Sample{
	std::vector<double> input;
	bool burn;
};

class GodMachine {
public:
	GodMachine(){
		classifySuccesses = 0;
	}
	virtual ~GodMachine(){}
	void addTrainingSample(Sample sample){
		trainingSet.push_back(sample);
	}
	bool isTrainingReady(){

		return (trainingSet.size() > 20);
	}
	bool isReadyToCross(){
		return classifySuccesses > 50;
	}
	void classifySample(Sample sample){
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
	bool isDoorOnFire(double input){
		int nearest = 0;
		double nearestDistance = DBL_MAX;
		for(int i = 0; i < trainingSet.size(); i++){
			double tmp = std::abs((input - trainingSet[i].input[0]));
			if (tmp < nearestDistance){
				nearestDistance = tmp;
				nearest = i;
			}
		}
//		std::cout << "El valor más cercano a " << input << " es " << trainingSet[nearest].input[0] << " y la puerta arde: " << trainingSet[nearest].burn << std::endl;

		return trainingSet[nearest].burn;
	}
	void clearTrainingSet(){
		trainingSet.clear();
		classifySuccesses = 0;
	}
private:
	std::vector<Sample> trainingSet;
	int classifySuccesses;
};


#endif /* GODMACHINE_H_ */
