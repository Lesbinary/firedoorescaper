/*
 * LRMachine.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#include "LRMachine.h"

LRMachine::LRMachine() {
	// TODO Auto-generated constructor stub
	nFeatures = 4;
	classifySuccesses = 0;
	iterTrain = 1000;
	alphaTrain = 0.001;
}

LRMachine::~LRMachine() {
	// TODO Auto-generated destructor stub
}

void LRMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

bool LRMachine::isTrainingReady() {
	if(trainingSet.size() > 500 ){
		trainByGradient(iterTrain, alphaTrain);
		return true;
	} else return false;
}

bool LRMachine::isReadyToCross() {
	return classifySuccesses > 10;
}

void LRMachine::classifySample(Sample sample) {
	// Como tengo un sigmoide, con un threshold voy to cheto
	double p = 0.0;
	for(int i=0; i<nFeatures+1; i++){
		if(i==0)
			p = theta[i];
		else p += theta[i]*sample.input[i-1];
	}
	p=sigmoid(p);
	if((p>0.5 && sample.burn) || (p<=0.5 && !sample.burn)){
		if(p>0.5)
			std::cout << "Predigo que la puerta está encendida" << std::endl;
		else std::cout << "Predigo que la puerta está apagada" << std::endl;
		std::cout << "Ha clasificao de puta madre" << std::endl;
		this->classifySuccesses++;
	} else if ((p<=0.5 && sample.burn) || (p>0.5 && !sample.burn)){
		if(p>0.5)
			std::cout << "Predigo que la puerta está encendida" << std::endl;
		else std::cout << "Predigo que la puerta está apagada" << std::endl;
		std::cout << "Pinyico... volviendo a entrenar" << std::endl;
		this->trainingSet.push_back(sample);
		this->trainByGradient(iterTrain, alphaTrain);
		this->classifySuccesses--;
	} else std::cout << "No se que carajo ha pasado" << std::endl;
	std::cout << "He clasificado correctamente " << classifySuccesses << std::endl;

}

bool LRMachine::isDoorOnFire(double input[]) {
	double p = 0.0;
	for(int i=0; i<nFeatures+1; i++){
		if(i==0)
			p = theta[i];
		else p += theta[i]*input[i-1];
	}
	p=sigmoid(p);
	std::cout << "La probabilidad de que la puerta esté caliente es: " << p << std::endl;
	if(p>0.4 && p <0.6)
		return true; // Esto es un truquillo para no jugarsela en un rango de más indecisión
	if(p>0.5)
		return true;
	else return false;
}

void LRMachine::clearTrainingSet() {
	trainingSet.clear();
	classifySuccesses=0;
}

double LRMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
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
		grad[j] = parcial/sizeY;
	}
}

void LRMachine::trainByGradient(int iter, double alpha) {
	double vari = 0.01;
	double pCoste = 0.0;
	double gradiente[nFeatures+1];
	fillX(X);
	fillTheta(theta);
	fillY(y);

	for(int k=0; k<iter; k++){
		// Calculo el coste
		double coste = cost(theta, nFeatures+1, X, y, trainingSet.size());
//		std::cout << "Para la iteración " << k << " el coste es: " << coste << std::endl;
		// Recalculo theta para la siguiente iteracion
		grad(theta, nFeatures+1, X, y, trainingSet.size(), gradiente);
//		std::cout << "El nuevo theta para la it " << k << " es: ";
		for(int i=0; i<nFeatures+1; i++){
			theta[i]=theta[i]-alpha*gradiente[i];
//			std::cout << theta[i]-alpha*gradiente[i] << " (" << alpha*gradiente[i] << ") ";
		}
//		std::cout << std::endl;
		vari = std::abs(coste-pCoste);
//		std::cout << "La variación en el coste para la iteración "<< k <<" es de: " << vari << std::endl;
		if(vari < 0.0001 && !(std::isnan(vari))){ // Truquillo porque a veces es nan
			std::cout << "Estoy suficientemente entrenado!!!!!!\n";
			break;
		} else if (std::isnan(vari)){
//			std::cout << "Tengo un NaN!!!!\n";
		}
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
