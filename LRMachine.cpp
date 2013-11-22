/*
 * LRMachine.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#include "LRMachine.h"

LRMachine::LRMachine() {
	// TODO Auto-generated constructor stub
	nFeatures = 1;
	classifySuccesses = 0;
}

LRMachine::~LRMachine() {
	// TODO Auto-generated destructor stub
}

void LRMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

bool LRMachine::isTrainingReady() {
	if(trainingSet.size() > 20){
		trainByGradient(400, 0.001);
		return true;
	} else return false;
}

bool LRMachine::isReadyToCross() {
	return classifySuccesses > 50;
}

void LRMachine::classifySample(Sample sample) {
//	double X[3][100];
//	for(int i=0; i<3; i++)
//		for(int j=0; j<3; j++)
//			X[i][j]=i+j;
//	double theta[3] = { 0, 0, 0 };
//	double Y[3] = { 1, 2, 3};
//	double coste = cost(theta, 3, X, Y, 3);
//	std::cout << "El coste es de: " << coste << std::endl;
//	std::cout << "Y el gradiente es: ";
//	double gradiente[3];
//	grad(theta, 3, X, Y, 3, gradiente);
//	for(int i=0; i<3; i++)
//		std::cout << gradiente[i] << " ";
//	std::cout << std::endl;

	// Como tengo un sigmoide, con un threshold voy to cheto
	double p = 0.0;
	for(int i=0; i<nFeatures+1; i++){
		if(i==0)
			p = theta[i];
		else p += theta[i]*sample.input[i-1];
	}
	std::cout << "La probabilidad de que la puerta con valor: " << sample.input[0] << " es: " << p << std::endl;
	if(p>0.5 && sample.burn){
		std::cout << "Ha clasificao de puta madre" << std::endl;
		this->classifySuccesses++;
	} else{
		std::cout << "Pinyico... volviendo a entrenar" << std::endl;
		this->classifySuccesses--;
		this->trainingSet.push_back(sample);
		this->trainByGradient(1000, 0.01);
	}

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

void LRMachine::trainByGradient(int iter, double alpha) {
	int it = 400;
	double vari = 0.01;
	double pCoste = 0.0;
	fillX(X);
	fillTheta(theta);
	fillY(y);

	// Imprimo cosas pa ver como va
	std::cout << "Hay estos elementos: " << trainingSet.size() << std::endl;
	for(int i=0;i<trainingSet.size(); i++){
		for(int j=0; j<nFeatures+1; j++){
			std::cout << X[i][j] << " \n";
		}
		std::cout << std::endl;
	}

	for(int k=0; k<it; k++){
		// Calculo el coste
		double coste = cost(theta, nFeatures+1, X, y, trainingSet.size());
		std::cout << "Para esta iteración el coste es: " << coste << std::endl;
		// Recalculo theta para la siguiente iteracion
		double gradiente[nFeatures+1];
		grad(theta, nFeatures+1, X, y, trainingSet.size(), gradiente);
		std::cout << "El nuevo theta para la it " << k << " es: ";
		for(int i=0; i<nFeatures+1; i++){
			theta[i]=theta[i]-alpha*gradiente[i];
			std::cout << theta[i]-alpha*gradiente[i] << " (" << alpha*gradiente[i] << ") ";
		}
		std::cout << std::endl;
		std::cout << "La variación en el coste es de: " << pCoste-coste << std::endl;
		pCoste = coste;
	}

}

void LRMachine::fillX(double X[][100]) {
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<nFeatures+1; j++){
			if(j==0)
				X[i][j]=1.0;
			else X[i][j]=trainingSet[i].input[j-1];
		}
	}
}

void LRMachine::fillTheta(double theta[]) {
	for(int i=0; i<nFeatures+1; i++)
		theta[i]=0;
}

void LRMachine::fillY(double y[]) {
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			y[i]=1;
		else y[i]=0;
	}
}
