/*
 * NNMachine.cpp
 *
 *  Created on: 27/11/2013
 *      Author: alvaro
 */

#include "NNMachine.h"
#include "Utils.h"

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
			nSamples=trainingSet[0].getNFeatures();
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

	//Thetas pasa a ser un vector, para poder ser usado
	std::vector<double> thetas;

	for(int l = 0; l < this->thetas.size(); l++){
		for(int j = 0; j < this->thetas[l].size(); j++){
			for(int k = 0; k < this->thetas[l][j].size(); k++){
				thetas.push_back(this->thetas[l][j][k]);
			}
		}
	}

	//Empieza el algoritmo
	//Para cada muestra
	for(int i = 0; i < this->nSamples; i++){
		a[0] = trainingSet[i].input;

		//Cálculo de a^(l) mediante forward propagation
		for(int l = 1; l < this->thetas.size()-1; l++){
			forwardPropagation(a[l-1],a[l],thetas,l-1);
		}

		//Uso de y^(i) para calcular lowerDelta^(L)
		for(int j = 0; j < a[nSamples-1].size(); j++){
			lowerDelta[nSamples-1][j] = a[nSamples-1][j] - y[i][j];
		}

		//Cómputo de los demás lowerDelta^(l)
		for(int l = L-2; l >=0; l--){//De atras adelante, por capas
			for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
				for(int k = 0; k < s_l[l+1]; k++){//todas las thetas
					lowerDelta[l][j] += Utils::getElement(thetas,s_l,l,j,k)*lowerDelta[l+1][k];//puede que me haya liado con los índices
				}
			}
		}

		//Cálculo de upperDelta
		for(int l = L-2; l >=0; l--){//De atras adelante, por capas
			for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
				for(int k = 0; k < s_l[l+1]; k++){//todas las thetas
					upperDelta[l][j][k] += a[l][j]*lowerDelta[l+1][k];
				}
			}
		}
	}

	std::vector<double> D;
	std::vector<double> gradApprox;

	//Cálculo de la D
	for(int l = 0; l < L-1; l++){//De atras adelante, por capas
		for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
			for(int k = 0; k < s_l[l+1]; k++){//todas las thetas
				D.push_back(upperDelta[l][j][k]/this->y.size());
			}
		}
	}

	//A partir de aqui deberia funcionar todo con vectores

	//Ahora empezamos con el gradient check, una vez tenemos las D

	//Convertimos D en un vector

	//Calculamos el gradApprox

	double epsilon = 0.001;

	for(int l = 0; l < L-1; l++){//De atras adelante, por capas
		for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
			for(int k = 0; k < s_l[l+1]; k++){//todas las thetas
				std::vector<double> thetasPlus(thetas);
				std::vector<double> thetasMinus(thetas);

				double element = Utils::getElement(thetasPlus,this->s_l,l,j,k);

				Utils::setElement(thetasPlus,this->s_l,l,j,k,element+epsilon);
				Utils::setElement(thetasMinus,this->s_l,l,j,k,element-epsilon);

				gradApprox.push_back((cost(thetasPlus)-cost(thetasMinus))/2*epsilon);
			}
		}
	}

	//Si graddApprox es igual que D, el backpropagation se hizo bien
}

//A falta de testear
void NNMachine::forwardPropagation(std::vector<double> x, std::vector<double> a, std::vector<double> theta, int l){
	for(int i=0; i<this->thetas[l].size(); i++){
		for(int j = 0; j < this->thetas[l][i].size(); j++){
			a[i] += Utils::getElement(theta,this->s_l,l,i,j)*x[j];
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

	std::vector<std::vector<double> > a;

	for(int i = 0; i < this->nSamples; i++){
		a.push_back(trainingSet[i].input);

		//Cálculo de a^(l) mediante forward propagation
		for(int l = 1; l < this->L-1; l++){
			forwardPropagation(a[l-1],a[l],thetas,l);
		}

		//Me guardo en h solo los resultados finales
		std::vector<double> h;

		for(int l = 0; l < a[this->L].size(); l++){
			h.push_back(a[this->L][l]);
		}

		//Calculo la J
		for(int i=0; i<y[0].size(); i++){
			for(int k = 0; k < this->nSamples; k++){
				J += (y[i][k]*std::log(h[k]))+((1-y[i][k])*log(1-h[k]));
			}
		}
	}

	return -J/this->nSamples;
}

double NNMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

void NNMachine::train() {
}
