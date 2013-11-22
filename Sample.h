/*
 * Sample.h
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <vector>

class Sample{
public:
	std::vector<double> input;
	bool burn;

	int getNFeatures(){
		return input.size();
	}
};



#endif /* SAMPLE_H_ */
