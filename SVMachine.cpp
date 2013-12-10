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
	if(trainingSet.size() > 40 ){
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

void SVMachine::quadraticSolution() {
	int n = trainingSet.size();
	int m = 1; // Entiendo que es el numero de restricciones
	Program qp (CGAL::EQUAL);
	// Obtengo la X
	arma::mat X = arma::mat(n, nFeatures);
	for(int i=0; i<n; i++){
		for(int j=0; j<nFeatures; j++){
			X(i,j)=trainingSet[i].input[j];
		}
	}
//	std::cout << X;
	// Obtengo la Y
	arma::mat y = arma::mat(n, 1);
	for(int i=0; i<trainingSet.size(); i++){
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
			arma::mat aux = X.row(j)*X.row(i).t();
			ET daux(arma::as_scalar(aux*y.at(i)*y.at(j)));
//			std::cout << "El producto de " << i << "," << j << std::endl << aux;
			qp.set_d(i,j,daux);
//			std::cout << "La matriz auxiliar vale:" <<  daux << std::endl;
		}
	}

	 // solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());
	// print basic constraint indices (we know that there is only one: 1)
	std::cout << "Y la solución es: " << s << std::endl;
	arma::mat W = arma::mat(n,1);
	if (s.is_optimal()) { // we know that, don't we?
		std::cout << "La solución es óptima\n";
		int i = 0;
		for (Solution::Variable_value_iterator it = s.variable_values_begin(); it != s.variable_values_end(); ++it){
			double sv = CGAL::to_double(*it);
			std::cout << sv << std::endl;
			W(i) = sv;
			i++;
		}
		std::cout << std::endl;
		arma::mat sum = arma::zeros(1,nFeatures);
		std::cout << sum << std::endl;
		int lastSV = 0;
		for(int i=0; i<n; i++){
			std::cout << "El valor para la fila " << i << " es: " << W.at(i)*y.at(i)*X.row(i) << std::endl;
			// // Calculo la W
			if(W.at(i) != 0.0){
				arma::mat aux = W.at(i)*y.at(i)*X.row(i);
				sum += aux;
				std::cout << "El valor para la fila " << i << " es: " << sum << std::endl;
				lastSV = i; // Esto lo hago para obtener un sv que me resuelva la b
			}
		}
		std::cout << "El vector w es: " << sum;
		double b = arma::as_scalar(sum*X.row(lastSV).t());
		b = (1/y.at(lastSV) - b);
		std::cout << "Y la b vale: " << b << std::endl;
	} else std::cout << "No es optima, vete tu a saber por qué...\n";


	int p;
	std::cin >> p;
}

void SVMachine::trainByQuadraticProgramming() {
	quadraticSolution();
}

