/*
 * GodMachine.h
 *
 *  Created on: 11/11/2013
 *      Author: leopoldo
 */

#ifndef GODMACHINE_H_
#define GODMACHINE_H_


struct Sample{
	std::vector<double> input;
	bool burn;
};

class GodMachine {
public:
	GodMachine(){}
	virtual ~GodMachine(){}
	void addTrainingSample(Sample sample){
		trainingSet.push_back(sample);
	}
	bool isTrainingReady(){
		return trainingSet.size()==5;
	}
	void clearTrainingSet(){
		trainingSet.clear();
	}
private:
	std::vector<Sample> trainingSet;
};


#endif /* GODMACHINE_H_ */
