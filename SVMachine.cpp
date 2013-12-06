/*
 * SVMachine.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: antonio
 */

#include "SVMachine.h"

SVMachine::SVMachine() {
	// TODO Auto-generated constructor stub

}

SVMachine::~SVMachine() {
	// TODO Auto-generated destructor stub
}

void SVMachine::addTrainingSample(Sample sample) {
}

bool SVMachine::isTrainingReady() {
	return false;
}

bool SVMachine::isReadyToCross() {
	return false;
}

void SVMachine::classifySample(Sample sample) {
}

bool SVMachine::isDoorOnFire(double input[]) {
}

void SVMachine::clearTrainingSet() {
}

void SVMachine::pedirParametros() {
}

void SVMachine::quadraticSolution() {
	// Inicializo la programacion cuadratica
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	// Seteo la matriz de acotacion (y'*alpha=0)
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			qp.set_a(1,i,1);
		else qp.set_a(1,i,0);
		qp.set_b(i,0);
		qp.set_r(i, CGAL::EQUAL);
		// Seteo c (linear) [Esto lo hago aquí pa quitar un bucle. Ya lo optimizare mas]
		qp.set_c(i,-1); // Segun San Yasser esto es to -1
	}
	// Seteo las cotas de alpha
	qp.set_l(0,true,0); qp.set_u(0,false,0); // 0 <= alpha <= infinito
	// Seteo la symmetric positive-semidefinite matrix
	// Obtengo la X
	arma::mat X = arma::mat(trainingSet.size(), nFeatures);
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<nFeatures; j++){
			X(i,j)=trainingSet[i].input[j-1];
		}
	}
	// Obtengo la Y
	arma::mat y = arma::mat(trainingSet.size(), 1);
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			y(i)=1;
		else y(i)=0;
	}
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<trainingSet.size(); j++){
			std::cout << X.col(1).t()*X.col(1)*y(i)*y(j);
		}
	}
}
