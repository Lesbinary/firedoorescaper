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
#include <vector>
#include <cstdlib>

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
		int nFeatures;
		int nSamples;

	//Esto es pa aclararme yo
		int L; //numero de capas de la red
		std::vector<int> s_l; //número de nodos por capa
		int classifySuccesses;

	//Variables

		std::vector<Sample> trainingSet; //Conjunto de samples para el entrenamiento
		//std::vector<double> inputLayer;
		std::vector<std::vector<std::vector<double> > > thetas; //L-1 matrices
		std::vector<std::vector<double> > a; //Creo que el nombre es bastante descriptivo
		std::vector<double> y;//Outputs de los samples

	//Valor para la regularizacion
		double lambda;

		void backPropagation();
		void forwardPropagation(std::vector<double> theta);
		double cost(std::vector<double> thetas);
		double sigmoid(double z);
		void train();

		void initA();
		void initTheta();
		void fillY();
};

#endif /* NNMACHINE_H_ */
