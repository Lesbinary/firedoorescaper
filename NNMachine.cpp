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

	std::vector<std::vector<double> > lowerDelta;
	std::vector<std::vector<std::vector<double> > > upperDelta;

	//Inicialización de upperDelta
	for(int l = 0; l < this->thetas.size(); l++){
		for(int j = 0; j < this->thetas[l].size(); j++){
			for(int k = 0; k < this->thetas[l][j].size(); k++){
				upperDelta[l][j][k] = 0.0;
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
		for(int l = L-2; l >=0; l--){//De atras adelante, por capas
			for(int j = 0; j < thetas[l].size(); j++){//De adelante atras, por niveles
				for(int k = 0; k < thetas[l][j].size(); k++){//todas las thetas
					lowerDelta[l][j] += thetas[l][j][k]*lowerDelta[l+1][k];//puede que me haya liado con los índices
				}
			}
		}

		//Cálculo de upperDelta
		for(int l = L-2; l >=0; l--){//De atras adelante, por capas
			for(int j = 0; j < thetas[l].size(); j++){//De adelante atras, por niveles
				for(int k = 0; k < thetas[l][j].size(); k++){//todas las thetas
					upperDelta[l][j][k] += a[l][j]*lowerDelta[l+1][k];
				}
			}
		}
	}

	std::vector<std::vector<std::vector<double> > > D;

	//Cálculo de la D
	for(int l = 0; l < this->thetas.size(); l++){
		for(int j = 0; j < this->thetas[l].size(); j++){
			for(int k = 0; k < this->thetas[l][j].size(); k++){
				D[l][j][k] = upperDelta[l][j][k]/this->y.size();
			}
		}
	}

	//A partir de aqui deberia funcionar todo con vectores

	//Ahora empezamos con el gradient check, una vez tenemos las D

	//Convertimos D en un vector

	//Calculamos el gradApprox

	double epsilon = 0.001;

	for(int l = 0; l < this->thetas.size(); l++){
		for(int j = 0; j < this->thetas[l].size(); j++){
			for(int k = 0; k < this->thetas[l][j].size(); k++){
				std::vector<std::vector<std::vector<double> > > thetasPlus(this->thetas);
				std::vector<std::vector<std::vector<double> > > thetasMinus(this->thetas);

				thetasPlus[l][j][k] += epsilon;
				thetasMinus[l][j][k] -= epsilon;

				//y ahora la funcion de costWHAT
				std::vector<std::vector<double> > as;

				//cost(as,thetasPlus,trainingSet[i].input,)
			}
		}
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
double NNMachine::cost(std::vector<double> thetas) {
	//Voy a hacer la ecuación tal cual está en las Lectures y las diapositivas de Andrew, no en los ejercicios

	//y es el vector de doubles procedentes de booleanos, que almacena si las puertas arden o no
	//X es el vector de vectores de doubles, que almacena los valores para cada entrada
	//h es en realidad el vector a(l) para la capa L, se pasa por parametro porque está precalculado, ya que luego se usará para el backpropagation
	//theta es la matriz de pesos para la capa L

	//Mirando ya a la ecuación...
	//La "m" de la ecuación sería y.size()
	//La "K" de la ecuación sería y[i].size()

	//Usaremos Utils::getElement(thetas,this->s_l,l,j,k) para acceder al elemento

	double J = 0.0;

	/*
	std::vector<std::vector<double> > a;

	for(int i = 0; i < this->nFeatures; i++){
			a.push_back(trainingSet[i].input);

			//Cálculo de a^(l) mediante forward propagation
			for(int l = 1; l < this->thetas.size()-1; l++){
				forwardPropagation(a[l-1],a[l],thetas[l-1]);
			}

	a[0] = X;

	for(int l = 1; l < this->thetas.size()-1; l++){
		forwardPropagation(a[l-1],a[l],thetas[l-1]);
	}

	for(int i=0; i<y[0].size(); i++){
		for(int k = 0; k < y.size(); k++){
			J += (y[i][k]*std::log(h[k]))+((1-y[i][k])*log(1-h[k]));
		}
	}
	*/
	return -J/y.size();
}

double NNMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

void NNMachine::train() {
}
