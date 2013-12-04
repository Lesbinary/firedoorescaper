/*
 * NNMachine.cpp
 *
 *  Created on: 27/11/2013
 *      Author: alvaro
 */

#include "NNMachine.h"
#include "Utils.h"

//A falta de completar
NNMachine::NNMachine() {
}

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

	if(trainingSet.size() > 3 ){
		train();
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
	trainingSet.clear();
	classifySuccesses=0;
}

//A falta de completar
void NNMachine::backPropagation(){
	//Con un trainingSet dado

	//Vectores auxiliares para construir matrices
	std::vector<std::vector<double> > v2;
	std::vector<double> v1;

	std::vector<std::vector<double> > lowerDelta;
	std::vector<std::vector<std::vector<double> > > upperDelta;

	//Inicialización de upperDelta
	for(int l = 0; l < L-1; l++){
		v2.clear();

		for(int j = 0; j < s_l[l]; j++){
			v1.clear();

			for(int k = 0; k < s_l[l+1]; k++){
				v1.push_back(0.0);
			}

			v2.push_back(v1);
		}

		upperDelta.push_back(v2);
	}

	//Inicialización de lowerDelta
	for(int l = 1; l < L; l++){
		v1.clear();

		for(int j = 0; j < s_l[l]; j++){
			v1.push_back(0.0);
		}

		lowerDelta.push_back(v1);
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
		std::cout << "Muestra " << i << std::endl;

		initA();

		a[0] = trainingSet[i].input;

		//Cálculo de a^(l) mediante forward propagation
		forwardPropagation(thetas);

		//Uso de y^(i) para calcular lowerDelta^(L)
		//Usamos el indice 0 directamente porque sabemos que solo hay 1 output

		lowerDelta[L-2][0] = a[L-1][0] - y[i];

		std::cout << "El error final es " << lowerDelta[L-2][0] << std::endl;

		//Cómputo de los demás lowerDelta^(l)
		for(int l = L-3; l >=0; l--){//De atras adelante, por capas
			for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
				for(int k = 0; k < s_l[l+1]; k++){//todas las thetas
					lowerDelta[l][j] += Utils::getElement(thetas,s_l,l,j,k)*lowerDelta[l+1][k];//puede que me haya liado con los índices
				}
			}
		}

//LOWERDELTA SE CALCULA BIEN

		//Cálculo de upperDelta: es muy simple, suponemos que va
		for(int l = 0; l < L-1; l++){
			for(int j = 0; j < s_l[l]; j++){
				for(int k = 0; k < s_l[l+1]; k++){
					upperDelta[l][j][k] += a[l][j]*lowerDelta[l][k];
				}
			}
		}
	}

	std::cout << "Muestro upperDelta" << std::endl;
	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			for(int k = 0; k < s_l[l+1]; k++){
				std::cout << l << " " << j << " " << k << std::endl;
				std::cout << upperDelta[l][j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<double> D;
	std::vector<double> gradApprox;

	//Cálculo de la D : igualmente simple
	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			for(int k = 0; k < s_l[l+1]; k++){
				D.push_back(upperDelta[l][j][k]/this->y.size());
			}
		}
	}

	//hasta aquí va

	//A partir de aqui deberia funcionar todo con vectores

	//Ahora empezamos con el gradient check

	//Calculamos el gradApprox

	double epsilon = 0.001;

	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			for(int k = 0; k < s_l[l+1]; k++){
				std::vector<double> thetasPlus(thetas);
				std::vector<double> thetasMinus(thetas);

				double element = Utils::getElement(thetas,this->s_l,l,j,k);

				Utils::setElement(thetasPlus,this->s_l,l,j,k,element+epsilon);
				Utils::setElement(thetasMinus,this->s_l,l,j,k,element-epsilon);



				std::cout << "El coste de thetasPlus es " << cost(thetasPlus) << std::endl;
				std::cout << "El coste de thetasMinus es " << cost(thetasMinus) << std::endl;

				gradApprox.push_back((cost(thetasPlus)-cost(thetasMinus))/(2.0*epsilon));
			}
		}
	}

	//Si graddApprox es igual que D, el backpropagation se hizo bien

	for(int l = 0; l < D.size(); l++){
		std::cout << "En D es " << D[l] << " y en gradApprox es " << gradApprox[l] << std::endl;
	}

	while(1){}
}

