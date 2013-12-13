/*
 * SVMachine.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: antonio
 */

#include "SVMachine.h"

SVMachine::SVMachine() {
	kernel = new LinearKernel();
	classifySuccesses = 0;
	nFeatures = 0;
}

SVMachine::SVMachine(KernelType t) {
	classifySuccesses = 0;
	nFeatures = 0;
	switch(t){
	case Linear: kernel = new LinearKernel();
		break;
	case Polynomial: kernel = new PolynomialKernel(2);
		break;
	case RBF: kernel = new RBFKernel();
		break;
	default: kernel = new LinearKernel();
	}
}

SVMachine::~SVMachine() {
	// TODO Auto-generated destructor stub
}

void SVMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

bool SVMachine::isTrainingReady() {
	if(trainingSet.size() > 0){
		if(trainingSet.size() == 1)
			nFeatures=trainingSet[0].getNFeatures();
		if(trainingSet.size() > nFeatures*7 ){
			trainByQuadraticProgramming();
			return true;
		}
	} else return false;
}

bool SVMachine::isReadyToCross() {
	return classifySuccesses > 10;
}

void SVMachine::classifySample(Sample sample) {
	ET aux(0.0);
	arma::Col<double> Input(sample.getNFeatures());
	for(int i=0; i<sample.getNFeatures(); i++)
		Input(i)=sample.input[i];
	for(int i=0; i<trainingSet.size(); i++){
		if(SupportVectors.at(i) > 0.0){
			aux += ET(SupportVectors.at(i))*ET(y.at(i))*kernel->K(X.row(i).t(), Input);
//			std::cout << "La suma auxiliar vale: " << aux+b << std::endl;
		}
	}
	double p = CGAL::to_double(aux + b);
	std::cout << "Para este sample tenemos una p de: " << p << std::endl;
	if((p>1 && sample.burn) || (p<=-1 && !sample.burn)){
		if(p>1)
			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
		else if(p<-1) std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
		std::cout << "Ha clasificao de puta madre" << std::endl;
		this->classifySuccesses++;
	} else if ((p<=-1 && sample.burn) || (p>1 && !sample.burn)){
		if(p>1)
			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
		else if(p<-1) std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
		std::cout << "Pinyico... volviendo a entrenar" << std::endl;
//		this->trainingSet.push_back(sample);
//		this->trainByQuadraticProgramming();
		this->classifySuccesses--;
	} else std::cout << "No se que carajo ha pasado" << std::endl;
	std::cout << "He clasificado correctamente " << classifySuccesses << std::endl;
}

bool SVMachine::isDoorOnFire(double input[]) {
	ET aux(0.0);
	arma::Col<double> Input(nFeatures);
	for(int i=0; i<nFeatures; i++)
		Input(i)=input[i];
	for(int i=0; i<trainingSet.size(); i++){
		if(SupportVectors.at(i) > 0.0){
			aux += ET(SupportVectors.at(i))*ET(y.at(i))*kernel->K(X.row(i).t(), Input);
			std::cout << "La suma auxiliar vale: " << aux+b << std::endl;
		}
	}
	double p = CGAL::to_double(aux + b);
	std::cout << "La probabilidad de que la siguiente puerta esté caliente es: " << p << std::endl;
	if(p>1)
		return true;
	else if(p<-1) return false;

	return true;
}

void SVMachine::clearTrainingSet() {
	trainingSet.clear();
	classifySuccesses=0;
}

void SVMachine::pedirParametros() {
}

void SVMachine::quadraticSolution() {
	int n = trainingSet.size();
	int m = 1; // Entiendo que es el numero de restricciones
	Program qp (CGAL::EQUAL);
	// Obtengo la X
	X = arma::mat(n, nFeatures);
	for(int i=0; i<n; i++){
		for(int j=0; j<nFeatures; j++){
			X(i,j)=trainingSet[i].input[j];
		}
	}
//	std::cout << X;
	// Obtengo la Y
	y = arma::mat(n, 1);
	for(int i=0; i<n; i++){
		if(trainingSet[i].burn)
			y(i)=1;
		else y(i)=-1;
	}

//	std::cout << y;
	// Seteo la restriccion
	for(int i=0; i<n; i++){
		qp.set_a(i,0,ET(y.at(i)));
		qp.set_l(i,true,ET(0));
		qp.set_u(i,false);
		qp.set_c(i,ET(-1));
		//std::cout << "y(" << i << "): " << y.at(i) << std::endl;
	}
	qp.set_b(0,ET(0));
	qp.set_r(0,CGAL::EQUAL);
	qp.set_c0(ET(0));

	// Seteo la symmetric positive-semidefinite matrix
	for(int i=0; i<n; i++){
		for(int j=0; j<=i; j++){
			ET ip = kernel->K(X.row(i).t(),X.row(j).t());
			std::cout << "El kernel para " << i << "," << j << " nos dice que el innerproduct es: " << ip << std::endl;
			ET daux = ip*ET(y.at(i))*ET(y.at(j));
//			std::cout << "El producto de " << i << "," << j << std::endl << aux;
			qp.set_d(i,j,daux);
//			std::cout << "La matriz auxiliar vale:" <<  daux << std::endl;
		}
	}

	 // solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());
	// print basic constraint indices (we know that there is only one: 1)
	std::cout << "Y la solución es: " << s << std::endl;
//	arma::mat W = arma::mat(n,1);
	this->SupportVectors = arma::mat(n,1);
	ET sumaB(0.0);
	if (s.is_optimal()) { // we know that, don't we?
		int i = 0;
		for (Solution::Variable_value_iterator it = s.variable_values_begin(); it != s.variable_values_end(); ++it){
			this->SupportVectors(i) = CGAL::to_double(*it);
			if(SupportVectors.at(i) != 0.0){
				this->m = i; // Esto lo hago para obtener un sv que me resuelva la b
			}
			i++;
		}
		// Calculo la b
		for(int i=0; i<n; i++)
			if(SupportVectors.at(i) != 0.0)
				sumaB += ET(SupportVectors.at(i))*ET(y.at(i))*kernel->K(X.row(i).t(), X.row(this->m).t());
		this->b = ET(y(this->m)) - sumaB;
		std::cout << "Y el valor de b es: "<< this->b << std::endl;
	} else std::cout << "No es optima, vete tu a saber por qué...\n";

	int pausa; std::cin >> pausa;
}

void SVMachine::trainByQuadraticProgramming() {
	quadraticSolution(); // Esto me da los Support Vectors

}

