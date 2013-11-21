/*
 * LRMachine.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#include "LRMachine.h"

LRMachine::LRMachine() {
	// TODO Auto-generated constructor stub

}

LRMachine::~LRMachine() {
	// TODO Auto-generated destructor stub
}

void LRMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

bool LRMachine::isTrainingReady() {
	return (trainingSet.size() > 20);
}

bool LRMachine::isReadyToCross() {
	return classifySuccesses > 50;
}

void LRMachine::classifySample(Sample sample) {
	double X[3][100];
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			X[i][j]=i+j;
	double theta[3] = { 0, 0, 0 };
	double Y[3] = { 1, 2, 3};
	double coste = cost(theta, 3, X, Y, 3);
	std::cout << "El coste es de: " << coste << std::endl;
	std::cout << "Y el gradiente es: ";
	double gradiente[3];
	grad(theta, 3, X, Y, 3, gradiente);
	for(int i=0; i<3; i++)
		std::cout << gradiente[i] << " ";
	std::cout << std::endl;

}

bool LRMachine::isDoorOnFire(double input) {
}

void LRMachine::clearTrainingSet() {
}

double LRMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,z));
}

double LRMachine::cost(double theta[], int sizeT, double X[][100],
		double y[], int sizeY) {
	double J = 0.0;
	for(int i=0; i<sizeY; i++){
		// Calculo el valor de la hipótises para la theta dada
		double h = 0.0;
		for(int j=0; j<sizeT; j++){
			h += theta[j]*X[i][j];
		}
		h = sigmoid(h);
		// Calculo el valor del coste para la theta dada
		J+=(-y[i]*std::log(h))-((1-y[i])*std::log(1-h));
	}
	return J/sizeY;
}

void LRMachine::grad(double theta[], int sizeT, double X[][100], double y[],
		int sizeY, double grad[]) {
	for(int j=0; j<sizeT; j++){
		double parcial = 0.0;
		for(int i=0; i<sizeY; i++){
			// Calculo el valor de la hipótises para la theta dada
			double h = 0.0;
			for(int k=0; k<sizeT; k++){
				h += theta[k]*X[i][k];
			}
			h = sigmoid(h);
			parcial += (h-y[i])*X[i][j];
		}
		grad[j] = parcial;
	}
}
