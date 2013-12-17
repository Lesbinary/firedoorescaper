/*
 * NNMachine.cpp
 *
 *  Created on: 27/11/2013
 *      Author: alvaro
 */

#include <cmath>
#include "NNMachine.h"
#include "Utils.h"
#include "include/crandomgenerator.h"

//A falta de completar
NNMachine::NNMachine() { }

//A falta de completar
NNMachine::~NNMachine() { }

//A falta de completar
void NNMachine::pedirParametros() { }

//Completo
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
	} else {
		return false;
	}
}

//Completo
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

//Completo?
void NNMachine::clearTrainingSet() {
	trainingSet.clear();
	classifySuccesses=0;
}

//Tronco... yo que sé
double NNMachine::backPropagation(){
	//Con un trainingSet dado

	//Vectores auxiliares para construir matrices multidimensionales
	std::vector<std::vector<double> > v2;
	std::vector<double> v1;

	//Inicialización de upperDelta, y se imprime
	std::vector<std::vector<std::vector<double> > > upperDelta;

	for(int l = 0; l < L-1; l++){
		v2.clear();

		for(int j = 0; j < s_l[l]; j++){
			v1.clear();

			int num = s_l[l+1];

			if(l != L-2){
				num--;
			}

			for(int k = 0; k < num; k++){
				std::cout << "0 ";
				v1.push_back(0.0);
			}
			std::cout << std::endl;

			v2.push_back(v1);
		}
		std::cout << std::endl;

		upperDelta.push_back(v2);
	}

	//Thetas pasa de ser una matriz a ser un vector, y se imprime
	std::vector<double> thetas;

	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			int num = s_l[l+1];

			if(l != L-2){
				num--;
			}

			for(int k = 0; k < num; k++){
				std::cout << this->thetas[l][j][k] << " ";
				thetas.push_back(this->thetas[l][j][k]);
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	//Empieza el algoritmo

	//Para cada muestra
	for(int i = 0; i < nSamples; i++){
		std::cout << "Muestra " << i << std::endl;

		//Inicialización de lowerDelta, y se imprime
		std::vector<std::vector<double> > lowerDelta;

		for(int l = 1; l < L; l++){
			v1.clear();

			int num = s_l[l];

			if(l != L-1){
				num--;
			}

			for(int j = 0; j < num; j++){
				std::cout << "0 ";
				v1.push_back(0.0);
			}

			std::cout << std::endl;

			lowerDelta.push_back(v1);
		}

		//Inicializo las a's (con los bias)
		initA();

		//Asigno a la primera capa de a's los valores del input
		for(int j = 0; j < nFeatures; j++){
			a[0][j+1] = trainingSet[i].input[j];
		}

		//Cálculo de a^(l) mediante forward propagation
		forwardPropagation(thetas);

		//Uso de y^(i) para calcular lowerDelta^(L)
		//Usamos el indice 0 directamente porque sabemos que solo hay 1 output

		lowerDelta[L-2][0] = a[L-1][0] - y[i];

		std::cout << "El error final es " << lowerDelta[L-2][0] << std::endl;

		//Cómputo de los demás lowerDelta^(l)
		for(int l = L-3; l >=0; l--){
			for(int j = 0; j < s_l[l+1]-1; j++){

				int num = s_l[l+2];

				if(l != L-3){
					num--;
				}

				for(int k = 0; k < num; k++){
					std::cout << "Con lowerDelta anterior " << lowerDelta[l+1][k];
					std::cout << " y theta " << Utils::getElement(thetas,s_l,l+1,j+1,k);
					lowerDelta[l][j] += Utils::getElement(thetas,s_l,l+1,j+1,k)*lowerDelta[l+1][k];
					std::cout << " la siguiente es " << lowerDelta[l][j] << std::endl;
				}
			}
		}

		std::cout << "lowerDelta es " << std::endl;

		for(int l = 0; l < L-1; l++){
			int num = s_l[l+1];
			if(l != L-2){
				num--;
			}
			for(int j = 0; j < num; j++){
				std::cout << lowerDelta[l][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		std::cout << "Los valores de upperDelta para esta muestra son: " << std::endl;
		//Cálculo de upperDelta: es muy simple, suponemos que va
		for(int l = 0; l < L-1; l++){
			for(int j = 0; j < s_l[l]; j++){
				int num = s_l[l+1];

				if(l != L-2){
					num--;
				}

				for(int k = 0; k < num; k++){
					upperDelta[l][j][k] += a[l][j]*lowerDelta[l][k];
					std::cout << a[l][j]*lowerDelta[l][k] << " ";
				}

				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Muestro upperDelta" << std::endl;
	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			int num = s_l[l+1];

			if(l != L-2){
				num--;
			}

			for(int k = 0; k < num; k++){
				std::cout << upperDelta[l][j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::vector<double> D;
	std::vector<double> gradApprox;

	std::cout << "Estas son las Ds:" << std::endl;

	//Cálculo de la D : igualmente simple
	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			int num = s_l[l+1];

			if(l != L-2){
				num--;
			}

			if(j ==0){
				for(int k = 0; k < num; k++){
					double res = upperDelta[l][j][k]/this->y.size();

					std::cout << res << " ";

					D.push_back(res);
				}
			} else {
				for(int k = 0; k < num; k++){
					double res = upperDelta[l][j][k]/this->y.size();
					res += (lambda*Utils::getElement(thetas,s_l,l,j,k));

					std::cout << res << " ";

					D.push_back(res);
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	//hasta aquí va

	//A partir de aqui deberia funcionar todo con vectores

	//Ahora empezamos con el gradient check

	//Calculamos el gradApprox

	double epsilon = 0.001;

	for(int l = 0; l < L-1; l++){
		for(int j = 0; j < s_l[l]; j++){
			int num = s_l[l+1];

			if(l != L-2){
				num--;
			}

			for(int k = 0; k < num; k++){
				std::cout << l << " " << j << " " << k << std::endl;

				std::vector<double> thetasPlus(thetas);
				std::vector<double> thetasMinus(thetas);

				double element = Utils::getElement(thetas,this->s_l,l,j,k);

				Utils::setElement(thetasPlus,this->s_l,l,j,k,element+epsilon);
				Utils::setElement(thetasMinus,this->s_l,l,j,k,element-epsilon);

				std::cout << "Plus: ";
				for(int l = 0; l < thetasPlus.size(); l++){
					std::cout << thetasPlus[l] << " ";
				}
				std::cout << std::endl;

				std::cout << "Minus: ";
				for(int l = 0; l < thetasMinus.size(); l++){
					std::cout << thetasMinus[l] << " ";
				}
				std::cout << std::endl;

				double cP = cost(thetasPlus);
				double cM = cost(thetasMinus);
				double cT = (cP-cM)/(2.0*epsilon);

				std::cout << "El coste de thetasPlus es " << cP << std::endl;
				std::cout << "El coste de thetasMinus es " << cM << std::endl;
				std::cout << "El coste final es " << cT << std::endl;
				std::cout << std::endl;

				gradApprox.push_back(cT);
				std::cout << std::endl;
			}
		}
	}

	//Si graddApprox es igual que D, el backpropagation se hizo bien

	double res = 0.0;

	for(int l = 0; l < D.size(); l++){
		double pres = D[l] - gradApprox[l];

		if(pres < 0.0){
			pres *=-1;
		}

		res += pres;

//		std::cout << "En D es " << D[l] << " y en gradApprox es " << gradApprox[l] << std::endl;
	}

	std::cout << "La diferencia final es " << res << std::endl;

	return res;
}

//Revisado
void NNMachine::forwardPropagation(std::vector<double> theta){
	for(int l = 0; l < L-1; l++){
		for(int i = 0; i<s_l[l+1]; i++){
			//En la última capa, no excluimos el bias (porque no hay)
			if(l == L-2){
				for(int j = 0; j < s_l[l]; j++){
//					std::cout << "La anterior es " << a[l][j];
//					std::cout << ", la theta " << Utils::getElement(theta,this->s_l,l,j,i);
					a[l+1][i] += Utils::getElement(theta,this->s_l,l,j,i)*a[l][j];
//					std::cout << ", la siguiente " << a[l+1][i] << std::endl;
				}

				a[l+1][i] = sigmoid(a[l+1][i]);

//				std::cout << "y su sigmoide " << a[l+1][i] << std::endl;
			} else {
				//sin embargo en todas las demás sí lo excluimos
				if(i != 0){
					for(int j = 0; j < s_l[l]; j++){
//						std::cout << "La anterior es " << a[l][j];
//						std::cout << ", la theta " << Utils::getElement(theta,this->s_l,l,j,i-1);
						a[l+1][i] += Utils::getElement(theta,this->s_l,l,j,i-1)*a[l][j];
//						std::cout << ", la siguiente " << a[l+1][i] << std::endl;
					}

					a[l+1][i] = sigmoid(a[l+1][i]);

//					std::cout << "y su sigmoide " << a[l+1][i] << std::endl;
				}
			}

//			std::cout << std::endl;
		}

//		std::cout << std::endl;
	}

//	std::cout << std::endl;
}

//Revisado
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

	std::vector<double> h;

	//Para cada muestra, calculo la h final
	for(int i = 0; i < nSamples; i++){
		initA();

		//Asigno a la primera capa de a's los valores del input
		for(int j = 0; j < nFeatures; j++){
			a[0][j+1] = trainingSet[i].input[j];
		}

		//Cálculo de a^(l) mediante forward propagation
		forwardPropagation(thetas);

		//Me guardo en h solo los resultados finales
		h.push_back(a[this->L-1][0]);
	}

	//Calculo el primer elemento de la ecuación de coste
	double J = 0.0;

	for(int i=0; i < nSamples; i++){
//		std::cout << "J suma y=" << y[i] << "*h=" << h[i] << std::endl;
		J += (y[i]*std::log(h[i]))+((1-y[i])*log(1-h[i]));
	}

	J /= (-nSamples);

	//Y el segundo elemento, de regularización
	double R = 0.0;

	for(int l = 0; l < L-2; l++){
		for(int j = 0; j < s_l[l]; j++){
			int num = s_l[l+1];

			if(l != L-3){
				num--;
			}

			for(int k = 0; k < num; k++){
				R += pow(Utils::getElement(thetas,s_l,l,j,k),2);
			}
		}
	}

	R *= lambda;
	R /= (2*this->nSamples);

	return J+R;
}

//FUNCIONA
double NNMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

void NNMachine::train() {
	std::cout << "Probando lambdas de 0 a 9..." << std::endl;

	std::vector<double> resultados;

	std::cout << "Empieza el entrenamiento" << std::endl;

	nFeatures = trainingSet[0].getNFeatures();
	nSamples = trainingSet.size();

	std::cout << "Hay " << nFeatures << " caracteristicas de entrada" << std::endl;

	//Rellenamos el vector que almacena los outputs de los samples
	fillY();

	//Inicializamos el vector de tamaños de la red neuronal según el tamaño del vector de entrada
	//Lo de que son 4 capas y la ultima es de tamaño 1 lo hardcodeamos aqui
	s_l.push_back(nFeatures+1);
	s_l.push_back(nFeatures+1);
	s_l.push_back(nFeatures+1);
	s_l.push_back(1);

	L = s_l.size();

	//Random Initialization del vector de pesos Thetas
	initTheta();

	Utils::scalation(trainingSet);

	for(int i = 0; i < 10; i++){
		lambda = i+1;

		double tmp = backPropagation();

		resultados.push_back(tmp);
	}

	for(int i = 1; i < resultados.size()+1; i++){
		std::cout << "Lambda " << i << " y resultado " << resultados[i-1] << std::endl;
	}

	std::cout << "I'm finished. Entrando en bucle..." << std::endl;

	while(1){}
}

//FUNCIONA
void NNMachine::initA(){
	a.clear();

	std::vector<double> v1;

	for(int l = 0; l < L; l++){//De atras adelante, por capas
		v1.clear();

		for(int j = 0; j < s_l[l]; j++){//De adelante atras, por niveles
			if(j == 0 && l != L-1) {
//				std::cout << "1 ";
				v1.push_back(1.0);
			} else {
//				std::cout << "0 ";
				v1.push_back(0.0);
			}
		}
//		std::cout << std::endl;

		a.push_back(v1);
	}
}

//FUNCIONA
void NNMachine::initTheta(){
	thetas.clear();

	std::vector<std::vector<double> > v2;
	std::vector<double> v1;

	srand(time(NULL));

	for(int l = 0; l < L-1; l++){
		v2.clear();

		for(int j = 0; j < s_l[l]; j++){
			v1.clear();

			int num = s_l[l+1];

			if(l != L-2){
				num--;
			}

			for(int k = 0; k < num; k++){
				double random = FireDoorEscaper::CRandomGenerator::CRNDGEN.uniformRandomDouble(-9,9);

				if(random == 0){
					random++;
				}

				v1.push_back(random);
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
