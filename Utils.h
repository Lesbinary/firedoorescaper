#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "float.h"

class Utils{
public:
	static double getElement(std::vector<double> vect, std::vector<int> info, int l, int j, int k){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			if(i == info.size()-2){
				index += info[i]*info[i+1];
			} else {
				index += info[i]*(info[i+1]-1);
			}
		}

		if(i == info.size()-2){
			index += j*info[i+1];
		} else {
			index += j*(info[i+1]-1);
		}

		index += k;

		return vect[index];
	}

	//falta modificar igual que en el get
	static void setElement(std::vector<double> &vect, std::vector<int> info, int l, int j, int k, double element){
		int index = 0;
		int i;

		for(i = 0; i < l; i++){
			if(i == info.size()-2){
				index += info[i]*info[i+1];
			} else {
				index += info[i]*(info[i+1]-1);
			}
		}

		if(i == info.size()-2){
			index += j*info[i+1];
		} else {
			index += j*(info[i+1]-1);
		}

		index += k;

		vect[index] = element;
	}

	static void plotData(std::vector<double> x, std::vector<double> y){
		std::ofstream myfile;
		myfile.open ("dataset.dat");
		for(int i = 0; i < x.size(); i++)
			myfile << x[i] << " " << y[i] << std::endl;
		myfile.close();
		system("gnuplot -persist -e \"plot './datafile.dat' using 1:2 title 'X' with linespoints, './datafile.dat' using 1:2 title 'Y' with points\"");
	}

	static void scalation(std::vector<Sample> &trainingSet){
		double absolMax = DBL_MIN;

		for(int i = 0; i < trainingSet.size(); i++){
			for(int j = 0; j < trainingSet[i].input.size(); j++){
				double num = trainingSet[i].input[j];

				if(num < 0){
					num *= -1.0;
				}

				if(num > absolMax){
					absolMax = num;
				}
			}
		}

		for(int i = 0; i < trainingSet.size(); i++){
			for(int j = 0; j < trainingSet[i].input.size(); j++){
				trainingSet[i].input[j] /= absolMax;
			}
		}
	}
};

#endif /* SAMPLE_H_ */
