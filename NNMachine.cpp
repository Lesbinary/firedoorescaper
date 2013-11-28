/*
 * NNMachine.cpp
 *
 *  Created on: 27/11/2013
 *      Author: alvaro
 */

#include "NNMachine.h"

//A falta de completar
NNMachine::NNMachine() { }

//A falta de completar
NNMachine::~NNMachine() { }

//A falta de completar
void NNMachine::pedirParametros() { }

void NNMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

//A falta de completar
bool NNMachine::isTrainingReady() {
	if(trainingSet.size() == 1){
			nFeatures=trainingSet[0].getNFeatures();
		}
		if(trainingSet.size() > 20 ){
			if(trainType == 1) train();
			return true;
		} else return false;
}

bool NNMachine::isReadyToCross() {
	return classifySuccesses > 10;
}

//A falta de completar
void NNMachine::classifySample(Sample sample) {
	//Aqui no hay tresholds chetos que valgan, this is Sparta
}

//A falta de completar
bool NNMachine::isDoorOnFire(double input[]) {
	//Mmyoquese
}

void NNMachine::clearTrainingSet() {
	inputLayer.clear();
	classifySuccesses=0;
}

//A falta de completar
void NNMachine::backPropagation(){
	//Con un trainingSet dado

	std::vector<std::vector<std::vector<double> > > upperDelta;
	std::vector<std::vector<double> > lowerDelta;

	//Inicialización de upperDelta
	for(int l = 0; l < this->thetas.size(); l++){
		for (int i = 0; i < this->thetas[0].size(); i++){
			for(int j = 0; j < this->thetas[0][0].size(); j++){
				upperDelta[l][i][j] = 0.0;
			}
		}
	}

	for(int i = 0; i < this->nFeatures; i++){
		a[0] = trainingSet[i].input;

		//Cálculo de a^(l) mediante forward propagation
		for(int l = 1; l < this->thetas.size()-1; l++){
			forwardPropagation(a[l-1],a[l],thetas[l-1]);
		}

		//Uso de y^(i) para calcular lowerDelta^(L)
		for(int j = 0; j < a[nFeatures-1].size(); j++){
			lowerDelta[nFeatures-1][j] = a[nFeatures-1][j] - y[i][j];
		}

		//Cómputo de los demás lowerDelta^(l)
			//Esto ya se hace con armadillo, i need consulting, así que paro ya por hoy

		//Cálculo de upperDelta
	}
}

//A falta de testear
void NNMachine::forwardPropagation(std::vector<double> x, std::vector<double> a, std::vector<std::vector<double> > theta){
	for(int i=0; i<theta.size(); i++){
		for(int j = 0; j < theta[0].size(); j++){
			a[i] += theta[i][j]*x[j];
		}

		a[i] = sigmoid(a[i]);
	}
}

//A falta de testear
double NNMachine::cost(std::vector<double> h, std::vector<std::vector<double> > theta, std::vector<std::vector<double> > X, std::vector<std::vector<double> > y) {
	//Voy a hacer la ecuación tal cual está en las Lectures y las diapositivas de Andrew, no en los ejercicios

	//y es el vector de doubles procedentes de booleanos, que almacena si las puertas arden o no
	//X es el vector de vectores de doubles, que almacena los valores para cada entrada
	//h es en realidad el vector a(l) para la capa L, se pasa por parametro porque está precalculado, ya que luego se usará para el backpropagation
	//theta es la matriz de pesos para la capa L

	//Mirando ya a la ecuación...
	//La "m" de la ecuación sería y.size()
	//La "K" de la ecuación sería y[i].size()

	double J = 0.0;

	for(int i=0; i<y[0].size(); i++){
		for(int k = 0; k < y.size(); k++){
			J += (y[i][k]*std::log(h[k]))+((1-y[i][k])*log(1-h[k]));
		}
	}

	return -J/y.size();
}

double NNMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

void NNMachine::train() {
}