//FUNCIONA
void NNMachine::forwardPropagation(std::vector<double> theta){
	for(int l = 0; l < theta.size(); l++){
		std::cout << theta[l] << " ";
	}
	std::cout << std::endl;

	for(int l = 0; l < this->L-1; l++){
		for(int i = 0; i<this->s_l[l]; i++){
			for(int j = 0; j < this->s_l[l+1]; j++){
				std::cout << "La anterior es " << a[l][j];
				a[l+1][i] += Utils::getElement(theta,this->s_l,l,i,j)*a[l][j];
				std::cout << ", la siguiente " << a[l+1][i];
			}

			a[l+1][i] = sigmoid(a[l+1][i]);
			std::cout << " y su sigmoide " << a[l+1][i] << std::endl;
		}
	}
}

//FUNCIONA
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

	for(int l = 0; l < thetas.size(); l++){
		std::cout << thetas[l] << " ";
	}
	std::cout << std::endl;

	double J = 0.0;

	std::vector<double> h;

	//Para cada muestra
	for(int i = 0; i < this->nSamples; i++){
		initA();

		a[0] = trainingSet[i].input;

		//Cálculo de a^(l) mediante forward propagation
		forwardPropagation(thetas);

		//Me guardo en h solo los resultados finales
		h.push_back(a[this->L-1][0]);
	}

	for(int l = 0; l < h.size(); l++){
		std::cout << h[l] << " ";
	}
	std::cout << std::endl;

	//Calculo la J
	for(int i=0; i<this->nSamples; i++){
		J += (y[i]*std::log(h[i]))+((1-y[i])*log(1-h[i]));
	}

	return -J/this->nSamples;
}

//FUNCIONA
double NNMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

void NNMachine::train() {
	std::cout << "Empieza el entrenamiento" << std::endl;

	nFeatures = trainingSet[0].getNFeatures();
	nSamples = trainingSet.size();

	std::cout << "Hay " << nFeatures << " caracteristicas de entrada" << std::endl;

	//Rellenamos el vector que almacena los outputs de los samples
	fillY();

	//Inicializamos el vector de tamaños de la red neuronal según el tamaño del vector de entrada
	//Lo de que son 4 capas y la ultima es de tamaño 1 lo hardcodeamos aqui
	s_l.push_back(nFeatures);
	s_l.push_back(nFeatures);
	s_l.push_back(nFeatures);
	s_l.push_back(1);

	L = s_l.size();

	//Random Initialization del vector de pesos Thetas (que es 3)
	initTheta();

	//Inicialización del vector de a's
	initA();

	backPropagation();
}

//FUNCIONA
void NNMachine::initA(){
	a.clear();

	std::vector<double> v1;

	for(int l = 0; l < L; l++){//De atras adelante, por capas
		v1.clear();

		for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
			v1.push_back(0.0);
		}

		a.push_back(v1);
	}
}

//FUNCIONA
void NNMachine::initTheta(){
	thetas.clear();

	std::vector<std::vector<double> > v2;
	std::vector<double> v1;

	for(int l = 0; l < L-1; l++){
		v2.clear();

		for(int j = 0; j < s_l[l]; j++){
			v1.clear();

			for(int k = 0; k < s_l[l+1]; k++){
				v1.push_back(3.0);//This must be rand
			}

			v2.push_back(v1);
		}

		thetas.push_back(v2);
	}
}

//FUNCIONA
void NNMachine::fillY(){
	y.clear();

	for(int i=0; i<nSamples; i++){
		if(trainingSet[i].burn){
			y.push_back(1.0);
		} else {
			y.push_back(0.0);
		}
	}
}
