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
	trainingSet.push_back(sample);
}

bool SVMachine::isTrainingReady() {
	if(trainingSet.size() == 1){
		nFeatures=trainingSet[0].getNFeatures();
	}
	if(trainingSet.size() > 100 ){
		trainByQuadraticProgramming();
		return true;
	} else return false;
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

void SVMachine::trainByQuadraticProgramming() {
	quadraticSolution();
}

void SVMachine::quadraticSolution() {
	// Inicializo la programacion cuadratica
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	// Seteo la matriz de acotacion (y'*alpha=0)
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			qp.set_a(0,i,1);
		else qp.set_a(0,i,0);
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
			X(i,j)=trainingSet[i].input[j];
		}
	}
//	std::cout << X;
	// Obtengo la Y
	arma::mat y = arma::mat(trainingSet.size(), 1);
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			y(i)=1;
		else y(i)=0;
	}
//	std::cout << y;
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<=i; j++){
			arma::mat aux = X.row(i)*X.row(j).t();
			qp.set_d(i,j,aux.at(0,0)*y.at(i)*y.at(j));
			std::cout << "La matriz auxiliar vale:\n" <<  aux;
		}
	}
	 // solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());
	// print basic constraint indices (we know that there is only one: 1)
	if (s.is_infeasible())
		 std::cout << " is not in the convex hull\n";
	if (s.is_optimal()) { // we know that, don't we?
		std::cout << "Basic constraints: ";
		for (Solution::Index_iterator it = s.basic_constraint_indices_begin(); it != s.basic_constraint_indices_end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	} else std::cout << "No es optima, vete tu a saber por qué...\n";
	if(s.is_valid()){
		std::cout << "Pero es válida...\n";
		std::cout << "Y la solución es: " << s << std::endl;
	}
	int p;
	std::cin >> p;
}
