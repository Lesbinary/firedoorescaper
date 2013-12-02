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
	alphaTrain = 0.01;
	trainType = 1; //1 normal, 2 gradiente
}


LRMachine::~LRMachine() {
	// TODO Auto-generated destructor stub
}


void LRMachine::pedirParametros(){

	std::cout << "1.Normal" << std::endl;
	std::cout << "2.Descenso por gradiente" << std::endl;
	std::cout << "Elige el modo de calculo del error: ";
	std::cin >> trainType;

	system("cls");
	if(trainType == 2){
		std::cout << "Introduce el valor de alpha: ";
		std::cin >> alphaTrain;
		system("cls");
		std::cout << "Introduce el numero de iteraciones: ";
		std::cin >> iterTrain;
		system("cls");
	 }
}
void LRMachine::addTrainingSample(Sample sample) {
	trainingSet.push_back(sample);
}

bool LRMachine::isTrainingReady() {
	if(trainingSet.size() == 1){
		nFeatures=trainingSet[0].getNFeatures();
	}
	if(trainingSet.size() > 20 ){
		if(trainType == 2)trainByGradient(iterTrain, alphaTrain);
		else trainByNormalEcuation();
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
			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
		else std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
		std::cout << "Ha clasificao de puta madre" << std::endl;
		this->classifySuccesses++;
	} else if ((p<=0.5 && sample.burn) || (p>0.5 && !sample.burn)){
		if(p>0.5)
			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
		else std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
		std::cout << "Pinyico... volviendo a entrenar" << std::endl;
		this->trainingSet.push_back(sample);
		if(trainType == 2)this->trainByGradient(iterTrain, alphaTrain);
		else this->trainByNormalEcuation();
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
	std::cout << "La probabilidad de que la siguiente puerta esté caliente es: " << p << std::endl;
//	if(p>0.4 && p <0.6)
	if(p>0.40)
		return true; // Esto es un truquillo para no jugarsela en un rango de más indecisión
//	if(p>0.5)
//		return true;
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

double LRMachine::cost(std::vector<double> theta, std::vector<std::vector<double> > X, std::vector<double> y) {
	double J = 0.0;
	for(int i=0; i<y.size(); i++){
		// Calculo el valor de la hipótises para la theta dada
		double h = 0.0;
		for(int j=0; j<theta.size(); j++){
			h += theta[j]*X[i][j];
		}
		h = sigmoid(h);
		// Calculo el valor del coste para la theta dada
		J+=(-y[i]*std::log(h))-((1-y[i])*std::log(1-h));
	}
	return J/y.size();
}

void LRMachine::grad(std::vector<double> tetha, std::vector<std::vector<double> > X, std::vector<double> y, std::vector<double> grad) {
	for(int j=0; j<theta.size(); j++){
		double parcial = 0.0;
		for(int i=0; i<y.size(); i++){
			// Calculo el valor de la hipótises para la theta dada
			double h = 0.0;
			for(int k=0; k<theta.size(); k++){
				h += theta[k]*X[i][k];
			}
			h = sigmoid(h);
			parcial += (h-y[i])*X[i][j];
		}
		grad[j] = parcial/theta.size();
	}
}

void LRMachine::trainByGradientAdvanced(int iter, double alpha) {
//	int i, ret = 0;
//	lbfgsfloatval_t fx;
//	lbfgsfloatval_t *theta = lbfgs_malloc(X.size());
//	lbfgs_parameter_t param;
//
//	if (theta == NULL) {
//		printf("ERROR: Failed to allocate a memory block for variables.\n");
//	}
//
//	/* Initialize the variables. */
//	for (i = 0;i < X.size();i += 2) {
//		theta[i] = this->theta[i];
//	}
//
//	/* Initialize the parameters for the L-BFGS optimization. */
//	lbfgs_parameter_init(&param);
//	/*param.linesearch = LBFGS_LINESEARCH_BACKTRACKING;*/
//
//	/*
//		Start the L-BFGS optimization; this will invoke the callback functions
//		evaluate() and progress() when necessary.
//	 */
//	ret = lbfgs(X.size(), theta, NULL, evaluateLR, progressLR, NULL, &param);
//
//	/* Report the result. */
//	printf("L-BFGS optimization terminated with status code = %d\n", ret);
//	printf("  fx = %f, x[0] = %f, x[1] = %f\n", fx, theta[0], theta[1]);
//
//	lbfgs_free(theta);
}

void LRMachine::trainByGradient(int iter, double alpha) {
	double vari = 0.01;
	double pCoste = 0.0;
	std::vector<double> gradiente;
	fillX();
	fillTheta();
	fillY();

	for(int k=0; k<iter; k++){
		// Calculo el coste
		double coste = cost(theta, X, y);
		std::cout << "Para la iteración " << k << " el coste es: " << coste << std::endl;
		// Recalculo theta para la siguiente iteracion
		grad(theta, X, y, gradiente);
//		std::cout << "El nuevo theta para la it " << k << " es: ";
		for(int i=0; i<theta.size(); i++){
			theta[i]=theta[i]-alpha*gradiente[i];
//			std::cout << theta[i]-alpha*gradiente[i] << " (" << alpha*gradiente[i] << ") ";
		}
//		std::cout << std::endl;
		vari = std::abs(coste-pCoste);
		std::cout << "La variación en el coste para la iteración "<< k <<" es de: " << vari << std::endl;
		if(vari < 0.0001 && !std::isnan(vari)){ // Truquillo porque a veces es nan
			std::cout << "Estoy suficientemente entrenado!!!!!!\n";
			break;
		} else if (std::isnan(vari)){
			std::cout << "Tengo un NaN!!!!\n";
		}
		pCoste = coste;
	}

}

void LRMachine::trainByNormalEcuation() {
	// Actualizo aqui el número de características
	int nFeaturesCuad = 2*nFeatures;
	// Obtengo la X
	arma::mat X = arma::mat(trainingSet.size(), nFeaturesCuad+1);
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<nFeatures+1; j++){
			if(j==0)
				X(i,j)=1.0;
			else X(i,j)=trainingSet[i].input[j-1];
		}
	}
	// Elementos cuadráticos
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<nFeatures; j++){
			X(i,nFeatures+j+1)=pow(trainingSet[i].input[j],2);
		}
	}
	// Obtengo la Y
	arma::mat y = arma::mat(trainingSet.size(), 1);
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			y(i)=1;
		else y(i)=0;
	}
	// Calculo la matriz de alpha
	arma::mat Alpha(nFeaturesCuad+1, nFeaturesCuad+1);
	Alpha.eye();
	Alpha(0,0)=0;
	alphaTrain*Alpha;
//	std::cout << Alpha;
	// Inicializo theta
	arma::mat theta = arma::mat(nFeaturesCuad+1, 1);
	// Calculo vectorialmente
	theta = arma::pinv(X.t()*X+Alpha)*X.t()*y;
//	std::cout << theta;
	this->theta.clear();
	for(int i=0; i<nFeaturesCuad+1; i++){
		this->theta.push_back(theta(i));
	}
}

void LRMachine::fillX() {
	//
	for(int i=0; i<trainingSet.size(); i++){
		for(int j=0; j<nFeatures+1; j++){
			if(j==0)
				X[i][j]=1.0;
			else X[i][j]=trainingSet[i].input[j-1];
		}
	}
}

void LRMachine::fillTheta() {
	for(int i=0; i<nFeatures+1; i++)
		theta[i]=0;
}

void LRMachine::fillY() {
	for(int i=0; i<trainingSet.size(); i++){
		if(trainingSet[i].burn)
			y[i]=1;
		else y[i]=0;
	}
}

void LRMachine::upgradeParameters() {

}

